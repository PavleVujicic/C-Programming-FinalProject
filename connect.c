#include "defs.h"

/* 
 * Function: setupServerSocket
 * ---------------------------
 * Sets up the server socket.
 *
 * serverSocket: Pointer to the integer where the server socket descriptor will be stored.
 */
void setupServerSocket(int *s)
{
  struct sockaddr_in serverAddr;
  int currPort = MIN_PORT;
  int i;

  
  *s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (*s < 0) {
    perror("Error creating socket");
    exit(EXIT_FAILURE);
  }

 
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons((unsigned short) currPort);

  
  i = bind(*s, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  while (i < 0 && currPort <= MAX_PORT) {
    perror("Error binding socket");
    printf("Trying next port: %d\n", currPort);
    serverAddr.sin_port = htons((unsigned short) ++currPort);
    i = bind(*s, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  }

  if (i < 0) {
    perror("Error binding socket");
    exit(EXIT_FAILURE);
  }

  
  i = listen(*s, 5);
  if (i < 0) {
    perror("Error listening on socket");
    exit(EXIT_FAILURE);
  }

  //printf("Server socket setup successful. Listening on port: %d\n", currPort);
}


/* 
 * Function: acceptConnection
 * --------------------------
 * Accepts a client connection.
 *
 * serverSocket: Server socket descriptor.
 * clientSocket: Pointer to the integer where the client socket descriptor will be stored.
 */
void acceptConnection(int lSock, int *cSock)
{
  struct sockaddr_in clientAddr;
  socklen_t addrSize;

  
  addrSize = sizeof(clientAddr);

  *cSock = accept(lSock, (struct sockaddr *) &clientAddr, &addrSize);
  if (*cSock < 0) {
    perror("Error accepting connection");
    exit(EXIT_FAILURE);
  }

  
  char clientIP[INET_ADDRSTRLEN];
  if (inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN) == NULL) {
    perror("Error converting client IP address");
    exit(EXIT_FAILURE);
  }

  //printf("Accepted connection from %s:%d\n", clientIP, ntohs(clientAddr.sin_port));
}


/* 
 * Function: setupClientSocket
 * ---------------------------
 * Sets up the client socket.
 *
 * clientSocket: Pointer to the integer where the client socket descriptor will be stored.
 * serverIP:     IP address of the server.
 */
void setupClientSocket(int *s, char *ip)
{
  struct sockaddr_in addr;
  int i;
  int currPort = MIN_PORT;

  
  *s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (*s < 0) {
    printf("Could not open socket\n");
    exit(-1);
  }

  
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(ip);
  addr.sin_port = htons((unsigned short) currPort);

  

  i = connect(*s, (struct sockaddr *) &addr, sizeof(addr));

  while (i<0 && currPort <= MAX_PORT) {
    addr.sin_port = htons((unsigned short) ++currPort);
    i = connect(*s, (struct sockaddr *) &addr, sizeof(addr));
  }

  if (i<0) {
    printf("Client could not connect\n");
    exit(-1);
  }
}


/* 
 * Function: sendData
 * -------------------
 * Sends data to the server.
 *
 * clientSocket: Client socket descriptor.
 * data:         Pointer to the character array containing data to be sent.
 */
void sendData(int s, char *buffer)
{
  send(s, buffer, strlen(buffer), 0);
}


/* 
 * Function: rcvData
 * -----------------
 * Receives data from the server.
 *
 * clientSocket: Client socket descriptor.
 * buffer:       Pointer to the character array where received data will be stored.
 *
 * Returns: Number of bytes received.
 */
int rcvData(int s, char *buffer)
{
  char tmpBuff[MAX_BUFF];
  int bytesRcv;

  
  bytesRcv = recv(s, tmpBuff, sizeof(tmpBuff), 0);
  tmpBuff[bytesRcv] = 0;
  strcpy(buffer, tmpBuff);

  return(bytesRcv);

}

