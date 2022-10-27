#include <stdio.h>

size_t number_str(char buf[], size_t n, char ch);

struct text_cmd input(struct text_cmd* text);

size_t text_len(FILE* fp);

struct text_cmd* pointer(struct text_cmd* text, size_t text_size, char end_ch);



int ProcessorMain ();

int GetArg (char* arg);


struct line
{
	size_t len;
	char* ptr;
};


struct text_cmd
{
	size_t num_str;
	char* buf;
	size_t num_symbols;
	struct line* strings;
};

#define DEF_CMD(name, num, ...) CMD_##name = num,
enum Commands
{
#include "..\cmd.h"
};
#undef DEF_CMD

