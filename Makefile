
LFLAGS=-pthread

# Nota: versioni precedenti di PThreads utilizzavano
# un flag differente ("-lpthread").
#LFLAGS=-lpthread

all:start

start.o: main.c header.h 
	gcc -c  main.c

procedure.o: procedure.c header.h
	gcc -c  procedure.c 

start: main.o procedure.o
	gcc  $(LFLAGS) -o start main.o procedure.o

clean:
	 rm -f *.o 
	 rm -f ./start

