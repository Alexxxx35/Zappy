//
// Created by dredhat on 16/11/2020.
//

#ifndef TCP_SERVER_CLIENT_HH
#define TCP_SERVER_CLIENT_HH

#include "Joueur.hh"

class Client {
public:
    void processBuffer(int sockfd);
    void sendCommands(int sockfd);
    void runClient(const char *hostname, long port);
    Client();
    ~Client();
    Joueur j;
};


#endif //TCP_SERVER_CLIENT_HH
