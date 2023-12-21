#ifndef CONNECT_H
#define CONNECT_H

void setupServerSocket(int*);
void acceptConnection(int, int*);
void setupClientSocket(int*, char*);
int  rcvData(int, char*);
void sendData(int, char*);

#endif