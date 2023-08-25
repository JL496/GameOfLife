/*
* File name: ccode.h
* Description: header that creates a prototype for ccode
*
* Author: Julia Lundstrum
* netid: jlu
* 
* Revision History (Date: Description):
* 11/27/21: File created 
*/
#ifndef CCODE_H_
#define CCODE_H_

// creates prototype for connect
int connect_to(char url[], int port);
// creates prototype for disconnect
int disconnect(int sockfd);
// creates prototype for send_message
void send_message(int sockfd, char val[], int length);

#endif /* CCODE_H_ */
