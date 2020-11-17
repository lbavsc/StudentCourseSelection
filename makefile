#################################################################  
# A simple Makefile  
# By Late Lee(http://www.latelee.org)  

#   
# bugs:  
#      1. 需要显式指定库位置、名称；  
#      2. make 及 make clean处理得不好(对于库，要么删除再编译，要么无操作)；  


#################################################################  

#ROOT = .
INCLUDE_DIR = $(ROOT)/include

export INCLUDE_DIR
#libs value depends on product type
#LIBS := libadd.a libafteradd.a 
LIBS := $(LIBS_ENV)

#LIBS := $(subst %:%, % %, $(LIBS_ENV))
CC=gcc
CFLAGS = -I$(INCLUDE_DIR) -g -L./release

SUBDIRS := $(ROOT)/course $(ROOT)/menu $(ROOT)/log $(ROOT)/student 
SOURCES := $(wildcard *.c)
CHEADERS := $(wildcard *.h)

objects := $(patsubst %.c,%.o,$(wildcard *.c))  




RM = rm -rf

target = main


MAKE = make
  
all: $(target)

$(objects) : %.o: %.c
	$(CROSS_COMPILE)gcc -c $(CFLAGS) $< -o $@  

$(target): $(objects)
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir all || exit 1; done
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@ 

clean:
	@for dir in $(SUBDIRS); do make -C $$dir clean|| exit 1; done
	$(RM) $(objects) $(target) ./release/*

.PHONY: all clean 
