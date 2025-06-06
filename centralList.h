#ifndef CENTRALLIST_H
#define CENTRALLIST_H

#include "userHasher.h"

#define NUM_FRIENDS 25

extern char pass[64];
static int serverOpen = 15;
static int port = 53822;

static int numFriends = 0;

void printFriends(struct HashTable* hash);

int addFriend(struct HashTable* hash, uint32_t ip, int port, char* name);

int removeFriend(struct HashTable* hash, uint32_t ip, int port);

int searchFriend(struct HashTable* hash, uint32_t ip, int port);

int checkOnlineStatus(struct HashTable* hash, uint32_t ip, int port);

void findIpPorts(struct HashTable* hash, uint32_t ip);

int setUpServer(char* filename);

int connectToFriend(uint32_t ip, int port);

void getServerOpenTime();

void getPort();

void setServerOpenTime(int s);

void setPort(int s);

void changePass(char* pass);

#endif
