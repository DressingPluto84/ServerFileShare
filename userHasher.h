#ifndef USERHASHER_H
#define USERHASHER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>

struct LinkedAddNode {
    uint32_t ip;
    int port;
    char* name;
    struct LinkedAddNode* next;
};

struct HashTable {
    struct LinkedAddNode** vals;
    int size;
};

int hashFunc(uint32_t ipAdd, int port, int size);

int hashSearch(uint32_t ipAdd, int port, struct HashTable* table);

int hashInsert(uint32_t ipAdd, int port, char* name, struct HashTable* table);

int hashDelete(uint32_t ipAdd, int port, struct HashTable* table);

int* hashFindPorts(uint32_t ipAdd, struct HashTable* table);

#endif
