SRCS = main.c add.c division.c multiple.c sub.c clear.c disp.c sign.c copy.c comp.c setInt.c convert.c
HEADERS = division.h main.h multiple.h sub.h add.h clear.h disp.h sign.h copy.h comp.h setInt.h convert.h
OBJS = ${SRCS:.c=.o}
CC = gcc
LD = gcc
LIBS = -lm
TARGET = main

all: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET) $(LIBS)

.c.o:
	$(CC) $(CCFLAGS) -c $<

$(OBJS): $(HEADERS) Makefile

clean:
	rm -f $(TARGET) $(OBJS) *~
