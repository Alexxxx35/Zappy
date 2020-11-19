# Comment exécuter

Exécutez les commandes suivantes:

```sh
$ cd Redha+Alex
$ g++ -std=c++11 -pthread -o server CliServer.cpp
$ ./serveur
$ g++ -o client CliClient.cpp
$ ./client
```

Une fois que le serveur et le client sont connectés, pour le moment nous pouvons envoyer manuellement un message au 
serveur et le serveur répondra, par exemple vous pouvez taper "left" le serveur renverra un simple message statique.

