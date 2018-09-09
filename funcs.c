/***************************************************************************
  > Filename   : funcs.c
  > Author     : oneface - one_face@sina.com
  > Company    : 一尊还酹江月
  > Time       : 2018-09-09 12:07:30
  > Description: 

  - This program is free software; you can redistribute it and/or modify it
  - under the terms of the GNU General Public License as published by the
  - Free Software Foundation;  either version 2 of the  License, or (at your
  - option) any later version.
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	CHARARRY,
	STRUCT,
	INT,
	STRUCTARRY,
}DATA_TYPE;

#define API_Print	Print_function

#define FUNC_BINARY(data)	{ \
	int i;	\
	for (i = 31; i >= 0; i--) { \
		if (data & (1 << i)) { \
			printf("1"); \
		} else { \
			printf("0"); \
		} \
	} \
	printf("\n"); \
}

typedef void (*psub)(int data);
typedef void (*pfunction)(DATA_TYPE type, int data, psub sub_func, void *buf, int bufsize);

struct struct_data {
	int a;
	char *c;
};

typedef struct _datastruct {
	DATA_TYPE type;
	int data;
	void *buffer;
	int bufsize;
	pfunction pfunc;
}datastruct;

void Print_function(DATA_TYPE type, void *buf, int bufsize)
{
	int i;

	switch (type) {
		case CHARARRY:
			{
				char **print_buf = (char **)buf;
				while (*print_buf != NULL) {
					printf("buf array: %s\n", *print_buf++);
				}
				break;
			}
		case STRUCT:
			break;
		case INT:
			break;
		case STRUCTARRY:
			{
				struct struct_data *pdatas = (struct struct_data *)buf;
				for (i = 0; i < bufsize; i++) {
					printf("%d, %s\n", pdatas->a, pdatas->c);	
					pdatas++;
				}
				break;
			}
		default:
			break;
	}
}

void sub_function(int data)
{
	FUNC_BINARY(data);
}

void data_function(DATA_TYPE type, int data, psub sub_func, void *buf, int bufsize)
{
	printf("data: %d\n", data);
	sub_func(data);
	API_Print(type, buf, bufsize);
}

char *buf_array[] = {
	"hello world",
	"i am fun",
	NULL
};

struct struct_data datas[] = {
	[0] = {909, "what`s the fuck"},
	[1] = {818, "i am the king"},
};

int main()
{
	datastruct *dst = (datastruct *)malloc(sizeof(datastruct));
	//
	dst->data = 666;
	//dst->type = CHARARRY;
	//dst->buffer = buf_array;
	dst->type = STRUCTARRY;
	dst->buffer = datas;
	dst->bufsize = sizeof(datas) / sizeof(datas[0]);
	dst->pfunc = data_function;
	psub sfunc = sub_function;
	dst->pfunc(dst->type, dst->data, sfunc, dst->buffer, dst->bufsize);

	free(dst);
	dst = NULL;

	return 0;
}
