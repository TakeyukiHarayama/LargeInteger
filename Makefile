SRCS = main.c add.c division.c multiple.c sub.c
HEADERS = division.h main.h multiple.h sub.h
OBJS = ${SRCS:.c=.o}
CC = gcc #Compiler
FC = gfortran
LD = gcc #Linker
#LIBS = -lm -L/usr/local/lib -llis #Library Option.Command line option.
LIBS = -lm #Library Option.Command line option.
TARGET = main #name of excutefile

#Run when make no option
all: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET) $(LIBS)

#cfile -> Object
.c.o:
	$(CC) $(CCFLAGS) -c $<

#Object -> Headerfile
$(OBJS): $(HEADERS) Makefile

clean:
	rm -f $(TARGET) $(OBJS) *~
