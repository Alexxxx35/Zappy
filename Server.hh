//
// Created by dredhat on 15/11/2020.
//

#ifndef TCP_SERVER_SERVER_HH
#define TCP_SERVER_SERVER_HH
#include <iostream>
#include "Plateau.hh"

using namespace std;


class Server {
public:
    static int runServer(const char *hostname, long port,int nbplayers,int heigth,int width);
    static void readBuffer(int sockfd);
    static void handleClient(int idPlayer,int sockfd, Plateau plateau);
    static string processMessage(char message[],Plateau p, Joueur* j);
    //static Joueur* j;
    static std::map<int,int> client_sockets;
};


#endif //TCP_SERVER_SERVER_HH
