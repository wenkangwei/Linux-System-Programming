# Makefile
# Wenkang Wei
# wenkanw
# ECE222 section 1, fall 2017
# MP2
# 
# Purpose:
# 	This file is to use make to compile all files of the mp2 program
TOP=./
MAKE=gcc
SRC=lab2.c lab2_funcs.c
OBJ=lab2_funcs.o lab2.o 
EXEC=lab2
INCLUDE+=$(TOP)/*.h


lab2: $(OBJ)
	
	$(MAKE) $(OBJ) -o $(EXEC) -Wall
	rm -f $(OBJ)
 
$(filter %.o,$(OBJ)): %.o : %.c 
	$(MAKE) -c $< -o $@

.PHONY:clean 

clean:
	rm -f $(OBJ)
	rm -f $(EXEC)



