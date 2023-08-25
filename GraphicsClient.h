/*
* File name: GraphicsClient.h
* Description: header file for GraphicsClient.cpp
*
* Author: Julia Lundstrum
* netid: jlu
* 
* Revision History (Date: Description):
* 11/27/21: File created 
* 12/10/21: Added getSockfd, hextoint, input, button_selection, and getFileName
*/
#ifndef GRAPHICSCLIENT_H_
#define GRAPHICSCLIENT_H_

class GraphicsClient{
    public:
        GraphicsClient(std::string, int);
        GraphicsClient(const GraphicsClient& origObject);
        ~GraphicsClient();
        GraphicsClient operator=(GraphicsClient obj);
        void setBackgroundColor(int red, int green, int blue);
        void setDrawingColor(int red, int green, int blue);
        void clear();
        void setPixel(int x, int y, int red, int green, int blue);
        void drawRectangle(int x, int y, int width, int height);
        void fillRectangle(int x, int y, int width, int height);
        void clearRectangle(int x, int y, int width, int height);
        void drawOval(int x, int y, int width, int height);
        void fillOval(int x, int y, int width, int height);
        void drawLine(int x, int y, int x2, int y2);
        void drawstring(int x, int y, string to_draw);
        void repaint();
        void inttohex(unsigned char* hex, int num);
        int getSockfd();
        int hextoint(unsigned char hex[]);
        int input(char arr[], int count);
        int button_selection(char arr[]);
        string getFileName();
    private:
        int port;
        int sfd;
        string fn;
        string url;
};

#endif /* GRAPHICSCLIENT_H_ */
