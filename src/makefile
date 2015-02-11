OBJS = main.o Tree.o Station.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

proj : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o proj

main.o : main.cpp Tree.h
	$(CC) $(CFLAGS) main.cpp

Tree.o: Tree.h Tree.cpp Station.h
	$(CC) $(CFLAGS) Tree.cpp
	
Station.o: Station.h Station.cpp
	$(CC) $(CFLAGS) Station.cpp

clean:
	\rm *.o *~ proj

tar:
	tar cfv proj.exe main.cpp Tree.cpp Tree.h Station.cpp Station.h