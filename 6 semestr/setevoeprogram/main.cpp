#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h> 
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#define BUFLEN 81
 int main() {
	int sockMain, msgLength;
	socklen_t length;
	struct sockaddr_in servAddr, clientAddr;
	char buf[BUFLEN];
	if(( sockMain = socket( AF_INET, SOCK_DGRAM, 0 ) ) < 0 )
	{ 
		perror("Сервер не может открыть socket для UDP.");
		exit(1);
	}
	memset(&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl( INADDR_ANY );
	servAddr.sin_port = 0;
	
	if (bind( sockMain, (struct sockaddr *) &servAddr, sizeof(servAddr)))
	{ 
		perror("Связывание сервера неудачно.");
		exit(1);
	}
	length = sizeof( servAddr ) ;
	if ( getsockname( sockMain,(struct sockaddr*)  &servAddr, &length ) )
	{ 
		perror("Вызов getsockname неудачен.");
		exit(1);
	}
	printf( "СЕРВЕР: номер порта - % d\n", ntohs(servAddr.sin_port ));
	for( ; ; ) {
		length = sizeof( clientAddr );
		bzero( buf, sizeof( BUFLEN) );
		if ((msgLength = recvfrom( sockMain, buf, BUFLEN, 0, (struct sockaddr*) &clientAddr, &length) ) < 0 )
        { 
			perror("Плохой socket клиента.");
			exit(1);
		}
		printf( "SERVER: IP адрес клиента: %s\n", inet_ntoa(clientAddr.sin_addr) ) ;
		printf( "SERVER: PORT клиента: %d\n", ntohs(clientAddr.sin_port) ) ;
		printf( "SERVER: Длина сообщения - %d\n", msgLength);
		printf( "SERVER: Сообщение: %s\n\n", buf);
		}
	}


