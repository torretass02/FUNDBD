CC = gcc -g
CFLAGS = -Wall -Wextra -pedantic #-ansi
LDLIBS = -lodbc
HEADERS = odbc.h

EXE = odbc-connection-test odbc-connection-test-2 odbc-example1 odbc-example2 odbc-example3 odbc-example4 menu

all : $(EXE)

clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o odbc.o

%.o: %.c $(HEADERS)
	@echo Compiling $<...
	$(CC) $(CFLAGS) -c -o $@ $<