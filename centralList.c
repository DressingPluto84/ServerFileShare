#include "centralList.h"

char pass[64] = "password";

void printFriends(struct HashTable* hash) {
    for (int i = 0; i < hash->size; i++) {
        if (hash->vals[i] != NULL) {
            struct in_addr ia;
            ia.s_addr = hash->vals[i]->ip;
            printf("Address: %s:%d\n", inet_ntoa(ia), hash->vals[i]->port);
        }
    }
}

int addFriend(struct HashTable* hash, uint32_t ip, int port) {
    if (numFriends >= hash->size) {
        return 0;
    }
    int k = hashInsert(ip, port, hash);
    if (k < 1) {
        fprintf(stderr, "Error adding new Friend");
        return 0;
    }
    numFriends += 1;
    return 1;
}

int removeFriend(struct HashTable* hash, uint32_t ip, int port) {
    if (numFriends == 0) {
        return 0;
    }
    int hashDeleteRet = hashDelete(ip, port, hash);
    if (!hashDeleteRet) {
        fprintf(stderr, "Error removing this Friend");
        return 0;
    }
    numFriends -= 1;
    return 1;
}

int searchFriend(struct HashTable* hash, uint32_t ip, int port) {
    if (!hashSearch(ip, port, hash)) {
        return 0;
    }
    return 1;
}

void findIpPorts(struct HashTable* hash, uint32_t ip) {
    int* ports = hashFindPorts(ip, hash);
    int i = 0;
    while (ports[i] != -1) {
        printf("%d\n", ports[i]);
        i += 1;
    }
    return;
}

int checkOnlineStatus(struct HashTable* hash, uint32_t ip, int port) {
    if (hashSearch(ip, port, hash) == 0) {
        return 0;
    }
    return 1;
    //int sock = socket(AF_INET, SOCK_STREAM, 0);
}

int setUpServer(char* filename) {
    int pid = fork();
    
    if (pid < 0) {
        perror("Server fork failure");
        exit(-1);
    }
    else if (pid == 0) {
        execlp("./serverForFileSharing", "serverForFileSharing", pass, filename, NULL);
        
        perror("Server Set Up Execlp failure");
        exit(-1);
    }
    else {
        return 0;
    }
}

int connectToFriend(uint32_t ip, int port) {
    uint32_t htonIp = htonl(ip);
    char bufIp[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &htonIp, bufIp, sizeof(bufIp)) == NULL) {
        fprintf(stderr, "IP conversion from uint32_t to string failed");
        return -1;
    }
    
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket error connecting to friend");
        exit(-1);
    }
    
    printf("hello\n");
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    inet_pton(AF_INET, bufIp, &serv.sin_addr);
    int con = connect(sock, (struct sockaddr*) &serv, sizeof(serv));
    if (con < 0) {
        perror("client connect failure");
        exit(-1);
    }
    
    char buf[64];
    printf("Enter password:\n");
    fgets(buf, sizeof(buf), stdin);
    buf[strlen(buf)] = '\0';
    send(sock, buf, sizeof(buf), 0);
    
    char fileBuf[128];
    read(sock, fileBuf, sizeof(fileBuf));
    fileBuf[127] = '\0';
    printf("File name to download: %s\n", fileBuf);
    
    char newFile[128];
    fgets(newFile, sizeof(newFile), stdin);
    newFile[127] = '\0';
    FILE *fp = fopen(newFile, "w");
    if (fp == NULL) {
        fprintf(stderr, "error opening new file\n");
        exit(-1);
    }
    
    int n;
    uint8_t fileTransBuf[1024];
    while ((n = read(sock, fileTransBuf, sizeof(fileTransBuf))) > 0) {
        fwrite(fileTransBuf, n, 1, fp);
    }
    
    fclose(fp);
    
    return 1;
}

void getServerOpenTime() {
    printf("%d\n", serverOpen);
}

void getPort() {
    printf("%d\n", port);
}

void setServerOpenTime(int s) {
    serverOpen = s;
}

void setPort(int s) {
    port = s;
}

void changePass(char* password) {
    char buf[64];
    fgets(buf, sizeof(buf), stdin);
    buf[strlen(buf) - 1] = '\0';
    if (strcmp(buf, pass) == 0) {
        strncpy(pass, password, strlen(password) + 1);
    }
}
