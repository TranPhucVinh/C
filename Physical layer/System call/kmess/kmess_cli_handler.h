#ifndef _INC_KMESS_CLI_HANDLER
#define _INC_KMESS_CLI_HANDLER

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define STREQ(str1, str2) (strcmp(str1, str2) == 0)
#define STRNEQ(str1, str2) (strncmp(str1, str2) == 0)
#define STRSW(str1, str2) (strstr(str1, str2) == str1)
#define STRNSW(str1, str2) (strstr(str1, str2) != str1)
#define STRCT(str1, str2) (strstr(str1, str2) != NULL)
#define STRNCT(str1, str2) (strstr(str1, str2) == NULL)

typedef struct
{
    uint8_t index;
    char* pattern;
} e_option_typedef;

typedef struct
{
    uint8_t index;
    char* pattern;
} v_option_typedef;

typedef struct
{
    uint8_t help_option;
    uint8_t m_option;
    v_option_typedef v_option;
    e_option_typedef e_option;
    uint8_t i_option;
} cli_handler;


int get_cli_params(int argc, char** args, cli_handler* result);

#endif