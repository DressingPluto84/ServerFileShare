#include "userHasher.h"

int hashFunc(uint32_t ipAdd, int port, int size) {
    uint32_t val = ipAdd + port;
    return val % size;
}

int hashSearch(uint32_t ipAdd, int port, struct HashTable* table) {
    int slot = hashFunc(ipAdd, port, table->size);
    if ((table->vals)[slot] == NULL) {
        return 0;
    }
    struct LinkedAddNode* node = (table->vals)[slot];
    while (node != NULL) {
        if (node->ip == ipAdd && node->port == port) {
            return 1;
        }
        else {
            node = node->next;
        }
    }
    return 0;
}

int hashInsert(uint32_t ipAdd, int port, struct HashTable* table) {
    int slot = hashFunc(ipAdd, port, table->size);
    struct LinkedAddNode* new = malloc(sizeof(struct LinkedAddNode));
    new->ip = ipAdd;
    new->port = port;
    new->next = NULL;
    if (table->vals[slot] == NULL) {
        (table->vals)[slot] = new;
    }
    else {
        struct LinkedAddNode* old = (table->vals)[slot];
        (table->vals)[slot] = new;
        new->next = old;
    }
    return 1;
}

int hashDelete(uint32_t ipAdd, int port, struct HashTable* table) {
    int slot = hashFunc(ipAdd, port, table->size);
    struct LinkedAddNode* node = (table->vals)[slot];
    if (node == NULL) {
        return 0;
    }
    if (node->ip == ipAdd && node->port == port) {
        struct LinkedAddNode* nk = (table->vals)[slot];
        (table->vals)[slot] = node->next;
        free(nk);
        return 1;
    }
    while (node != NULL && node->next != NULL) {
        if (node->next->ip == ipAdd && node->next->port == port) {
            struct LinkedAddNode* nk = node->next;
            node->next = node->next->next;
            free(nk);
            return 1;
        }
        node = node->next;
    }
    return 0;
}

int* hashFindPorts(uint32_t ipAdd, struct HashTable* table) {
    int slot = hashFunc(ipAdd, 0, table->size);
    int numPorts = 0;
    int ports[table->size];
    
    struct LinkedAddNode* node = (table->vals)[slot];
    if (node == NULL) {
        return (int*) 0;
    }
    while (node != NULL) {
        if (node->ip == ipAdd) {
            ports[numPorts] = node->port;
            numPorts += 1;
        }
        node = node->next;
    }
    
    int* totalPorts = malloc(sizeof(int) * (numPorts + 1));
    int i = 0;
    for (; i < numPorts; i++) {
        totalPorts[i] = ports[i];
    }
    totalPorts[i] = -1;
    return totalPorts;
}
