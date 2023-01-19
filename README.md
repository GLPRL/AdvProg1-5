# AdvProg1-5: Multiple Clients, Single Knn Server
Fourth Task in Advanced Programming 1 course 2023/838921001

Authors:

Gal Pearl,
Dekel Schreiber

In this task, there will be five algorithms for calculating vectors, in different approaches.
The client selects the test and train files: the earlier is already classified, the latter is to be classified.

Each vector in the unclassified CSV will be classified, according to known algorithms and number of closest neighbors,
and the user can modify calculation variables (Algorithm and amount of neighbors), display the info or save to file.

Comparisons can be made between a single archtype, as each has their own attributes to compare.

### Compliation Instructions:
First, clone/download zip of the repository, 
cloning:
```
git clone https://github.com/GLPRL/AdvProg1-5
```
(ZIP requires unpacking, use your preffered method)
and cd into the un-packed project folder
Among all the files, there's a makefile for using make. However, you'll need to use it for the entity you need:

For each entity - client and server, there's a make command. Cd into the wanted folder and run
```
make
```

##### Run instructions for server:

First, you must check if a port is available. Do it with 
```
netstat
```
Look for the following attributes:

**Type:** STREAM

**State:** CONNECTED

**Path:** (none/empty)

Each one of them is required for correct functionality and connectivity of the server.
#### Run the server with:
```
./server.out <port>
```
- port: A valid port in range of 0-65535. We will check at runtime.

#### Run instructions for client:
```
./client.out <ip> <port>
```
- ip: 127.0.0.1, Unless client is run on a different computer)
- port: A valid port in range of 0-65535, used to connect to the server.

## General implementation details
### Distance Algorithms

We have a server, which will accept new clients and work with each one on a seperate thread,
saving their data in a new class, called Client. The data of each client will be made of items to classify, classified items, options of the
algorithm to use and more, as all of the above is used to communicate and help the server to proccess the data, maintaining communications with the client as well.

The algorithms implementation reside in Algorithms.cpp source file. There is also a header file Algorithms.h for this source file which the main includes in order to have access to the algorithms.

The Algorithms are implemented in accordance to the guidlines that are listed below.

List of Algorithms:

1) Euclidean Distance: We receive two points, each one will be represented as an array - the size of the array is as the size of the dimension.
   Points will be marked as P and Q, and coordinates will be marked as p1, p2, p3 .... and q1, q2, q3 .... for each i, qi and pi will be the coordinate of the
   point, and "i" will not be larger than the size of the dimension. General idea:
   
   ![image](https://user-images.githubusercontent.com/116657293/201177857-87b63e5f-3d96-40c0-8830-92bd56ce6340.png)
   
2) Manhattan Geometry: Sum of two points in their cartesian coordinates. We will receive two points, in a given dimension, marked as N.
   Points are represented by arrays with N slots.Calculation will present the sum of lengths of the projections of the line segment between points onto the coordinate      axes. Formally:
   
   ![image](https://user-images.githubusercontent.com/116657293/201179543-c6ef7476-f613-4903-acb6-cb0a0cbf0a75.png)
   
   Where P = (p1, p2, ... , pn) and Q = (q1, q2, ... , qn)
   
3) Chebyshev Distance: The distance is defined by the greatest distance difference, between two vectors, in a vector space.
   Each vector will be represented by N numbers (N >= 1), and will be represented as an array. For each Xi and Yi, as Xi is a coord. from X, and Yi from Y,
   will return the max distance of Xi - Yi, for each i in range of 1 to N. Formally:
   
   ![image](https://user-images.githubusercontent.com/116657293/201183032-e4f08c81-3ece-415a-b3d4-25ccf5729271.png)
   
4) Canberra Distance: numerical measure of the distance between pairs of points in a vector space. It is used to compare ranked lists.         
   Formally: (For P = (p1, p2, ... , pn) and Q = (q1, q2, ... , qn))
   *Fun fact: Also used for intrusion detection in computer security (IDS).*
   
   ![image](https://user-images.githubusercontent.com/116657293/201183812-5c097577-4977-4eff-a4cc-c545d3817105.png)

   **Important Notice** : If Pi = Qi = 0, then we divide by zero. Instead, the calc. of abs(Pi)+abs(Qi), will make the division
   zero, in total, with a simple condition to check if it's met. Otherwise, the program will work as usual.

5) Minkowski Distance: metric for a normed vector space, which is a generalization of Euclidean and Manhattan Distance formulas.

   ![image](https://user-images.githubusercontent.com/116657293/201184801-bcb3d888-f0a9-4b54-8b15-e9f8aa8c3509.png)

      As for P: The formula uses P=1 or P=2, which corresponds to the Manhattan and Euclidean formulas, respectively.
      In this task, we take P=2 only (as stated by TA, We can choose any parameter P). So eventually, it'll run Euclidean formula.
      
### TypeVector
We introduce a new object: TypeVector.
It contains three field:
   - Vector of double type numbers. Stores values of location in some dimention
   - String, describing the type of the vector. Ex.: Our vector is a type of flower, "iris-versicolor". So, "iris-versicolor" will be stored.
   - Distance of type double. We will store the distance of the vector with a given user vector, according to algorithm of their choosing.
   
### Server - Client Classification Process
Our server will deal with reading from CSV file (Only once, at initial start), and store the data in a vector of TypeVector.
Next, it will initiate a sequence of operations to start listening on a given port, waiting for clients.
Once a client has reached out, it'll accept it, and receive data, as follows:
1) A list of numbers: the vector to process and classify. Each number will be verified for correctness at client side.
2) Distance calculation method: 
   
   - AUC for Euclidean;
   - MAN for Manhattan;
   - CHB for Chebyshev;
   - CAN for Canberra;
   - MIN for Minkowsky;
   
   Each algorithm selection will be verified for correctness at client side.
   
3) Natural number (K): The user's selection for K - nearest - neighbors.

Afterwards, it will build all the data that was received as vector of double precision numbers, string and an integer
and will find what is the item's K closest neighbors: Calculate the distance between each record in the CSV file, that was translated
into TypeVector, and the user's input vector, according to user's algorithm selection.
   
After the distance was calculated, we sort using a specialized "less"-operator, that will compare by distances (smallest distance is first),
count the K - first TypeVectors, and find the one who appeared the most times - and return the type of it, back to the main function which server
running, sent back to the client as simple text to print.
After finishing, the server will wait for more data to be sent, and allows up to 5 clients simultaneously.

### Design Patter: Command
![image](https://user-images.githubusercontent.com/116657293/211402849-f1d01908-18af-4c38-a03a-fede81e50ece.png)

New design pattern, utilising Command.h abstract class. Each request by the client is a command to the server, to execute accordingly.
Each Command uses the Command.h header file, implementing it: execute is abstract, and each command will implement it.
The fields for the commands are the DefaultIO (another class) and our class for saving data of a specific user - Client.

Commands List:
1) Upload the training file and the test file: Which are the classified and unclassified vectors files.
2) Algorithm settings: Change method of calc. and amount of neighbors.
3) Classify the data: Run the classification.
4) Display results: In simple text.
5) Download results from server, into a file in the path of the user's system.
8) Exit.

### DefaultIO
Another abstract class, which is implemented by SocketIO, and StandardIO.
StandardIO is simple interaction using standard input/output via keyboard and screen.
SocketIO is interaction for client/server on the network, receiving byte-byte and sending a chunk of bytes to
client, which in turn, reads byte-byte until a signal is sent to stop expecting for data from the server.

### CLI
A new class which will maintain the correct operation of commands on the server.
It has info about the commands, mapped to their numbers, which the user entered in order to execute.

### Client
As mentioned earlier, a class used to save a client's info for the server to process, send and receive,
in it's respective thread.

<sub> Images and some explanations sourced from Wikipedia pages of the distance formulas </sub>
