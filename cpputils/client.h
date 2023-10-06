#ifndef SIMPLE_SOCKET
#define SIMPLE_SOCKET

// AF_INET:  IPv4
// AF_INET6: IPv6
//
// SOCK_STREAM: "Stream Sockets"
//  Maintains open connection and uses TCP
// SOCK_DGRAM:  "Datafram Sockets"
//  Connectionless; fire and forget and uses UDP
//
// IPPROTO_TCP: Specify TCP protocol
//  There are others for internet protocols, raw, and UDP
#define CONFIG_IPV             AF_INET
#define CONFIG_SOCKET_TYPE     SOCK_STREAM
#define CONFIG_PROTOCOL        IPPROTO_TCP

// gcc preprocessor macros
//
// if windows detected, use winsock libraries 
// otherwise assume POSIX-style sockets
#ifdef _WIN32
    #include <winsock.h>
    #include <ws2tcpip.h>
    typedef SOCKET Socket; 
    #define ERROR_SOCKET INVALID_SOCKET
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    typedef int Socket; 
    #define ERROR_SOCKET -1
#endif

// any issues will cause the function to return an error-indicating socket
// TODO: maybe create error logfile if things go wrong
Socket connect() 
{
    // initialize winsock API on windows
    // nothing needed for POSIX-style sockets
    int initStatus;
    #ifdef _WIN32
        WSADATA wsaData; 
        // check for appropriate initialization
        if (WSAStartup(MAKEWORD(2,2), &wsaData)!= 0) {
            return ERROR_SOCKET;
        }
        // check winsock version 2.2 is available
        if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
            WSACleanup(); 
            return ERROR_SOCKET;
        }
    #endif


    Socket sckt = socket(CONFIG_IPV, CONFIG_SOCKET_TYPE, CONFIG_PROTOCOL);

    #ifdef _WIN32
        // configure the connection location in the winsock struct
        sockaddr_in addrConfig; 
        addrConfig.sin_family = CONFIG_IPV; 
    #endif
    
}

int send() 
{

}

int recieve() {

}

int disconnect(Socket sckt) 
{
    #ifdef _WIN32
        int temp = closesocket(sckt); 
        WSACleanup();
        return temp;  
    #else
        return close(sckt); 
    #endif
}

#endif