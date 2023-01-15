#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include "kmess_cli_handler.h"

char buffer[1024];
char temp_buffer[1024];
// const char newline_hex[4] = {'\\', 'x', '0', 'a'};
// const char newline_hex[] = "\\x0a";
// const char newline_hex[] = "\x0a";
char newline_hex[] = "\x0a";
int epollfd, fd;
bool isMultipleLine = false;
cli_handler my_cli_hanlder;

char kmess_help[]=
"Usage: kmess [OPTION]\n"\
" -h,            Get help for the command\n"\
" -m             Some kernel message is multi-lines, use this to display full msg\n"\
"                1 line displayed is default\n"\
" -e             use pattern for matching, not currently supporting regexp\n"\
" -v             use pattern for non-matching, not currently supporting regexp\n"\
" -i             ignore case sensitive";

void signal_action_handler(int signal_number, siginfo_t *siginfo, void *ucontext){
    close(fd);
    close(epollfd);
    exit(0);
}

int main(int argc, char** args)
{

    int result = get_cli_params(argc, args, &my_cli_hanlder);
    if (result < 0)
    {
        printf("kmess: fail to get cli params\n");
        exit(1);
    }

    if (my_cli_hanlder.help_option != 0)
    {
        printf("%s\n", kmess_help);
        exit(0);
    }

    if (my_cli_hanlder.m_option != 0)
    {
        isMultipleLine = true;
    }

    // Set up signal to override the ctrl + c action
    // Just for the purpose of safe exit when pressing ctrl + c
    struct sigaction sa;
    sa.sa_sigaction = &signal_action_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa, NULL);
    fd = open("/dev/kmsg", O_RDONLY|O_NONBLOCK);
    if (fd < 0)
    {
        printf("fail to open\n");
        return -1;
    }

    // need this to fetch the latest update
    lseek(fd, 0, SEEK_END);

    struct epoll_event ev, events[MAX_EVENTS];
    int nfds;

    epollfd = epoll_create1(0);
    if (epollfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
        perror("Fail to init epoll\n");
        exit(EXIT_FAILURE);
    }

    char* analyze_content_msg = NULL;
    for (;;) {
        bzero(buffer, 1024);
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            close(epollfd);
            exit(EXIT_FAILURE);
        }
        for (int n = 0; n < nfds; ++n) {
            if (events[n].data.fd == fd) {
                int sz = read(fd, buffer, 1024);
                // the format will be sth like this
                // 4,516,1452858886,-;<kernel message>
                // string process
                char* content_msg = strstr(buffer, ";") + 1;
                free(analyze_content_msg);
                if (my_cli_hanlder.m_option != 0) content_msg[strlen(content_msg) - 1] = 0; // strip out last \n
                else content_msg = strtok(content_msg, "\n");

                analyze_content_msg = malloc(strlen(content_msg) + 1);
                strcpy(analyze_content_msg, content_msg);

                //-i option handler
                if (my_cli_hanlder.i_option != 0) TOLOWER(analyze_content_msg);

                //-e option handler
                if (my_cli_hanlder.e_option.index != 0)
                {
                    char* match_pattern = malloc(strlen(my_cli_hanlder.e_option.pattern) + 1);
                    strcpy(match_pattern, my_cli_hanlder.e_option.pattern);
                    if (my_cli_hanlder.i_option != 0)
                    {
                        TOLOWER(match_pattern);
                    }
                    bool isMatch = STRCT(analyze_content_msg, match_pattern);
                    free(match_pattern);
                    if (isMatch == false)
                    {
                        continue;
                    }
                }

                //-v option handler
                if (my_cli_hanlder.v_option.index != 0)
                {
                    char* match_pattern = malloc(strlen(my_cli_hanlder.v_option.pattern) + 1);
                    strcpy(match_pattern, my_cli_hanlder.v_option.pattern);
                    if (my_cli_hanlder.i_option != 0) TOLOWER(match_pattern);
                    bool isMatch = STRNCT(analyze_content_msg, match_pattern);
                    free(match_pattern);
                    if (isMatch == false) continue;
                }
                char* num_str = strtok(buffer, ";");
                char* time_str = strtok(num_str, ",");
                time_str = strtok(NULL, ",");
                time_str = strtok(NULL, ",");

                // get the third string number after commas
                // this number represents the number of micro second from starting kernel to present
                long long ret = atoll(time_str);
                double time_s = ret / 1000000.0;

                // final printf
                // check multipline option to handle hex output "\x0a"
		
                // IDEAS
                // brief explaination, when using \n in printk, the buffer read from /dev/kmesg replace the '\n'
                // character with four other characters '\' 'x' '0' 'a'
                // In the -m option, we will handle this four character with new line when print out the message

                // ISSUE
                // A testing kernel module with 1 simple printk("line1\nline2") is used for testing
                // The buffer read to the content_msg variable is fully expanded to "line1\x0aline2" (debugged)
                // Already have the design to handle this, but the "strstr" function doesn't behave as expected
                // Here strstr(content_msg, newline_hex) return NULL break the design flow which should oviously
                // return not NULL ???????

                if (my_cli_hanlder.m_option != 0 && strstr(content_msg, newline_hex) != NULL)
                {
                    int temp_size = strlen(content_msg);
                    char* s_ptr = content_msg;
                    char* p_ptr = s_ptr;
                    bzero(temp_buffer, 1024);
                    while((s_ptr = strstr(s_ptr, newline_hex)) != NULL)
                    {
                        printf("here: %d\n", temp_size);
                        *s_ptr = 0;
                        strcat(temp_buffer, p_ptr);
                        strcat(temp_buffer, "\n");
                        s_ptr+=4;
                        p_ptr = s_ptr;
                    }
                     if(p_ptr != (content_msg + temp_size)){
                        strcat(temp_buffer, p_ptr);
                    }
                    printf("[ %.6lf] %s\n", time_s, temp_buffer);
                }
                else if (my_cli_hanlder.m_option != 0 && strstr(content_msg, newline_hex) == NULL) {
                    printf("DEBUG strstr() is NULL [ %.6lf] %s\n", time_s, content_msg);
                    // for (int i = 0; i < strlen(content_msg); i++) printf("%c %d\n", content_msg[i], content_msg[i]);
                }
                else printf("[ %.6lf] %s\n", time_s, content_msg);

            } else {
                // weird behavior
                close(epollfd);
                exit(1);
            }
        }
    }

    // program cannot get here
    return 0;
}
