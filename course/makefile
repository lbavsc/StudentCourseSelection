# A simple Makefile for lib(libxxx.a)  
# By Late Lee(httpwww.latelee.org)  
AR = ar
ARFLAGS = cr
RM = -rm -rf
INCLUDE_DIR = ../include
CFLAGS = -I$(INCLUDE_DIR) -g 
LIB = libcourse.a
CC = gcc
objects := $(patsubst %.c,%.o,$(wildcard *.c))  
$(objects) : %.o: %.c  %.h
	gcc -c $(CFLAGS) $< -o $@  

all:$(LIB)
$(LIB):$(objects)
	$(AR) $(ARFLAGS) $@ $(objects);cp $(LIB) ../release/
clean:
	$(RM) $(LIB) $(objects)
.PHONY: all clean
