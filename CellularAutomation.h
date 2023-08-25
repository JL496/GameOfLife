/*
* File name: CellularAutomation.h
* Description: header for CellularAutomation.cpp
*
* Author: Julia Lundstrum
* netid: jlu
* 
* Revision History (Date: Description):
* 11/27/21: File created 
* 12/10/21: Added changeValue
*/
#ifndef CELLULARAUTOMATION_H_
#define CELLULARAUTOMATION_H_

class CellularAutomation{
    public:
        CellularAutomation(std::string, int);
        CellularAutomation(int, int, int);
        CellularAutomation(){};
        CellularAutomation(const CellularAutomation& origObject);
        CellularAutomation operator=(CellularAutomation obj);
        ~CellularAutomation();
        void step(unsigned char (*rule)(CellularAutomation&, int, int));
        void display2DCA(GraphicsClient& origObject);
        int getRows();
        int getCols();
        unsigned char getWrap();
        int getValue(int x, int y);
        void changeValue(int x, int y);
    private:
        int rows;
        int cols;
        int width;
        int height;
        int xm;
        int **cadata;
        int state;
        unsigned char wrap;
};

#endif /* CELLULARAUTOMATION_H_ */

