#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <sys\stat.h>
#include <typeinfo>
#include <iostream>

#include "cpu_functions.h"
#include "..\Stack\stack.h"
#include "..\Stack\static_functions.h"



struct text_cmd input(struct text_cmd* text)
{
    assert(text != NULL);

    FILE* fpin = fopen("..\\Comp_Code.bin", "rb");

    assert(fpin != NULL);


    size_t text_size = text_len(fpin);

    (*text).buf = (char*)calloc(text_size + 1, sizeof(char));


    assert((*text).buf != NULL);


    (*text).num_symbols = fread((*text).buf, 1, text_size, fpin);

    (*text).num_str = number_str((*text).buf, (*text).num_symbols, ' ');

    (*text).strings = (struct line*)calloc((*text).num_str + 1, sizeof(struct line));
    text = pointer(text, text_size, ' ');


    fclose(fpin);

    return *text;
}

size_t number_str(char buf[], size_t n, char ch)
{
    assert(buf != NULL);

    size_t num = 0;
    for (size_t i = 0; i < n; ++i)
    {
        if (buf[i] == ch)
            ++num;
    }
    return num;
}


struct text_cmd* pointer(struct text_cmd* text, size_t text_size, char end_ch)
{
    assert(text != NULL);

    (*text).strings[0].ptr = &(*text).buf[0];

    size_t nline = 1;
    for (size_t i = 0; i < text_size - 1; ++i)
    {
        if ((*text).buf[i] == end_ch)
        {
            (*text).strings[nline].ptr = &(*text).buf[i + 1];
            (*text).strings[nline - 1].len = (*text).strings[nline].ptr - (*text).strings[nline - 1].ptr;
            (*text).buf[i] = '\0';
            ++nline;
        }
    }
    (*text).strings[nline - 1].len = (*text).strings[nline].ptr - (*text).strings[nline - 1].ptr;

    return text;
}

size_t text_len(FILE* fp)
{
    assert(fp != NULL);

    struct stat buff = {};
    fstat(fileno(fp), &buff);

    return buff.st_size;
}

int ProcessorMain ()
{
    struct text_cmd text = { 0, NULL, 0, NULL };
    text = input(&text);
    
    struct stack stk = {0, NULL, 0, 0, 0, 0, 0, 0};
    StackCtor (&stk, text.num_str + 1);
   // elem_t RAM[5800] = {};

    for (size_t ip = 0; ip <= text.num_str;ip++)
    {
        #define DEF_CMD(name, num, arg, code) if(num == (int) *text.strings[ip].ptr - 48)\
                                              {\
                                              code\
                                              }\
                                              else
        #include "..\cmd.h"
        /*else*/ printf("Syntax Error\n");
        #undef DEF_CMD
    }




    return 0;
}

int GetArg (char* arg)
{
    int temp = 0;
    int fl = 1;
    if (*arg == '-')
    {
        fl = -1;
        arg++;
    }

    for (; *arg != '\0'; arg++)
    {
        temp = temp * 10 + *arg - 48;
    }

    return temp * fl;
}