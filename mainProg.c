#include "mainProg.h"

int main(int argc, char* argv[]) {
    char buf[256];
    
    struct HashTable hash;
    hash.size = 25;
    struct LinkedAddNode** lst = malloc(sizeof(struct LinkedAddNode*) * 25);
    for (int i = 0; i < 25; i++) {
        lst[i] = malloc(sizeof(struct LinkedAddNode));
    }
    hash.vals = lst;
    
    while (1) {
        printf(">");
        fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf) - 1] = '\0';
        struct argAndLen *aal = strSplit(buf);
        if (strcmp(aal->args[0], "setUpServer") == 0) {
            if (aal->ac != 2) {
                printf("Usage: setUpServer filename\n");
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
        else if (strcmp(aal->args[0], "printFriends") == 0) {
            printFriends(&hash);
        }
        else if (strcmp(aal->args[0], "addFriend") == 0) {
            if (aal->ac != 4) {
                printf("Usage: addFriend ip port name\n");
                continue;
            }
            uint32_t ipAdd = ipToNum(aal->args[1]);
            char* endptr;
            int port = (int) strtol(aal->args[2], &endptr, 10);
            int afr = addFriend(&hash, ipAdd, port, aal->args[3]);
            if (afr != 1) {
                if (afr == -1) {
                    printf("No more space on Friends List!\n");
                    continue;
                }
                else {
                    printf("Unknown error adding friend to list\n");
                    continue;
                }
            }
        }
        else if (strcmp(aal->args[0], "removeFriend") == 0) {
            if (aal->ac != 3) {
                printf("Usage: addFriend ip port\n");
                continue;
            }
            uint32_t ipAdd = ipToNum(aal->args[1]);
            char* endptr;
            int port = (int) strtol(aal->args[2], &endptr, 10);
            int rfr = removeFriend(&hash, ipAdd, port);
            if (rfr == 0) {
                printf("Error removing friend\n");
                continue;
            }
        }
        else if (strcmp(aal->args[0], "searchFriend") == 0) {
            if (aal->ac != 3) {
                printf("Usage: searchFriend ip port\n");
                continue;
            }
            uint32_t ipAdd = ipToNum(aal->args[1]);
            char* endptr;
            int port = (int) strtol(aal->args[2], &endptr, 10);
            int sfr = searchFriend(&hash, ipAdd, port);
            if (sfr > 0) {
                printf("Friend found\n");
            }
            else {
                printf("Friend not found\n");
            }
        }
        else if (strcmp(aal->args[0], "findIpPort") == 0) {
            if (aal->ac != 2) {
                printf("Usage: findIpPort ip\n");
                continue;
            }
            uint32_t ipAdd = ipToNum(aal->args[1]);
            findIpPorts(&hash, ipAdd);
        }
        else if (strcmp(aal->args[0], "getServerTime") == 0) {
            getServerOpenTime();
        }
        else if (strcmp(aal->args[0], "getCurrPort") == 0) {
            getPort();
        }
        else if (strcmp(aal->args[0], "setServer") == 0) {
            printf("Enter new server open time in seconds: ");
            char bufff[64];
            fgets(bufff, sizeof(bufff), stdin);
            buf[strlen(bufff) - 1] = '\0';
            char* endptr;
            int time = (int) strtol(bufff, &endptr, 10);
            setServerOpenTime(time);
        }
        else if (strcmp(aal->args[0], "setPort") == 0) {
            printf("Enter new port: ");
            char bufff[64];
            fgets(bufff, sizeof(bufff), stdin);
            buf[strlen(bufff) - 1] = '\0';
            char* endptr;
            int port = (int) strtol(bufff, &endptr, 10);
            setPort(port);
        }
        else if (strcmp(aal->args[0], "changePassword") == 0) {
            if (aal->ac != 2) {
                printf("Usage: changePassword oldpass\n");
                continue;
            }
            changePass(aal->args[1]);
        }
        else if (strcmp(aal->args[0], "commands") == 0) {
            printf("setUpServer:\nUsage: setUpServer filename\nSets up server with the given filename so others can connect and download it\n\n");
            
            printf("connect:\nUsage: connect ip port\nConnects to the server with given ip and port\n\n");
            
            printf("printFriends:\nUsage: printFriends\nPrint out friends list\n\n");
            
            printf("addFriend:\nUsage: addFriend ip port\nAdds the friend with the given ip and port\n\n");
            
            printf("removeFriend:\nUsage: removeFriend ip port\nRemoves the friend with the given ip and port\n\n");
            
            printf("searchFriend:\nUsage: searchFriend ip port\nSee if the given friend is in your friends list\n\n");
            
            printf("findIpPort:\nUsage: findIpPort ip\nGets all ports in friends list belonging to a given ip address\n\n");
            
            printf("getServerTime:\nUsage: GetServerTime\nGet amount of time in seconds a server will remain open\n\n");
            
            printf("getCurrPort:\nUsage: getCurrPort\nGet current server port number\n\n");
            
            printf("setServer:\nUsage: setServer\nChanges the number of seconds a server will be open for\n\n");
            
            printf("setPort:\nUsage: setPort\nChanges port that a server will run on\n\n");
            
            printf("changePassword:\nUsage: changePassword newPassword\nChanges password for those wanting to connect to servers\n\n");
        }
        else if (strcmp(aal->args[0], "exit") == 0) {
            break;
        }
        else {
            if (strcmp(aal->args[0], "") == 0) {
                continue;
            }
            else {
                printf("Not a valid command. Enter 'commands' to view command list.\n");
            }
        }
    }
}
