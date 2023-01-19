CC = g++
CFLAGS = -std=c++11 -pthread

all: server.out client.out

server.out: KnnServer/knnServer.o KnnServer/Algorithms.o KnnServer/MainDistance.o KnnServer/TypeVector.o KnnServer/InOut.o KnnServer/Client.o KnnServer/CLI.o KnnServer/Command.o
	$(CC) $(CFLAGS) KnnServer/knnServer.o KnnServer/Algorithms.o KnnServer/MainDistance.o KnnServer/TypeVector.o SocketIO.o StandardIO.o KnnServer/Client.o KnnServer/CLI.h ClassifyData.o UploadData.o -o server.out

client.out:	
	g++ -std=c++11 KnnClient/KnnClient.cpp -o client.out

knnServer.o: KnnServer/knnServer.cpp KnnServer/knnServer.h
	$(CC) $(CFLAGS) -c KnnServer/knnServer.cpp

Algorithms.o: KnnServer/Algorithms.cpp KnnServer/Algorithms.h
	$(CC) $(CFLAGS) -c KnnServer/Algorithms.cpp

MainDistance.o: KnnServer/MainDistance.cpp KnnServer/MainDistance.h
	$(CC) $(CFLAGS) -c KnnServer/MainDistance.cpp

TypeVector.o: KnnServer/TypeVector.cpp KnnServer/TypeVector.h
	$(CC) $(CFLAGS) -c KnnServer/TypeVector.cpp

Client.o: KnnServer/Client.h KnnServer/Client.cpp
	$(CC) $(CFLAGS) -c KnnServer/Client.cpp

KnnServer/InOut.o: KnnServer/IO/DefaultIO.h KnnServer/IO/SocketIO.h KnnServer/IO/SocketIO.cpp KnnServer/IO/StandardIO.h KnnServer/IO/StandardIO.cpp
	$(CC) $(CFLAGS) -c KnnServer/IO/SocketIO.cpp
	$(CC) $(CFLAGS) -c KnnServer/IO/StandardIO.cpp

KnnServer/Command.o: KnnServer/Command/Command.h KnnServer/Command/ClassifyData.cpp KnnServer/Command/UploadData.cpp
	$(CC) $(CFLAGS) -c KnnServer/Command/ClassifyData.cpp KnnServer/Command/UploadData.cpp KnnServer/Command/AlgoSettings.h KnnServer/Command/SendnSaveData.h KnnServer/Command/SendSaveData.h

KnnServer/CLI.o:
	$(CC) $(CFLAGS) -c KnnServer/CLI.h


clean:
	rm -f *.o KnnServer/*.h.gch KnnServer/*.o KnnClient/*.o server.out client.out
