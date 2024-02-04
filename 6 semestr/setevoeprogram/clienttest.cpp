#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFLEN 81

int main(int argc, char *argv[]) {
    int sock;
    char message[BUFLEN];
    struct sockaddr_in servAddr, clientAddr;
    struct hostent *hp;

    if (argc < 3) {
        printf("Введите udpclient имя_хоста порт\n");
        exit(1);
    }

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Не могу получить socket\n");
        exit(1);
    }

    bzero((char *)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    hp = gethostbyname(argv[1]);
    bcopy(hp->h_addr, &servAddr.sin_addr, hp->h_length);
    servAddr.sin_port = htons(atoi(argv[2]));

    bzero((char *)&clientAddr, sizeof(clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    clientAddr.sin_port = 0;

    if (bind(sock, (struct sockaddr *)&clientAddr, sizeof(clientAddr))) {
        perror("Клиент не получил порт.");
        exit(1);
    }

    printf("CLIENT: Готов к пересылке.\n");

    for (int i = 1; i <= 10; ++i) {
        snprintf(message, BUFLEN, "%d", i);
        if (sendto(sock, message, strlen(message), 0, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
            perror("Проблемы с sendto . \n");
            exit(1);
        }

        printf("Sent: %d\n", i);

        // Получаем подтверждение от сервера
        bzero(message, sizeof(message));
        recvfrom(sock, message, BUFLEN, 0, NULL, NULL);
        printf("CLIENT: Получено от сервера: %s\n", message);

        sleep(1);
    }

    printf("CLIENT: Пересылка завершена. Счастливо оставаться. \n");
    close(sock);

    return 0;
}

