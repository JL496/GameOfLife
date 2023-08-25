/*
* File name: CellularAutomation.cpp
* Description: Represents a 2DCA
*
* Author: Julia Lundstrum
* netid: jlu
* 
* Revision History (Date: Description):
* 11/27/21: File created 
* 12/10/21: Added changeValue
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

#include "ccode.h"
#include "GraphicsClient.h"
#include "CellularAutomation.h"

/*
* Function: Constructor
* Description: Reads files and initializes CellularAutomation
*
* Parameters:
* string file_name - name of file that contains values for the CA
* int qstate - quiescent state of array
*/
CellularAutomation::CellularAutomation(std::string file_name, int qstate){
    ifstream file;
    // opens given file
    file.open(file_name);
    // first value in file is number of rows
    file >> rows;
    // second value in file is number of columns
    file >> cols;
    // allocate space for an array of pointers
    cadata = new int*[cols];
    // allocate space for each array
    for (int i = 0; i < cols; i++){
        cadata[i] = new int[rows];
    }
    // loop through file and store values
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            file >> cadata[j][i];
        }
    }
    // close file
    file.close();
    // store given state and set wrap to true;
    state = qstate;
    wrap = 1;
}

/*
* Function: Constructor
* Description: Initializes CellularAutomation to given state
*
* Parameters:
* int qstate - quiescent state of array
* int row - number of rows
* int col - number of columns
*/
CellularAutomation::CellularAutomation(int qstate, int row, int col){
    //set values to given values
    rows = row;
    cols = col;
    state = qstate;
    wrap = 1;
    // allocate space for an array of pointers
    cadata = new int*[cols];
    // allocate space for each array
    for (int i = 0; i < cols; i++){
        cadata[i] = new int[rows];
    }
    int set_to = qstate;
    // loop through and set values to state
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(qstate == -1){
                set_to = rand()%2;
            }
            cadata[j][i] = set_to;
        }
    }
}

/*
* Function: Copy Constructor
* Description: Creates a new CA with the same values
*
* Parameters:
* CellularAutomation& origObject - object to copy
*/
CellularAutomation::CellularAutomation(const CellularAutomation& origObject){
    // copy values
    rows = origObject.rows;
    cols = origObject.cols;
    state = origObject.state;
    wrap = origObject.wrap;
    // allocate space for an array of pointers
    cadata = new int*[cols];
    // allocate space for each array
    for (int i = 0; i < cols; i++){
        cadata[i] = new int[rows];
    }
    // loop through array and set values
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cadata[j][i] = origObject.cadata[j][i];
        }
    }
}

/*
* Function: Assignment =
* Description: Creates a new CA with given parameters
*
* Parameters:
* CellularAutomation& origObject - object to set to
*/
CellularAutomation CellularAutomation::operator=(CellularAutomation obj){
    rows = obj.rows;
    cols = obj.cols;
    state = obj.state;
    wrap = obj.wrap;
    // allocate space for an array of pointers
    cadata = new int*[cols];
    // allocate space for each array
    for (int i = 0; i < cols; i++){
        cadata[i] = new int[rows];
    }
    // loop through array and set values
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cadata[j][i] = obj.cadata[j][i];
        }
    }
    return *this;
}


/*
* Function: Destructor
* Description: Releases Allocated Resources
*/
CellularAutomation::~CellularAutomation(){
    for (int i = 0; i < cols; i++){
        delete[] cadata[i];
    }
    delete[] cadata;
}

/*
* Function: Step
* Description: Performs one step on the CA using the given rule
*
* Parameters:
* unsigned char (*rule)(CellularAutomation&, int, int) - rule to use
*/
void CellularAutomation::step(unsigned char (*rule)(CellularAutomation&, int, int)){
    int neu[cols][rows];
    // use rule on each cell, storing the new value in the new array
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            neu[j][i] = rule(*this, j, i);            
        }
    }
    // set each array value to its new value
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cadata[j][i] = neu[j][i];            
        }
    }
}

/*
* Function: display2DCA
* Description: Displays current state of the 2DCA
*
* Parameters:
* GraphicsClient& object - graphics client to display on 
*/
void CellularAutomation::display2DCA(GraphicsClient& object){
    int max = rows;
    if (cols > rows){
        max = cols;
    }
    int wid, cg = 0;
    // sets cell size and size between boxes based on the number of rows/cols (whichever is greater)
    switch(max){
        case 201 ... 600:
            wid = 1;
            xm = 1;
            break;
        case 101 ... 200:
            wid = 2;
            xm = 3;
            cg = 1;
            break;
        case 51 ... 100:
            wid = 4;
            xm = 5;
            cg = 1;
            break;
        case 1 ... 50:
            wid = 10;
            xm = 12;
            cg = 2;
            break;
        default:
            break;
    }
    int heig = wid*rows + cg*(rows-1);
    int widt = wid*cols + cg*(cols-1);
    width = widt;
    height = heig;
    object.clearRectangle(0,0,widt, heig);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(cadata[j][i] == 1){
                object.fillRectangle(j*xm, i*xm, wid, wid);
            }           
        }
    }
    object.repaint();
}

/*
* Function: getRows
* Description: returns number of rows since rows are private
*/
int CellularAutomation::getRows(){
    return rows;
}

/*
* Function: getCols
* Description: returns number of cols since cols are private
*/
int CellularAutomation::getCols(){
    return cols;
}

/*
* Function: getWrap
* Description: returns wrap since wrap is private
*/
unsigned char CellularAutomation::getWrap(){
    return wrap;
}

/*
* Function: getValue
* Description: returns value of given location since array is private
*/
int CellularAutomation::getValue(int x, int y){
    return cadata[x][y];
}

/*
* Function: changeValue
* Description: change value of given location
*/
void CellularAutomation::changeValue(int x, int y){
    if(x < width && y < height){
        int xloc = x/xm;
        int yloc = y/xm;
        int current = cadata[xloc][yloc];
        if(current == 0){
            cadata[xloc][yloc] = 1;
        } else{
            cadata[xloc][yloc] = 0;
        }
    }
}
