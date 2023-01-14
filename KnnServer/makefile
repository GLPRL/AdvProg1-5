CC = g++
CFLAGS = -std=c++11

server.out: knnServer.o Algorithms.o MainDistance.o TypeVector.o InOut.o Client.o CLI.o Command.o
	$(CC) $(CFLAGS) knnServer.o Algorithms.o MainDistance.o TypeVector.o SocketIO.o StandardIO.o Client.o CLI.h ClassifyData.o UploadData.o -o server.out

knnServer.o: knnServer.cpp knnServer.h
	$(CC) $(CFLAGS) -c knnServer.cpp

Algorithms.o: Algorithms.cpp Algorithms.h
	$(CC) $(CFLAGS) -c Algorithms.cpp

MainDistance.o: MainDistance.cpp MainDistance.h
	$(CC) $(CFLAGS) -c MainDistance.cpp

TypeVector.o: TypeVector.cpp TypeVector.h
	$(CC) $(CFLAGS) -c TypeVector.cpp

Client.o: Client.h Client.cpp
	$(CC) $(CFLAGS) -c Client.cpp

InOut.o: IO/DefaultIO.h IO/SocketIO.h IO/SocketIO.cpp IO/StandardIO.h IO/StandardIO.cpp
	$(CC) $(CFLAGS) -c IO/SocketIO.cpp
	$(CC) $(CFLAGS) -c IO/StandardIO.cpp

Command.o: Command/Command.h Command/ClassifyData.cpp Command/UploadData.cpp
	$(CC) $(CFLAGS) -c Command/ClassifyData.cpp Command/UploadData.cpp

CLI.o:
	$(CC) $(CFLAGS) -c CLI.h

#need to compile/link the IO and Command dirs too

clean:
	rm -f *.o server.out
