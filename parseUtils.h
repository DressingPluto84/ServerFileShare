#ifndef PARSEUTILS_H
#define PARSEUTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

struct argAndLen {
    int ac;
    char** args;
};

struct argAndLen* strSplit(char* str);

char* getStr(char* str1, char* str2);

char* extractFileType(char* str);

uint32_t ipToNum(char* ipAdd);

#endif
