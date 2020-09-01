CC	=	gcc
CFLAGS	=	-Wall
LDFLAGS	=
OBJFILES	=	shell-methods.o main.o
TARGET	=	seashell

all:	$(TARGET)

$(TARGET):	$(OBJFILES)
	$(CC)	$(CFLAGS)	-o	$(TARGET)	$(OBJFILES)	$(LDFLAGS)

clean:
	TARGET *.o

