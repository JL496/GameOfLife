# File name: makefile
# Description: creates executable program main
#
# Author: Julia Lundstrum
# netid: jlu
# 
# Revision History (Date: Description):
# 11/27/21: File created 

CFILES   = $(wildcard *.c)
CPPFILES = $(wildcard *.cpp)
OBJFILES = $(CFILES:.c=.o) $(CPPFILES:.cpp=.o)
OUT      = main

CC = g++

#creates executable file main
$(OUT): $(OBJFILES)

.PHONY: clean
#force removes main
clean:
	rm -f $(OBJFILES) $(OUT)