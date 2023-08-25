/*
* File name: main.cpp
* Description: Main program
*
* Author: Julia Lundstrum
* netid: jlu
* 
* Revision History (Date: Description):
* 11/27/21: File created 
* 12/10/21: Added user interface and receiving messages from the server
*/
#include <iostream>
using namespace std;

#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include "ccode.h"
#include "GraphicsClient.h"
#include "CellularAutomation.h"

int main(int argc, char* argv[]){
    string fname = argv[1];
    //creates cellular automation reading the given file from the command line
    CellularAutomation ca = CellularAutomation(fname, 0);
    unsigned char conway(CellularAutomation&, int, int);
    void input(char arr[], int count);

    GraphicsClient gc = GraphicsClient("127.0.0.1", 7777);
    //display ca in current state
    ca.display2DCA(gc);

    gc.setDrawingColor(9,137,217);
    gc.fillRectangle(600, 0, 200, 600);
    gc.setDrawingColor(133,208,250);
    gc.fillRectangle(655, 15, 90, 30);
    gc.fillRectangle(655, 60, 90, 30);
    gc.fillRectangle(655, 105, 90, 30);
    gc.fillRectangle(655, 150, 90, 30);
    gc.fillRectangle(655, 195, 90, 30);
    gc.fillRectangle(655, 240, 90, 30);
    gc.fillRectangle(655, 285, 90, 30);
    gc.fillRectangle(655, 330, 90, 30);
    gc.drawstring(655, 400, "SELECT SIZE");
    gc.fillRectangle(645, 410, 30, 30);
    gc.fillRectangle(685, 410, 30, 30);
    gc.fillRectangle(725, 410, 30, 30);
    gc.setDrawingColor(255,255,255);
    gc.drawstring(685, 35, "STEP");
    gc.drawstring(685, 80, "RUN");
    gc.drawstring(680, 125, "PAUSE");
    gc.drawstring(680, 170, "RESET");
    gc.drawstring(675, 215, "RANDOM");
    gc.drawstring(685, 260, "LOAD");
    gc.drawstring(685, 305, "QUIT");
    gc.drawstring(680, 350, "CLEAR");
    gc.drawstring(655, 430, "1");
    gc.drawstring(695, 430, "2");
    gc.drawstring(735, 430, "3");

    int sockfd = gc.getSockfd();

    struct timespec time1;
    time1.tv_sec = 1;
    time1.tv_nsec = 100000000L;

    int ex = 0;
    int in = 0;
    int count = 0;
    char buff[300];
    int choice = 0;
    int size = 40;
    int run = 0;
    int xval, yval;
    unsigned char x[4];
    unsigned char y[4];

    while(ex == 0){
        //printf("Press Enter to Perform a Step.");
        if(run == 1){
            nanosleep(&time1, &time1);
            ca.step(conway);
            ca.display2DCA(gc);
        }
        ioctl(sockfd, FIONREAD, &count);
        if(count > 0){
            read(sockfd, buff, count);
            choice = gc.input(buff, count);
            switch(choice){
                case 1:
                    size = 40;
                    break;
                case 2:
                    size = 150;
                    break;
                case 3:
                    size = 600;
                    break;
                case 4:
                    ca.step(conway);
                    ca.display2DCA(gc);
                    break;
                case 5:
                    run = 1;
                    break;
                case 6:
                    run = 0;
                    break;
                case 7:
                    ca = CellularAutomation(fname, 0);
                    ca.display2DCA(gc);
                    break;
                case 8:
                    ca = CellularAutomation(-1, size, size);
                    ca.display2DCA(gc);
                    break;
                case 9:
                    break;
                case 10:
                    ex = 1;
                    break;
                case 11:
                    x[0] = buff[7];
                    x[1] = buff[8];
                    x[2] = buff[9];
                    x[3] = buff[10];
                    y[0] = buff[11];
                    y[1] = buff[12];
                    y[2] = buff[13];
                    y[3] = buff[14];
                    xval = gc.hextoint(x);
                    yval = gc.hextoint(y);
                    ca.changeValue(xval,yval);
                    ca.display2DCA(gc);
                    break;
                case 12:
                    printf("12!!\n");
                    gc.clearRectangle(0,0,600,600);
                    break;
                case 13:
                    fname = gc.getFileName();
                    ca = CellularAutomation(fname, 0);
                    ca.display2DCA(gc);
                    break;
                default:
                    break;
            }
        }
    }
    gc.~GraphicsClient();
    return EXIT_SUCCESS;
}

/*
* Function: conway
* Description: 
* performs Conway's Game of Life on the given cell
*
* Parameters:
* CellularAutomation& caobj- pointer to the object
* int x - column index of cell to perform rule on
* int y - row index of cell to perform rule on
*
* Returns:
* unsigned char of new value for cell
*/
unsigned char conway(CellularAutomation& caobj, int x, int y){
    int neighbors = 0;
    int before_index, after_index, above_index, below_index;
    if(!(caobj.getWrap() == 0 && x == 0)){
        before_index = ((x - 1)+caobj.getCols())%caobj.getCols();
        int before_value = caobj.getValue(before_index,y);
        if(before_value == 1){
            neighbors++;
        }
    }
    if(!(caobj.getWrap() == 0 && x == caobj.getCols() - 1)){
        after_index = ((x + 1)+caobj.getCols())%caobj.getCols();
        int after_value = caobj.getValue(after_index,y);
        if(after_value == 1){
            neighbors++;
        }
    }
     if(!(caobj.getWrap() == 0 && y == 0)){
        above_index = ((y - 1)+caobj.getRows())%caobj.getRows();
        int above_value = caobj.getValue(x,above_index);
        if(above_value == 1){
            neighbors++;
        }
    }
    if(!(caobj.getWrap() == 0 && y == caobj.getRows() - 1)){
        below_index = ((y + 1)+caobj.getRows())%caobj.getRows();
        int below_value = caobj.getValue(x,below_index);
        if(below_value == 1){
            neighbors++;
        }
    }
    if(!(caobj.getWrap() == 0 && (y == 0 || x == 0))){
        int ul_value = caobj.getValue(before_index,above_index);
        if(ul_value == 1){
            neighbors++;
        }
    }
    if(!(caobj.getWrap() == 0 && (y == 0 || x == caobj.getCols() - 1))){
        int ur_value = caobj.getValue(after_index,above_index);
        if(ur_value == 1){
            neighbors++;
        }
    }
    if(!(caobj.getWrap() == 0 && (y == caobj.getRows() - 1 || x == 0))){
        int ll_value = caobj.getValue(before_index,below_index);
        if(ll_value == 1){
            neighbors++;
        }
    }
    if(!(caobj.getWrap() == 0 && (y == caobj.getRows() - 1 || x == caobj.getCols() - 1))){
        int lr_value = caobj.getValue(after_index,below_index);
        if(lr_value == 1){
            neighbors++;
        }
    }
    if(neighbors == 3){
        return 1;
    }
    int value = caobj.getValue(x,y);
    if(value == 1 && neighbors == 2){
        return 1;
    }
    return 0;
}
