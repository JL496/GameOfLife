# coms327P1

-----------------------------------------

File name: README.md  
Description: ReadMe for Com S 327 Project 2  

Author: Julia Lundstrum  
netid: jlu  

-----------------------------------------

### README
coms327P2 is a project on cellular automata. This project was created for Com S 327: Advanced Programming Techniques in Fall 2021.

-----------------------------------------

### CHANGELOG
11/27/21 - ccode.c, ccode.c, CellularAutomation.cpp, CellularAutomation.h, DEVELOPER.md, GraphicsClient.cpp, GraphicsClient.h, main.cpp, makefile, and README.md created
12/10/21 - Added user interface and receiving messages from the server

-----------------------------------------

### FUNCTIONS

#### ccode.cpp
connect_to: Connects to the graphics server at the given port and url   
disconnect: Shuts down the given socket  
send_message: Sends a message to the graphics server  

#### CellularAutomation.cpp
constructor: Reads files and initializes CellularAutomation  
constructor: Initializes CellularAutomation to given state  
Copy Constructor: Creates a new CA with the same values  
Assignment =: Creates a new CA with given parameters  
Destructor: Releases Allocated Resources  
Step: Performs one step on the CA using the given rule  
display2DCA: Displays current state of the 2DCA  
getRows: returns number of rows since rows are private  
getCols: returns number of cols since cols are private  
getWrap: returns wrap since wrap is private  
getValue: returns value of given location since array is private  
changeValue: change value of given location  

#### GraphicsClient.cpp
Constructor: Calls connect_to from ccode.c to connect to the graphics server at the given port and url  
Copy Constructor: Creates a new connection to the same address and port number  
Operator = Method: Closes existing connect and creates a new connection with given parameters  
Destructor: Releases Allocated Resources  
setBackgroundColor: Sets the background color of the display  
setDrawingColor: Sets the drawing color for the objects  
Clear: Clears display to background color  
setPixel: Sets specified pixel to specified color  
drawRectangle: Draw rectangle of specified size at specified location  
fillRectangle: Draw filled rectangle of specified size at specified location  
clearRectangle: Clears rectangle of specified size at specified location  
drawOval: Draw oval of specified size at specified location  
fillOval: Draw filled oval of specified size at specified location  
drawLine: Draw line from point a to point b  
drawstring: Draw string starting from given point  
repaint: Send repaint signal to server  
inttohex: Conver integer to hex number where each char is one bit  
getSockfd: Returns sockfd  
input: Checks length of message, if input is a mouse click or file path, and calls appropriate functions  
button_selection: Checks what button user was pressing based on x and y coordinates and calls appropriate functions  
getFileName: Returns file name so it can be used in the main function

#### main.cpp
main: creates and initializes a CA based on given inputs. It then prints the current state of the CA after each step  
conway: performs Conway's Game of Life on the given cell  

#### makefile
make: makes an executable program named "main", which runs the main program in main.c  
clean: force removes main

-----------------------------------------

### KNOWN ERRORS AND ISSUES
There are no known errors or issues at this time.

-----------------------------------------

### EXECUTION
Typing make in the top directory will make an executable program named "gol", which runs the main program in main.c.

```bash
make
#executes file reading file test.txt
./main test.txt
```

-----------------------------------------

### INSTALLATION
The gitlab repository can be cloned from (https://git.linux.iastate.edu/jlu/coms327p2).

```bash
git clone https://git.linux.iastate.edu/jlu/coms327p2.git
```

-----------------------------------------

### USAGE

```c
#include "ccode.h"

//connect to graphics server
int sock = connect_to("127.0.0.1", 7777);

//send message to the server
char message[] = {0xFF, 0x00, 0x00, 0x00, 0x07, 0x02};
send_message(sock, message, 6);

//disconnect from graphics server
disconnect(sock);
```

```cpp
#include "CellularAutomation.cpp"
#include "GraphicsClient.h"
unsigned char conway(CellularAutomation&, int, int);

//creates ca reading test.txt
CellularAutomation ca = CellularAutomation("test.txt", 0);

//Creates a connection to the graphics server
GraphicsClient gc = GraphicsClient("127.0.0.1", 7777);

//performs a step using the conway function
ca.step(conway);

//display current state of CA
ca.display2DCA(gc);

//sets background color to blue
gc.setBackgroundColor(0, 0, 255);

//sets drawing color to green
gc.setDrawingColor(0, 255, 0);

//sets pixel (4, 5) to red
gc.setPixel(4, 5, 255, 0, 0);

//draws a 7 by 8 rectangle at (9,9)
gc.drawRectangle(9,9,7,8);

//draws a 12 by 8 filled rectangle at (3,5)
gc.fillRectangle(3,5,12,8);

//clears a 12 by 8 rectangle at (3,5)
gc.clearRectangle(3,5,12,8);

//clears board
gc.clear();

//draws a 7 by 8 oval at (9,9)
gc.drawOval(9,9,7,8);

//draws a 12 by 8 filled oval at (3,5)
gc.fillOval(3,5,12,8);

//draws a line from (4,4) to (8,8)
gc.drawLine(4,4,8,8);

//draws the string "hello world!" at (10,9)
gc.drawstring(10,9,"hello world!");

//sends repaint signal
gc.repaint();

// calls destructor
gc.~GraphicsClient();
```

-----------------------------------------

### FILES

ccode.c  
ccode.h  
CellularAutomation.cpp  
CellularAutomation.h
GraphicsClient.cpp
GraphicsClient.h
main.cpp  
makefile  
DEVELOPER.md

