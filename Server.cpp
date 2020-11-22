//
// Created by dredhat on 15/11/2020.
//

#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <thread>
#include "Server.hh"
#include "json.hpp"
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#define MAX 500
#define SA struct sockaddr
using namespace std;


std::map<int,int> Server::client_sockets;
template <typename T, typename S>
void displayMap(std::map<T,S> mymap){
    for (auto it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
}


int Server::runServer(const char *hostname, long port,int nbplayers, int heigth,int witdh) {
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    int count_client =0;
    Plateau plateau(witdh,heigth);
    plateau.AddPierre();
    plateau.AddPierre();
    plateau.AddPierre();
    plateau.AddPierre();
    std::cout << "Created a map of size " << heigth<< "x" <<witdh<<std::endl;
    plateau.DisplayPlateau();

    std::cout << "Waiting for " << nbplayers << " players to join" << std::endl;

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

            while(count_client< nbplayers){

                // Accept the data packet from client and verification
                connfd = accept(sockfd, (SA*)&cli, reinterpret_cast<socklen_t *>(&len));
                if (connfd < 0) {
                    printf("server accepted failed...\n");
                    exit(0);
                }
                else{
                    printf("server accepted the client...\n");
                    client_sockets.insert(std::pair<int,int>(++count_client,connfd));
                    plateau.AddPlayer();
                    plateau.DisplayPlateau();
                    if (nbplayers > count_client){
                        std::cout << "Waiting for "<< (nbplayers-count_client) << " more clients to join !" << std::endl;
                    }


                }

                // Creating a separate thread per client
                //thread worker(readBuffer, connfd);
                //worker.detach();
                /*while(!plateau.IsVictory()){
                    for(auto it = client_sockets.begin();it != client_sockets.end();++it){
                        thread worker(readBuffer,it->second);
                        worker.detach();
                    }
                }*/
            }
            std::cout << "Game is ready to start " << std::endl;
            
            while(!plateau.IsVictory()){
                for(auto it = client_sockets.begin();it != client_sockets.end();++it){
                    if (plateau.GetPlayerById(it->first)!= nullptr){
                        handleClient(it->first,it->second,plateau);
                    }
                    plateau.KillLoosers();
                }
                std::cout << "Everyone played | Current map : " << std::endl;
                plateau.DisplayPlateau();
                std::cout << "Adding 2 random stones ...." << std::endl;
                plateau.AddPierre();
                plateau.AddPierre();
                std::cout << " New map : " << std::endl;
                plateau.DisplayPlateau();


            }


            return 1;
    }catch(exception& e){
        // After chatting close the socket
        cout << e.what() << '\n';
        close(sockfd);
        return 0;
    }
}



void Server::handleClient(int idPlayer,int sockfd, Plateau plateau){
    Joueur* j = plateau.GetPlayerById(idPlayer);
    char buff[MAX];
    while(j->GetEnergie()>0){
        bzero(buff, MAX);
        // read the message from client and copy it in buffer or wait for client message
        read(sockfd, buff, sizeof(buff));
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            close(sockfd);
            break;
        }
        ActionNames a = Action::ActionFromChar(buff);
        Action action(a);
        plateau.ExecuteAction(j,action);
        string processResult = processMessage(buff,plateau,j);
        int sizeResult = processResult.length();
        char* resChar = new char[sizeResult+1];
        strcpy(resChar, processResult.c_str());
        // and send that buffer to client
        write(sockfd, resChar, sizeof(buff));
        
    }
    j->ResetTour();
}

/*void Server::readBuffer(int sockfd) {
    char buff[MAX];
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
        char* resChar = new char[sizeResult+1];
        strcpy(resChar, processResult.c_str());

        // and send that buffer to client
        write(sockfd, resChar, sizeof(buff));
    }
}*/



string Server::processMessage(char *message,Plateau plateau, Joueur* joueur) {
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
        int nbJoueur = plateau.GetPlayerNumber();
        for(int i =0 ; i <= nbJoueur ; i++){
            Joueur* player = plateau.GetPlayerById(i);
            if (player!= nullptr){
                json j2;
                j2= {
                    {"id",player->GetId()},
                    {"life",player->GetVie()},
                    {"energy",player->GetEnergie()},
                    {"victory",player->GetVictoire()},
                    {"orientation",player->GetOrientationStr()}
                };
                j["inspect"].push_back(j2);
                
            }

        }
    }

    

    if(strcmp(message, "me\n") == 0){
        j["me"] = {
                {"id",joueur->GetId()},
                {"life",joueur->GetVie()},
                {"energy",joueur->GetEnergie()},
                {"victory",joueur->GetVictoire()},
                {"orientation",joueur->GetOrientationStr()}
        };
    }
    std::string result = j.dump();

    return result;
}



int main(int argc, char *argv[])
{
    std::string host("127.0.0.1");
    std::string port("4242");
    std::string map_height("5");
    std::string map_width("5");
    std::string players("2");
    std::string cycle("500");


    if (argc == 1)
    {
        std::cout << "no parameters other than program_name: " << std::endl;
    }

    std::cout << "number_of_params(option+args): " << argc - 1 << std::endl;

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (i % 2 != 0)
        {
            std::cout << "option: " << arg << std::endl;
        }

        if ((arg == "-h") || (arg == "--help"))
        {
            std::cerr << "Usage: " << arg << " [option(s)] "
                      << "Options:\n"
                      << "\t-h,--help\tShow this help message\n"
                      << "\t--host\t\tConfigure the host set by default on : 127.0.0.1\n"
                      << "\t--port\t\tConfigure the port for server communication set by default on : 4242\n"
                      << "\t--map-height\tConfigure the board height set by default on : 5\n"
                      << "\t--map-width\tConfigure the board witdh set by default on : 5\n"
                      << "\t--players\tConfigure number of players set by default on : 4\n"
                      << "\t--cycle\t\tConfigure the turn duration (in millisecond) set by default on : 500\n"
                      << std::endl;
            return 0;
        }

        if (arg == "--host")
        {
            if (i + 1 >= argc)
            {
                std::cout << "--host option has not argument: default value chosen" << std::endl;
                host = host;
                cout << host << endl;
            }
            else
            {
                host = argv[i + 1];
                cout << host << endl;
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
        if (arg == "--map-height")
        {
            if (i + 1 >= argc)
            {
                std::cout << "--map-height option has not argument: default value chosen" << std::endl;
                map_height = map_height;
            }
            else
            {
                map_height = argv[i + 1];
            }
        }
        if (arg == "--map-width")
        {
            if (i + 1 >= argc)
            {
                std::cout << "--map-width option has not argument: default value chosen" << std::endl;
                map_width = map_width;
            }
            else
            {
                map_width = argv[i + 1];
            }
        }
        if (arg == "--players")
        {
            if (i + 1 >= argc)
            {
                std::cout << "--players option has not argument: default value chosen" << std::endl;
                players = players;
            }
            else
            {
                players = argv[i + 1];
            }
        }
        if (arg == "--cycle")
        {
            if (i + 1 >= argc)
            {
                std::cout << "--cycle option has not argument: default value chosen" << std::endl;
                cycle = cycle;
            }
            else
            {
                cycle = argv[i + 1];
            }
        }
    }

    std::string h_string = host;
//    std::string h_string = "127.0.0.1";
    const char *h_char = h_string.c_str();

    Server server = Server();

    int nbplayers = stoi(players);
    int height = stoi(map_height);
    int width = stoi(map_width);

    server.runServer(h_char, 4242,nbplayers,height,width);

    return 0;
}
