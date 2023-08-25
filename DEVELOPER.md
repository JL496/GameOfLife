# coms327P2

-----------------------------------------

File name: DEVELOPER.md  
Description: Developer file for Com S 327 Project 2  

Author: Julia Lundstrum  
netid: jlu  

-----------------------------------------

### DEVELOPMENT SETUP

The gitlab repository can be cloned from (https://git.linux.iastate.edu/jlu/coms327p2).

```bash
# Clone the Github repo:
git clone https://git.linux.iastate.edu/jlu/coms327p2.git

# Go to coms327p2 directory:
cd coms327p2
```

-----------------------------------------

### FUNCTIONS

#### ccode.c

##### connect_to
Description: 
Connects to the graphics server at the given port and url  

Parameters:  
char[] url - the URL to connect  
int port - port to connect  

Explanation:  
Uses socket, memset, inet_pton, and connect to establish connection. Throws error if unable to create socket, invalid address, or if the connection fails.  

##### disconnect
Description:  
Shuts down the given socket  

Parameters:  
int sockfd - socket  

Explanation:  
Calls close() to shut down the socket  

##### send_message
Description: Sends a message to the graphics server  

Parameters:  
int sockfd - socket  
char[] val - message to send  
int length - length of message  

Explanation:  
Calls send() to send a message to the graphics server  

#### CellularAutomation.cpp

##### Constructor
Description: Reads files and initializes CellularAutomation  

Parameters:  
string file_name - name of file that contains values for the CA  
int qstate - quiescent state of array  

Explanation:  
Uses ifstream to read file int by int and create new CA with given values.  

##### Constructor
Description: Initializes CellularAutomation to given state  

Parameters:  
int qstate - quiescent state of array  
int row - number of rows  
int col - number of columns  

Explanation:  
Stores given values and loops through to set array to state.   

##### Copy Constructor
Description: Creates a new CA with the same values  

Parameters:  
CellularAutomation& origObject - object to copy  

Explanation:  
Stores given values and loops through to set array to same values.   

##### Assignment = 
Description: Creates a new CA with given parameter  

Parameters:  
CellularAutomation& origObject - object to set to  

Explanation:  
Stores given values and loops through to set array to values.   

##### Destructor
Description: Releases Allocated Resources  

Explanation:  
Delete the cadata array   

##### Step
Description: Performs one step on the CA using the given rule  

Parameters:  
unsigned char (*rule)(CellularAutomation&, int, int) - rule to use  

Explanation:  
Creates a new array to store new values in to preserve original values to calculate with, loops through performing rule on each cell. Uses a for loop to set values to calculated values   

##### display2DCA
Description: Displays current state of the 2DCA  

Parameters:  
GraphicsClient& object - graphics client to display on  

Explanation:  
Uses a switch statement depending on the size of the ca for the size of the boxes. Calls clear from Graphics Client to clear current board, then calls fillRectangle for each cell set to 1.   

##### getRows
Description: returns number of rows since rows are private    

##### getCols
Description: returns number of cols since cols are private    

##### getWrap
Description: returns number of wrap since wrap are private    

##### getValue
Description: returns value of given location since array is private 

##### changeValue
Description: change value of given location  

Explanation: checks cells current value and sets it to the opposite value

#### GraphicsClient.cpp

##### Constructor
Description: Calls connect_to from ccode.c to connect to the graphics server at the given port and url  

Parameters:  
string url_given - the URL to connect  
int port_number - port to connect  

Explanation:  
Calls connect_to from ccode.c and uses the given url and port to establish a connection.  

##### Copy Constructor
Description: Creates a new connection to the same address and port number  

Parameters:  
GraphicsClient& origObject - object to copy  

Explanation:  
Calls connect_to from ccode.c and uses the given url and port to establish a connection.  

##### Operator = Method
Description: Closes existing connect and creates a new connection with given parameters  

Parameters:  
GraphicsClient& origObject - object to set to  

##### Destructor
Description: Releases Allocated Resources  

##### setBackgroundColor
Description: Sets the background color of the display  

Parameters:  
int red - red value for bg color  
int green - green value for bg color  
int blue - blue value for bg color  

Explanation:  
Creates arrays to store hex values, calls function using hex values for each integer, creates array of hex values for message, and then calls send_message from ccode.c to send the message to the server.  

##### setDrawingColor
Description: Sets the drawing color of the display  

Parameters:  
int red - red value for drawing color  
int green - green value for drawing color  
int blue - blue value for drawing color  

Explanation:  
Creates arrays to store hex values, calls function using hex values for each integer, creates array of hex values for message, and then calls send_message from ccode.c to send the message to the server.  

##### Clear
Description: Clears display to background color  

Explanation:  
Creates array of hex values for message, and then calls send_message from ccode.c to send the message to the server.  

##### setPixel
Description: Sets specified pixel to specified color  

Parameters:  
int x - x value of pixel to set  
int y - y value of pixel to set  
int red - red value for drawing color  
int green - green value for drawing color  
int blue - blue value for drawing color  

Explanation:  
Creates arrays to store hex values, calls function using hex values for each integer, creates array of hex values for message, and then calls send_message from ccode.c to send the message to the server.  

##### drawRectangle
Description: Draw rectangle of specified size at specified location  

Parameters:  
int x - x value of rectangle  
int y - y value of rectangle  
int width - width of rectangle  
int height - height of rectangle  

Explanation:  
Creates arrays to store hex values, calls function using hex values for each integer, creates array of hex values for message, and then calls send_message from ccode.c to send the message to the server.  

##### fillRectangle
Description: Draw filled rectangle of specified size at specified location  

Parameters:  
int x - x value of rectangle  
int y - y value of rectangle  
int width - width of rectangle  
int height - height of rectangle  

Explanation:  
Creates arrays to store hex values, calls function using hex values for each integer, creates array of hex values for message, and then calls send_message from ccode.c to send the message to the server.  

##### clearRectangle
Description: Clear rectangle of specified size at specified location  

Parameters:  
int x - x value of rectangle  
int y - y value of rectangle  
int width - width of rectangle  
int height - height of rectangle  

Explanation:  
Creates arrays to store hex values, calls function using hex values for each integer, creates array of hex values for message, and then calls send_message from ccode.c to send the message to the server.  

##### drawOval
Description: Draw oval of specified size at specified location  

Parameters:  
int x - x value of oval  
int y - y value of oval  
int width - width of oval  
int height - height of oval  

Explanation:  
Creates arrays to store hex values, calls function using hex values for each integer, creates array of hex values for message, and then calls send_message from ccode.c to send the message to the server.  

##### fillOval
Description: Draw filled oval of specified size at specified location  

Parameters:  
int x - x value of oval  
int y - y value of oval  
int width - width of oval  
int height - height of oval  

Explanation:  
Creates arrays to store hex values, calls function using hex values for each integer, creates array of hex values for message, and then calls send_message from ccode.c to send the message to the server.  

##### drawLine
Description: Draw line from point a to point b  

Parameters:  
int x - x value for start point  
int y - y value for start point  
int x2 - x value for end point  
int y2 - y value for end point  

Explanation:  
Creates arrays to store hex values, calls function using hex values for each integer, creates array of hex values for message, and then calls send_message from ccode.c to send the message to the server.  

##### drawstring
Description: Draw string starting from given point  

Parameters:  
int x - x value for start point  
int y - y value for start point  
string to_draw - string to draw  

Explanation:  
Creates arrays to store hex values, calls function using hex values for each integer, creates array of hex values for message, and then calls send_message from ccode.c to send the message to the server.  

##### repaint
Description: Send repaint signal to server  

Explanation:  
Creates array of hex values for message, and then calls send_message from ccode.c to send the message to the server.  

##### inttohex
Description: Conver integer to hex number where each char is one bit  

Parameters:  
unsigned char * hex - array to store hex values in  
int num - number to convert  

Explanation:  
Uses shift and remainder operators to get one bit.  

#### main.cpp

##### main
Description:  
creates and initializes a 2DCA based on given inputs. It then prints the current state of the 2DCA after each step

Explanation:  
Takes number of dimensions and file to read in as command line parameters. Prints to stderr and exits upon invalid input. Calls constructor to create structure. Performs step with Conway's Game of Life Rule (conway) each time the user presses enter, displaying the array after each call. 

##### conway
Description:  
Performs Conway's Game of Life on the given cell.  

Parameters:  
CellularAutomation& caobj- pointer to the object   
int x - x index of cell to perform rule on  
int y - y index of cell to perform rule on  

Returns:  
unsigned char of new value for cell  

#### makefile
make: makes an executable program named "main", which runs the main program in main.c  
clean: force removes main

-----------------------------------------

### DOCUMENTATION

#### headers
Headers are included for each file and include the file name, description, author, author's netid, and revision history of the file in the following format:

```c
/*
* File name: 
* Description: 
*
* Author: 
* netid: 
* 
* Revision History (Date: Description):
* 9/21/21: Example
*/
```

#### functions
Each function has documentation that includes the function name, description, and parameters in the following format:

```c
/*
* Function: 
* Description: 
*
* Parameters:
* type name - description
*/
```

#### comments
Comments are included throughout the code to explain what is happening in the format:
```c
// this is a comment
```

---------------------------------------

### FILES

ccode.c  
Contains functions (connect_to, disconnect, send_message) for the graphics server.  

ccode.h  
Header file for ccode.c. Creates prototypes for connect_to, disconnect, and send_message.  

CellularAutomation.cpp
Represents a 2DCA and contains functions for a 2DCA.   

CellularAutomation.h  
Header file for CellularAutomation.cpp.  

GraphicsClient.cpp  
Encapsulates drawing methods that can be made to a graphics server program via network messages  

GraphicsClient.h
Header file for GraphicsClient.cpp  

main.cpp  
creates and initializes a CA based on given inputs. It then prints the current state of the CA after each step. Also contains conway function.  

makefile  
Creates executable program main and contains a clean function that force removes main.  

README.md  
Read me for project. Contains information on project, changelog, functions, known errors and issues, execution, installation, usage, files.

DEVELOPER.md  
Developer file for project. Contains information on development setup, functions, documentation, and files.
