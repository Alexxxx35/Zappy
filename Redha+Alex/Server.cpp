//
// Created by dredhat on 15/11/2020.
//

#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <strings.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <thread>
#include "Server.hh"
#include "json.hpp"
#define MAX 80
#define SA struct sockaddr
using namespace std;


int Server::runServer(const char *hostname, long port) {
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    try{

            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd == -1) {
                printf("socket creation failed...\n");
                exit(0);
            }
            else
                printf("Socket successfully created..\n");
            bzero(&servaddr, sizeof(servaddr));

            // assign IP, PORT
            servaddr.sin_family = AF_INET;
            servaddr.sin_addr.s_addr = inet_addr(hostname);
            servaddr.sin_port = htons(port);

            // Binding newly created socket to given IP and verification
            if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
                printf("socket bind failed...\n");
                exit(0);
            }
            else
                printf("Socket successfully binded..\n");
            // Now server is ready to listen and verification


            if ((listen(sockfd, 5)) != 0) {
                printf("Listen failed...\n");
                exit(0);
            }
            else
                printf("Server listening..\n");
            len = sizeof(cli);
        for (;;) {
            // Accept the data packet from client and verification
            connfd = accept(sockfd, (SA*)&cli, reinterpret_cast<socklen_t *>(&len));
            if (connfd < 0) {
                printf("server acccept failed...\n");
                exit(0);
            }
            else
                printf("server acccept the client...\n");

            // Creating a separate thread per client
            thread worker(readBuffer, connfd);
            worker.detach();
        }
    }catch(exception& e){
        // After chatting close the socket
        cout << e.what() << '\n';
        close(sockfd);
        return 0;
    }
}

void Server::readBuffer(int sockfd) {
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer or wait for client message
        read(sockfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            close(sockfd);
            break;
        }

        string processResult = processMessage(buff);
        int sizeResult = processResult.length();
        char resChar[sizeResult+1];
        strcpy(resChar, processResult.c_str());

        // and send that buffer to client
        write(sockfd, resChar, sizeof(buff));
    }
}

string Server::processMessage(char *message) {
    using json = nlohmann::json;
    json j;

    if(strcmp(message, "left\n") == 0){
        j["left"] = "OK";
    }

    if(strcmp(message, "right\n") == 0){
        j["right"] = "OK";
    }

    if(strcmp(message, "fwd\n") == 0){
        j["fwd"] = "OK";
    }

    if(strcmp(message, "leftfwd\n") == 0){
        j["leftfwd"] = "OK";
    }

    if(strcmp(message, "rightfwd\n") == 0){
        j["rightfwd"] = "OK";
    }

    if(strcmp(message, "jump\n") == 0){
        j["jump"] = "OK";
    }

    if(strcmp(message, "back\n") == 0){
        j["back"] = "OK";
    }

    if(strcmp(message, "inspect\n") == 0){
        j["inspect"] ={
                {
                        {"id",1},
                        {"life",8},
                        {"victory",1}
                },{
                        {"id",2},
                        {"life",2},
                        {"victory",4}
                }
        };
    }

    if(strcmp(message, "me\n") == 0){
        j["me"] = {
                {"id",1},
                {"life",8},
                {"energy",1},
                {"victory",7},
                {"orientation","West"}
        };
    }
    std::string result = j.dump();

    return result;
}
