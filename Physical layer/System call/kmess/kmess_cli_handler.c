#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "kmess_cli_handler.h"

#define OPTION_STRING "ie:iv:e:v:mhi"

int get_cli_params(int argc, char** args, cli_handler* result)
{
    int argflag;
    while ((argflag = getopt(argc, (char **)args, OPTION_STRING)) != -1)
    {
        switch (argflag)
        {
        case 'e':
            // printf("case %c. with param: %s\n", argflag, optarg);
            result->e_option.pattern = (char*)malloc(strlen(optarg)+1);
            bzero(result->e_option.pattern, strlen(optarg)+1);
            strcpy(result->e_option.pattern, optarg);
            result->e_option.index = 1;
            break;
        case 'h':
            // printf("case %c. with param: %s\n", argflag, optarg);
            result->help_option = 1;
            break;
        case 'i':
            // printf("case %c. with param: %s\n", argflag, optarg);
            result->i_option = 1;
            break;
        case 'm':
            // printf("case %c. with param: %s\n", argflag, optarg);
            result->m_option = 1;
            break;
        case 'v':
            // printf("case %c. with param: %s\n", argflag, optarg);
            result->v_option.pattern = (char*)malloc(strlen(optarg)+1);
            bzero(result->v_option.pattern, strlen(optarg)+1);
            strcpy(result->v_option.pattern, optarg);
            result->v_option.index = 1;
            break;
        default:
            break;
        }
    }
    return 0;
}