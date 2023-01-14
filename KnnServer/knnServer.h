/**
 * KnnServer header file
 */
#ifndef ADVPROG1_4_KNNSERVER_H
#define ADVPROG1_4_KNNSERVER_H
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include "Algorithms.h"
#include "MainDistance.h"
#include "Client.h"
#include "CLI.h"
#include "IO/SocketIO.h"
#include "IO/StandardIO.h"
#include "Command/Command.h"
#include "Command/UploadData.cpp"
using namespace std;
#endif //ADVPROG1_4_KNNSERVER_H
