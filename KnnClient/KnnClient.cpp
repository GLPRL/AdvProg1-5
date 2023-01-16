#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;
const char EOL = '$';
const char ERR = '<';
const char EF = '>';
/**
 * reads input from the user in accordance to exrecise instructions.
 * returns 1 if success
 * returns 0 if input was -1
 * returns -1 if input was not good
 */
int readVector(string &distanceType, int &k,vector<double> &v,char c[] ) {
    string lin;
    getline(cin, lin);
    for(int i=0;i<lin.length();i++){
        c[i]=lin[i];
    }
    c[lin.length()] = '\0';                         //c[lin.length()+1] = '\0';
    if(lin.compare("-1")==0){
        return 0;
    }
    lin = ' ' + lin + " ";
    // If there is more than one space in a row, then return and allow re-entry
    if (lin.find("  ") != string::npos) {
        return -1;
    }
    int pos = 0,y;
    double x;
    char *e;
    int wasDistance = 0;
    int wasVector = 0;
    int wasK = 0;

    lin.erase(0,1);
    // Loop until the end of the string each time separating the spaces.
    while ((pos = lin.find(" ")) != string::npos) {
        string sub = lin.substr(0, pos);
        if ((sub.compare("AUC") == 0)
            || (sub.compare("MAN") == 0)
            || (sub.compare("CHB") == 0)
            || (sub.compare("CAN") == 0)
            || (sub.compare("MIN") == 0)
                ) {
            if ( (wasVector == 1) && (wasK == 0) ) {
                wasDistance = 1;
                distanceType = sub;
            } else {
                return -1;
            }

        } else if (wasDistance==1)  {
            if (wasK == 1) {
                return -1;
            }
            y = stoi(sub);
            x = std::strtod(sub.c_str(), &e);
            k=y;
            if(k!=x){
                return -1;
            }
            wasK = 1;

        } else {
            x = std::strtod(sub.c_str(), &e);
            if (*e != '\0') {
                return -1;
            }
            wasVector = 1;
            v.push_back(x);
        }
        lin.erase(0, pos + 1);
    }
    if(wasDistance && wasK) {
        return 1;
    }
    return-1;
}
/**
 * Check if port is valid: If can be converted to int, and is in range 0-65535
 * @param port port to listen on
 * @return port number if exists, -1 otherwise.
 */
int getPort(string port) {
    int size = port.size();
    for (int i = 0; i < size; i++) {                  //Iterate through the port characters and validate they are digits
        if (isdigit(port[i]) == false) {
            return -1;
        }
    }
    int serverPort = stoi(port);                                                             //Convert string to int
    if (serverPort > 65535) {                                                             //Port in range of 65535 and 0
        return -1;
    }
    if (serverPort < 0) {
        return -1;
    }
    return serverPort;
}
/**
 * read data and send to server
 * @param sock  client sock
 * @return 1 if everything works; 2 if no file was found; 3 if connection error
 */
int readData(int sock) {
    char bufferFile[4096];                                                   //Clearing space for answer from server
    int expected_data_len = sizeof(bufferFile);
    int read_bytes = recv(sock, bufferFile, expected_data_len, 0);       //Receive from server
    bufferFile[read_bytes]='\0';
    if (read_bytes < 0) {                                                                             //If error
        perror("Error reading data from server");
        return 3;
    } else if ( read_bytes != 0 ) {
        cout << bufferFile;
    }
    string filename;
    cin >> filename;
    ifstream fin;
    char buffer[1];
    memset(&buffer, 0, sizeof(buffer));
    string line;
    int sent_bytes;
    fin.open(filename, ios::in);
    if (fin.is_open()) {
        while (getline(fin, line)) {                                                 //Read from file and process.
            int size = line.size();
            for (int i = 0; i < size; i++) {                                            //send char by char
                buffer[0] = line[i];
                sent_bytes = send(sock, buffer, 1, 0);
                if (sent_bytes < 0) {
                    perror("Error sending data to server\n");
                    return 3;
                }
                memset(&buffer, 0, 1);
            }
            buffer[0] = EOL;                        //Signal of EOL
            sent_bytes = send(sock, buffer, 1, 0);
            if (sent_bytes < 0) {
                perror("Error sending data to server\n");
                return 3;
            }
        }
    } else {                                                          //Failed opening file
        cout <<"invalid input"<< endl;
        buffer[0] = ERR;
        sent_bytes = send(sock, buffer, 1, 0);
        if (sent_bytes < 0) {
            perror("Error sending data to server\n");
            return 3;
        }
        return 2;
    }
    buffer[0] = EF;
    sent_bytes = send(sock, buffer, 1, 0);
    if (sent_bytes < 0) {
        perror("Error sending data to server\n");
        return 3;
    }
    fin.close();
    return 1;
}
/**
 * Display data, without saving to file.
 * @param sock client socket
 */
void receiveData(int sock) {
    char buffer[1];
    string s;
    int read_bytes = recv(sock, buffer, 1, 0);
    if (read_bytes < 0) {
        perror("Error reading data from server");
    }
    while (buffer[0] != '>' && buffer[0] != '!' && buffer[0] != '@') {      // > = end of reading data
        // ! = files were not classified
        s = s + buffer[0];                                   // @ = no files
        read_bytes = recv(sock, buffer, 1, 0);
        if (read_bytes < 0) {
            perror("Error reading data from server");
        }
    }
    if (buffer[0] == '!') {          //file was not classified
        cout << s;
        return;
    }
    cout << s;
}
/**
 * Save data into file
 * @param sock client socket
 */
void saveData(int sock, string filename) {
    ofstream fout;
    char buffer[1];
    string s;
    fout.open (filename);
    if (fout.is_open()) {
        int read_bytes = recv(sock, buffer, 1, 0);
        if (read_bytes < 0) {
            perror("Error reading data from server");
        }
        while (buffer[0] != '>' && buffer[0] != '!' && buffer[0] != '@') {      // > = end of reading data
            // ! = files were not classified
            s = s + buffer[0];                                   // @ = no files
            read_bytes = recv(sock, buffer, 1, 0);
            if (read_bytes < 0) {
                perror("Error reading data from server");
            }
        }
    } else if (buffer[0] == '!') {          //file was not classified
        cout << s;
        return;
    } else if (buffer[0] == '@') {          //no file
        cout << s;
        return;
    }
    fout << s;
    fout.close();
}
void option2(int sock){
    char buff[40];
    char c[1];
    memset(&buff, 0, 40);
    cin.ignore(1000, '\n');
    cin.getline(buff,40);
    for(int i=0;i<40;i++){
        if(buff[i]==0){
            c[0]='$';
            int sent_bytes = send(sock, c, 1, 0);
            break;
        }
        c[0]=buff[i];
        int sent_bytes = send(sock, c, 1, 0);
    }


}
/**
 * KNN client
 * @param argc command line args
 * @param argv arguments:
 * argv[0] = client.out
 * argv[1] = dest ip
 * argv[2] = dest port
 * @return
 */
int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("invalid input");
        return 1;
    }
    const char *ip_address = argv[1];                                                               //Options for socket
    const int port_no = getPort(argv[2]);
    if (port_no == -1) {                                                                                    //Error port
        perror("invalid input");
        return 1;
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        return 1;
    }
    struct sockaddr_in sin;                                                                               //setup socket
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {                   //Connected to server
        perror("Error connecting to server");
    }
    while (true) {
        char buffer[4096];                                                       //Clearing space for answer from server
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);                 //Receive from server
        buffer[read_bytes] = '\0';
        if (read_bytes < 0) {                                                                                 //If error
            perror("Error reading data from server");
        } else if (read_bytes != 0) {
            cout << buffer << endl;                                                                       //Print result
        }
        memset(&buffer, 0, sizeof(buffer));                                       //Purge past data from buffer
        char data_addr[1];
        memset(&data_addr, 0, sizeof(data_addr));                                           //Purge send buffer
        cin >> data_addr;
        int sent_bytes = send(sock, data_addr, 1, 0);                             //Sending data
        if (sent_bytes < 0) {
            perror("Error sending data to server\n");
            return 1;
        }
        if (sent_bytes == 1 && data_addr[0] == '5') {
            string filename;
            cin >> filename;
            read_bytes = recv(sock, buffer, 189, 0);
            cout <<buffer<<endl;
            memset(&buffer, 0, sizeof(buffer));
            saveData(sock, filename);
        } else if (sent_bytes == 1 && data_addr[0] == '1') {     //Upload command
            int f1 = readData(sock);                               //upload training file
            if (f1 == 1) {
                int f2 = readData(sock);                               //upload testing file
                if (f2 == 1) {              //both files uploaded successfully
                    char buff[16];
                    read_bytes = recv(sock, buff, 16, 0);
                    int i = 0;
                    string s;
                    for(;i<16;i++) {
                        s = s + buff[i];
                    }
                    cout << s << endl;
                    continue;
                } else if (f2 == 2) {
                    continue;
                }
            } else if (f1 == 2) {                                 //Wrong path
                continue;
            }
        } else if (sent_bytes == 1 && data_addr[0] == '2') {
            option2(sock);
        } else if (sent_bytes == 1 && data_addr[0] == '4') {
            receiveData(sock);
        } else if (sent_bytes == 1 && data_addr[0] == '8') {
            exit(0);
        } else if (sent_bytes == 1 && data_addr[0] == '3') {
            char bufferOne[1];
            read_bytes = recv(sock, bufferOne, 1, 0);
            if (bufferOne[0] == '!') {                //won't run loop if everything is correct
                string s;
                char err[18];
                read_bytes = recv(sock, err, 18, 0);
                int i = 0;
                while (i < 18) {                      //copy data to string to print
                    s = s + err[i];
                    i++;
                }
                cout << s << endl;
            }
            memset(&bufferOne, 0, 1);
        }
    }
}