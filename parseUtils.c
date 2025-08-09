#include "parseUtils.h"

struct argAndLen* strSplit(char* str) {
    /* splits arguments by spaces into a struct
    struct has num args and each arg
    */
    int i = 0;
    int count = 0;
    char* space = strchr(str, ' ');
    char* start = str;
    char** finalChars = malloc(strlen(str) * sizeof(char*));
    while (space != NULL) {
        finalChars[i] = getStr(start, space);
        i += 1;
        start = space + 1;
        space = strchr(start, ' ');
        count += 1;
    }
    finalChars[i] = getStr(start, start + strlen(start));
    count += 1;
    char** finalForReal = malloc(sizeof(char*) * count);
    for (int j = 0; j < count; j++) {
        finalForReal[j] = finalChars[j];
    }
    free(finalChars);
    struct argAndLen *as = malloc(sizeof(struct argAndLen));
    as->ac = count;
    as->args = finalForReal;
    return as;
}

char* getStr(char* str1, char* str2) {
    int i = 0;
    int newLen = str2 - str1;
    char* newStr = malloc(newLen + 1);
    for (; i < newLen; i++) {
        newStr[i] = str1[i];
    }
    newStr[i] = '\0';
    return newStr;
}

char* extractFileType(char* str) {
    char* type = strchr(str, '.');
    if (type == NULL) {
        return "plaintext";
    }
    type += 1;
    if (type - str >= strlen(str)) {
        return "plaintext";
    }
    if (strchr(type, '.') != NULL) {
        return "plaintext";
    }
    return type;
}

uint32_t ipToNum(char* ipAdd) {
    struct in_addr s;
    int af = inet_pton(AF_INET, ipAdd, &s);
    if (af < 0) {
        perror("ip converion error");
        exit(1);
    }
    return s.s_addr;
}
