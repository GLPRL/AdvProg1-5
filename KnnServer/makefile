server.out: knnServer.o Algorithms.o MainDistance.o TypeVector.o		#Server files
	g++ -std=c++11 knnServer.o Algorithms.o MainDistance.o TypeVector.o -o server.out

knnServer.o: knnServer.cpp KnnServer/knnServer.h
	g++ -c knnServer.cpp

Algorithms.o: Algorithms.cpp KnnServer/Algorithms.h
	g++ -c Algorithms.cpp

MainDistance.o: MainDistance.cpp
	g++ -c MainDistance.cpp

TypeVector.o: TypeVector.cpp KnnServer/TypeVector.h
	g++ -c TypeVector.cpp

clean:
	rm *.o *.out
