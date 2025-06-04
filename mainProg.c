#include "mainProg.h"

int main(int argc, char* argv[]) {
    char buf[256];
    
    while (1) {
        printf(">");
        fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf) - 1] = '\0';
        struct argAndLen *aal = strSplit(buf);
        if (strcmp(aal->args[0], "setUpServer") == 0) {
            if (aal->ac != 2) {
                printf("Usage: setServer filename\n");
                continue;
            }
            int sss = setUpServer(aal->args[1]);
            if (sss < 0) {
                printf("Server Setup Failure\n");
                continue;
            }
        }
        else if (strcmp(aal->args[0], "connect") == 0) {
            if (aal->ac != 3) {
                printf("Usage: connect ip port\n");
                continue;
            }
            uint32_t ipAdd = ipToNum(aal->args[1]);
            char* endptr;
            int port = (int) strtol(aal->args[2], &endptr, 10);
            if (endptr == aal->args[2]) {
                printf("Usage: connect ip port\n");
            }
            int con = connectToFriend(ipAdd, port);
            if (con < 0) {
                printf("Connection Failure\n");
                continue;
            }
        }
        else if (strcmp(aal->args[0], "setServer") == 0) {
            
        }
        break;
    }
}
