#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>

#define MAX 500
#define SA struct sockaddr

#include "Client.hh"

void Client::processBuffer(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s\n", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            close(sockfd);
            break;
        }
    }
}

void Client::sendCommands(int sockfd){
    this->j.QueueRandomActions();
    char buff[MAX];
    bzero(buff, sizeof(buff));
    std::queue<Action> actions = this->j.GetQueue();
    while (!actions.empty()){
        Action a = actions.front();
        std::string s = a.toString();
        actions.pop();
        strcpy(buff,s.c_str());
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s\n", buff);
    }
    this->j.ResetTour();
}

void Client::runClient(const char *hostname, long port) {
    int sockfd;
    //int connfd;
    struct sockaddr_in servaddr;

    // socket create and varification
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

    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    //////////////////////////////A modifier , le client reste à l'écoute jusqu'a ce que le serveur lui demande d'envoyer des commandes ///////
    processBuffer(sockfd);
    //sendCommands(sockfd);

    // close the socket
    close(sockfd);
}

Client::Client(){
    
}
Client::~Client(){

}

int main(int argc, char *argv[])
{
    std::string host("127.0.0.1");
    std::string port("4242");

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg == "--host")
        {
            if (i + 1 >= argc)
            {
                std::cout << "--host option has not argument: default value chosen" << std::endl;
                host = host;
            }
            else
            {
                host = argv[i + 1];
            }
        }

        if (arg == "--port")
        {
            if (i + 1 >= argc)
            {
                std::cout << "--port option has not argument: default value chosen" << std::endl;
                port = port;
            }
            else
            {
                port = argv[i + 1];
            }
        }
    }

    std::string h_string = host;
    const char *h_char = h_string.c_str();

    Client client = Client();

    client.runClient(h_char, 4242);
    return 0;
}