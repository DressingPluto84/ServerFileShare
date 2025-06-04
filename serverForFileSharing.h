#ifndef SERVERFORFILESHARING_H
#define SERVERFORFILESHARING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <time.h>
#include <pthread.h>
#include "centralList.h"
#include "userHasher.h"
#include <signal.h>

struct clientInfo {
    int cliFd;
    char* fname;
};

static int mySock;

void* writeToClient(void* arg);

void sigIntHandler(int sig);

#endif
