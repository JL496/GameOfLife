/*
* File name: ccode.c
* Description: Connects, disconnects, and sends messages to the graphics server
*
* Author: Julia Lundstrum
* netid: jlu
* 
* Revision History (Date: Description):
* 11/27/21: File created 
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

/*
* Function: connect_to
* Description: Connects to the graphics server at the given port and url
*
* Parameters:
* char[] url - the URL to connect
* int port - port to connect
*/
int connect_to(char url[], int port){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        fprintf( stderr, "Error creating socket\n");
        exit(-1);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, url, &serv_addr.sin_addr)<=0){
        fprintf(stderr, "Invalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        fprintf(stderr, "Connection Failed \n");
        return -1;
    }

    return sockfd;
}

/*
* Function: disconnect
* Description: Shuts down the given socket
*
* Parameters:
* int sockfd - socket
*/
int disconnect(int sockfd){
    close(sockfd);
    return EXIT_SUCCESS;
}

/*
* Function: send_message
* Description: Sends a message to the graphics server
*
* Parameters:
* int sockfd - socket
* char[] val - message to send
* int length - length of message
*/
void send_message(int sockfd, char val[], int length){
    send(sockfd, val, length, 0);
}
