#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024

void get_service_banner(const char *ip, int port) {
    int sock;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE], message[] = "GET / HTTP/1.1\r\nHost: \r\n\r\n";
    ssize_t bytes_received;

    // Création du socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Erreur de création du socket");
        return;
    }

    // Préparation de l'adresse du serveur
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);

    // Connexion au serveur
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Erreur de connexion");
        close(sock);
        return;
    }

    // Envoi de la requête HTTP
    if (send(sock, message, strlen(message), 0) < 0) {
        perror("Erreur d'envoi de données");
        close(sock);
        return;
    }

    // Réception de la bannière
    bytes_received = recv(sock, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received < 0) {
        perror("Erreur de réception de données");
        close(sock);
        return;
    }

    if (bytes_received > 0) {
        buffer[bytes_received] = '\0'; // Assurez-vous que la chaîne est terminée
        printf("Bannière reçue du port %d:\n%s\n", port, buffer);
    } else {
        printf("Aucune bannière reçue du port %d\n", port);
    }

    // Fermeture du socket
    close(sock);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Utilisation: %s <adresse IP> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    get_service_banner(ip, port);
    return 0;
}
