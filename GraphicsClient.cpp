/*
* File name: GraphicsClient.cpp
* Description: Encapsulates drawing methods that can be made to a graphics server program via network messages
*
* Author: Julia Lundstrum
* netid: jlu
* 
* Revision History (Date: Description):
* 11/27/21: File created 
* 12/10/21: Added getSockfd, hextoint, input, button_selection, and getFileName
*/
#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>
using namespace std;

#include "ccode.h"
#include "GraphicsClient.h"

/*
* Function: Constructor
* Description: Calls connect_to from ccode.c to connect to the graphics server at the given port and url
*
* Parameters:
* string url_given - the URL to connect
* int port_number - port to connect
*/
GraphicsClient::GraphicsClient(std::string url_given, int port_number){
    //store values
    port = port_number;
    url = url_given;
    char* to_pass;
    to_pass = &url_given[0];
    // call connect_to from ccode.c
    sfd = connect_to(to_pass, port_number);
}

/*
* Function: Copy Constructor
* Description: Creates a new connection to the same address and port number
*
* Parameters:
* GraphicsClient& origObject - object to copy
*/
GraphicsClient::GraphicsClient(const GraphicsClient& origObject){
    //store values
    port = origObject.port;
    url = origObject.url;
    char* to_pass;
    to_pass = &url[0];
    // call connect_to from ccode.c
    sfd = connect_to(to_pass, port);
}

/*
* Function: Operator = Method
* Description: Closes existing connect and creates a new connection with given parameters
*
* Parameters:
* GraphicsClient& origObject - object to set to
*/
GraphicsClient GraphicsClient::operator=(GraphicsClient obj){
    // call disconnect from ccode.c
    disconnect(sfd);
    GraphicsClient neu = GraphicsClient(obj.url, obj.port);
    return neu;
}

/*
* Function: Destructor
* Description: Releases Allocated Resources
*/
GraphicsClient::~GraphicsClient(){
    disconnect(sfd);
}

/*
* Function: setBackgroundColor
* Description: Sets the background color of the display
*
* Parameters:
* int red - red value for bg color
* int green - green value for bg color
* int blue - blue value for bg color
*/
void GraphicsClient::setBackgroundColor(int red, int green, int blue){
    //create arrays to store hex value in
    unsigned char r[4];
    unsigned char g[4];
    unsigned char b[4];
    // call function to get hex values of each function
    inttohex(r, red);
    inttohex(g, green);
    inttohex(b, blue);
    //put hex numbers in array for the message
    char message[] = {0xFF, 0x00, 0x00, 0x00, 0x07, 0x02, r[2], r[3], g[2], g[3], b[2], b[3]};
    send_message(sfd, message, 12);
}

/*
* Function: setDrawingColor
* Description: Sets the drawing color for the objects
*
* Parameters:
* int red - red value for drawing color
* int green - green value for drawing color
* int blue - blue value for drawing color
*/
void GraphicsClient::setDrawingColor(int red, int green, int blue){
    //create arrays to store hex value in
    unsigned char r[4];
    unsigned char g[4];
    unsigned char b[4];
    // call function to get hex values of each function
    inttohex(r, red);
    inttohex(g, green);
    inttohex(b, blue);
    //put hex numbers in array for the message
    char message[] = {0xFF, 0x00, 0x00, 0x00, 0x07, 0x06, r[2], r[3], g[2], g[3], b[2], b[3]};
    send_message(sfd, message, 12);
}

/*
* Function: Clear
* Description: Clears display to background color
*/
void GraphicsClient::clear(){
    // same hex message everytime
    char message[] = {0xFF, 0x00, 0x00, 0x00, 0x01, 0x01};
    send_message(sfd, message, 6);
}

/*
* Function: setPixel
* Description: Sets specified pixel to specified color
*
* Parameters:
* int x - x value of pixel to set
* int y - y value of pixel to set
* int red - red value for drawing color
* int green - green value for drawing color
* int blue - blue value for drawing color
*/
void GraphicsClient::setPixel(int x, int y, int red, int green, int blue){
    //create arrays to store hex value in
    unsigned char r[4];
    unsigned char g[4];
    unsigned char b[4];
    unsigned char xv[4];
    unsigned char yv[4];
    // call function to get hex values of each function
    inttohex(r, red);
    inttohex(g, green);
    inttohex(b, blue);
    inttohex(xv, x);
    inttohex(yv, y);
    //put hex numbers in array for the message
    char message[] = {0xFF, 0x00, 0x00, 0x00, 0x0F, 0x02, xv[0], xv[1], xv[2], xv[3], yv[0], yv[1], yv[2], yv[3], r[2], r[3], g[2], g[3], b[2], b[3]};
    send_message(sfd, message, 20);
}

/*
* Function: drawRectangle
* Description: Draw rectangle of specified size at specified location
*
* Parameters:
* int x - x value for rectangle
* int y - y value for rectangle
* int width - width of rectangle
* int height - height of rectangle
*/
void GraphicsClient::drawRectangle(int x, int y, int width, int height){
    //create arrays to store hex value in
    unsigned char w[4];
    unsigned char h[4];
    unsigned char xv[4];
    unsigned char yv[4];
    // call function to get hex values of each function
    inttohex(w, width);
    inttohex(h, height);
    inttohex(xv, x);
    inttohex(yv, y);
    //put hex numbers in array for the message
    char message[] = {0xFF, 0x00, 0x00, 0x01, 0x01, 0x07, xv[0], xv[1], xv[2], xv[3], yv[0], yv[1], yv[2], yv[3], w[0], w[1], w[2], w[3], h[0], h[1], h[2], h[3]};
    send_message(sfd, message, 22);
}

/*
* Function: fillRectangle
* Description: Draw filled rectangle of specified size at specified location
*
* Parameters:
* int x - x value for rectangle
* int y - y value for rectangle
* int width - width of rectangle
* int height - height of rectangle
*/
void GraphicsClient::fillRectangle(int x, int y, int width, int height){
    //create arrays to store hex value in
    unsigned char w[4];
    unsigned char h[4];
    unsigned char xv[4];
    unsigned char yv[4];
    // call function to get hex values of each function
    inttohex(w, width);
    inttohex(h, height);
    inttohex(xv, x);
    inttohex(yv, y);
    //put hex numbers in array for the message
    char message[] = {0xFF, 0x00, 0x00, 0x01, 0x01, 0x08, xv[0], xv[1], xv[2], xv[3], yv[0], yv[1], yv[2], yv[3], w[0], w[1], w[2], w[3], h[0], h[1], h[2], h[3]};
    send_message(sfd, message, 22);
}

/*
* Function: clearRectangle
* Description: Clears rectangle of specified size at specified location
*
* Parameters:
* int x - x value for rectangle
* int y - y value for rectangle
* int width - width of rectangle
* int height - height of rectangle
*/
void GraphicsClient::clearRectangle(int x, int y, int width, int height){
    //create arrays to store hex value in
    unsigned char w[4];
    unsigned char h[4];
    unsigned char xv[4];
    unsigned char yv[4];
    // call function to get hex values of each function
    inttohex(w, width);
    inttohex(h, height);
    inttohex(xv, x);
    inttohex(yv, y);
    //put hex numbers in array for the message
    char message[] = {0xFF, 0x00, 0x00, 0x01, 0x01, 0x09, xv[0], xv[1], xv[2], xv[3], yv[0], yv[1], yv[2], yv[3], w[0], w[1], w[2], w[3], h[0], h[1], h[2], h[3]};
    send_message(sfd, message, 22);
}

/*
* Function: drawOval
* Description: Draw oval of specified size at specified location
*
* Parameters:
* int x - x value for oval
* int y - y value for oval
* int width - width of oval
* int height - height of oval
*/
void GraphicsClient::drawOval(int x, int y, int width, int height){
    //create arrays to store hex value in
    unsigned char w[4];
    unsigned char h[4];
    unsigned char xv[4];
    unsigned char yv[4];
    // call function to get hex values of each function
    inttohex(w, width);
    inttohex(h, height);
    inttohex(xv, x);
    inttohex(yv, y);
    //put hex numbers in array for the message
    char message[] = {0xFF, 0x00, 0x00, 0x01, 0x01, 0x0A, xv[0], xv[1], xv[2], xv[3], yv[0], yv[1], yv[2], yv[3], w[0], w[1], w[2], w[3], h[0], h[1], h[2], h[3]};
    send_message(sfd, message, 22);
}

/*
* Function: fillOval
* Description: Draw filled oval of specified size at specified location
*
* Parameters:
* int x - x value for oval
* int y - y value for oval
* int width - width of oval
* int height - height of oval
*/
void GraphicsClient::fillOval(int x, int y, int width, int height){
    //create arrays to store hex value in
    unsigned char w[4];
    unsigned char h[4];
    unsigned char xv[4];
    unsigned char yv[4];
    // call function to get hex values of each function
    inttohex(w, width);
    inttohex(h, height);
    inttohex(xv, x);
    inttohex(yv, y);
    //put hex numbers in array for the message
    char message[] = {0xFF, 0x00, 0x00, 0x01, 0x01, 0x0B, xv[0], xv[1], xv[2], xv[3], yv[0], yv[1], yv[2], yv[3], w[0], w[1], w[2], w[3], h[0], h[1], h[2], h[3]};
    send_message(sfd, message, 22);
}

/*
* Function: drawLine
* Description: Draw line from point a to point b
*
* Parameters:
* int x - x value for start point
* int y - y value for start point
* int x2 - x value for end point
* int y2 - y value for end point
*/
void GraphicsClient::drawLine(int x, int y, int x2, int y2){
    //create arrays to store hex value in
    unsigned char x2v[4];
    unsigned char y2v[4];
    unsigned char xv[4];
    unsigned char yv[4];
    // call function to get hex values of each function
    inttohex(x2v, x2);
    inttohex(y2v, y2);
    inttohex(xv, x);
    inttohex(yv, y);
    //put hex numbers in array for the message
    char message[] = {0xFF, 0x00, 0x00, 0x01, 0x01, 0x0D, xv[0], xv[1], xv[2], xv[3], yv[0], yv[1], yv[2], yv[3], x2v[0], x2v[1], x2v[2], x2v[3], y2v[0], y2v[1], y2v[2], y2v[3]};
    send_message(sfd, message, 22);
}

/*
* Function: drawstring
* Description: Draw string starting from given point
*
* Parameters:
* int x - x value for start point
* int y - y value for start point
* string to_draw - string to draw
*/
void GraphicsClient::drawstring(int x, int y, string to_draw){
    //create arrays to store hex value in
    unsigned char xv[4];
    unsigned char yv[4];
    // call function to get hex values of each function
    inttohex(xv, x);
    inttohex(yv, y);
    int slen = 2*to_draw.length();
    int len = slen + 9; //twice the length since each character takes up two values plus 4 x values, 4 y values, and type
    int totlen = len + 5; //plus 5 for the ones that aren't included in that hex (0xFF and length)
    unsigned char l[4];
    inttohex(l, len);
    char message[totlen];
    //put hex numbers in array for the message
    message[0] = 0xFF;
    message[1] = l[0];
    message[2] = l[1];
    message[3] = l[2];
    message[4] = l[3];
    message[5] = 0x05;
    message[6] = xv[0];
    message[7] = xv[1];
    message[8] = xv[2];
    message[9] = xv[3];
    message[10] = yv[0];
    message[11] = yv[1];
    message[12] = yv[2];
    message[13] = yv[3];
    //loop through string to get hex value of each character
    for(int i = 0; i < to_draw.length(); i++){
        int ch = int(to_draw[i]);
        unsigned char temp[4];
        inttohex(temp, ch);
        message[2*i + 14] = temp[2];
        message[2*i + 15] = temp[3];
    }
    send_message(sfd, message, totlen);
}

/*
* Function: repaint
* Description: Send repaint signal to server
*/
void GraphicsClient::repaint(){
    //same message everytime
    char message[] = {0xFF, 0x00, 0x00, 0x00, 0x01, 0x0C};
    send_message(sfd, message, 6);
}

/*
* Function: inttohex
* Description: Conver integer to hex number where each char is one bit
*
* Parameters:
* unsigned char * hex - array to store hex values in 
* int num - number to convert
*/
void GraphicsClient::inttohex(unsigned char* hex, int num){
    unsigned char a = num >> 12;
    unsigned char b = (num >> 8) % 16;
    unsigned char c = (num >> 4) % 16;
    unsigned char d = (num >> 0) % 16;
    hex[0] = a;
    hex[1] = b;
    hex[2] = c;
    hex[3] = d;
}

/*
* Function: getSockfd
* Description: Returns sockfd
*/
int GraphicsClient::getSockfd(){
    return sfd;
}

/*
* Function: inttohex
* Description: Conver integer to hex number where each char is one bit
*
* Parameters:
* unsigned char * hex - array to store hex values in 
* int num - number to convert
*/
int GraphicsClient::hextoint(unsigned char hex[]){
    int a = hex[0] << 12;
    int b = hex[1] << 8;
    int c = hex[2] << 4;
    int d = hex[3];
    int ret = a + b + c + d;
    return ret;
}

/*
* Function: input
* Description: Checks length of message, if input is a mouse click or file path, and calls appropriate functions.
*
* Parameters:
* char arr[] - array with message receive
* int count - length of total message
*/
int GraphicsClient::input(char arr[], int count){
    unsigned char length[] = {arr[1], arr[2], arr[3], arr[4]};
    int flength = hextoint(length);
    int code = flength-2;
    char message[code];
    char filep[flength];
    string fp = "";
    int ret = 0;
    int j = 0;
    int bs;
    switch(arr[5]){
        case 0x01:
            for(int i = 0; i < code; i++){
                message[i] = arr[i+7];
            }
            ret = button_selection(message);
            return ret;
            break;
        case 0x0E:
        case 0x0A:
            for(int i = 6; i < flength+4; i +=2){
                filep[j] = (arr[i]<<4)&0x00F0;
                filep[j] |= arr[i+1]&0x000F;
                fp += filep[j];
                j++;
            }
            bs = fp.find_last_of("/") + 1;
            fn = fp.substr(bs);
            return 13;
            break;
        default:
            for(int i = 0; i < code+2; i++){
                ret = arr[i];
            }
            break;
    }
    return ret;
}

/*
* Function: button_selection
* Description: Checks what button user was pressing based on x and y coordinates and calls appropriate functions.
*
* Parameters:
* char arr[] - array with x and y
*/
int GraphicsClient::button_selection(char arr[]){
    unsigned char x[] = {arr[0], arr[1], arr[2], arr[3]};
    unsigned char y[] = {arr[4], arr[5], arr[6], arr[7]};
    int xcord = hextoint(x);
    int ycord = hextoint(y);
    if(xcord < 600){
        return 11;
    }
    if(ycord >= 410 && ycord <= 440){
        if(xcord >= 645 && xcord <= 675){
            return 1;
        }
        if(xcord >= 685 && xcord <= 715){
            return 2;
        }
        if(xcord >= 725 && xcord <= 755){
            return 3;
        }
    }
    if(!(xcord >= 655 && xcord <= 745)){
        return 0;
    }
    char message[] = {0xFF, 0x00, 0x00, 0x00, 0x01, 0x0E};
    switch(ycord){
        case 15 ... 45:
            return 4;
            break;
        case 60 ... 90:
            return 5;
            break;
        case 105 ... 135:
            return 6;
            break;
        case 150 ... 180:
            return 7;
            break;
        case 195 ... 225:
            return 8;
            break;
        case 240 ... 270:
            send_message(sfd, message, 6);
            return 9;
            break;
        case 285 ... 315:
            return 10;
            break;
        case 330 ... 360:
            return 12;
            break;
        default:
            return 0;
            break;
    }
}

/*
* Function: getFileName
* Description: Returns file name so it can be used in the main function
*/
string GraphicsClient::getFileName(){
    return fn;
}
