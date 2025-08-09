#include "serverForFileSharing.h"

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        return 1;
    }
    
    time_t curr = time(NULL);
    
    if (curr == (time_t)(-1)) {
        fprintf(stderr, "Error in server set up (timing)");
    }

    //socket set up
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    mySock = sock;
    if (sock < 0) {
        perror("socket error");
        return 0;
    }

    //create child process for counting how long server is open
    int f = fork();
    if (f < 0) {
        perror("forking server");
        exit(1);
    }
    else if (f == 0) {
        close(sock);
        while (1) {
            if (difftime(time(NULL), curr) > serverOpen) {
                //send signal to kill the server process
                int killer = kill(getppid(), SIGINT);
                if (killer < 0) {
                    perror("kill");
                    exit(0);
                }
                exit(0);
            }
        }
    }
    else if (f > 0) {
        //server side socket setup
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        struct in_addr ipAddy;
        ipAddy.s_addr = INADDR_ANY;
        addr.sin_addr = ipAddy;
        
        int bindRet = bind(sock, (struct sockaddr*) &addr, sizeof(addr));
        if (bindRet < 0) {
            perror("socket bind error");
            return 0;
        }
        
        int lis = listen(sock, NUM_FRIENDS);
        if (lis < 0) {
            perror("listen call failure");
            return 0;
        }
        
        while (1) {
            //waiting for clients to connect
            struct sockaddr_in* client = malloc(sizeof(struct sockaddr_in));
            socklen_t sizeCli = sizeof(client);
            
            int acc = accept(sock, (struct sockaddr*) client, &sizeCli);
            if (acc < 0) {
                perror("accept call failed");
                exit(1);
            }
            
            char buf[64];
            int amtRead = read(acc, buf, sizeof(buf));
            if (amtRead < 0) {
                perror("Error reading from client trying to connect");
            }
            buf[strlen(buf) - 1] = '\0';
            if (strcmp(buf, argv[1]) != 0) {
                close(acc);
                continue;
            }
            
            int wriCli = write(acc, argv[2], strlen(argv[2]) + 1);
            if (wriCli < 0) {
                perror("writing filename to client");
                close(acc);
                continue;
            }
            
            
            pthread_t thread;
            struct clientInfo* cli = malloc(sizeof(struct clientInfo));
            cli->cliFd = acc;
            cli->fname = argv[2];
            //each client get a seperate thread
            int ptc = pthread_create(&thread, NULL, writeToClient, (void *)cli);
            if (ptc > 0) {
                fprintf(stderr, "thread creation");
                exit(1);
            }
        }
    }
}

void* writeToClient(void* arg) {
    struct clientInfo *cli = arg;
    int n;
    uint8_t buf[1024];
    FILE* fp = fopen(cli->fname, "rb");
    if (fp == NULL) {
        fprintf(stderr, "error reading file");
        return (void*)(1);
    }
    
    while ((n = fread(buf, 1, sizeof(buf), fp)) > 0) {
        send(cli->cliFd, buf, n, 0);
    }
    
    close(cli->cliFd);
    fclose(fp);
    return (void*)(1);
}

void sigIntHandler(int sig) {
    close(mySock);
    exit(sig);
}
