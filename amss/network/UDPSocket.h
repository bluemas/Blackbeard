//
// Created by bluem on 2017-10-25.
//

#ifndef LGDEMOCODEDIST_CUDPSOCKET_H
#define LGDEMOCODEDIST_CUDPSOCKET_H

#if  defined(_WIN32) || defined(_WIN64)
#pragma comment (lib, "Ws2_32.lib")
#include <Winsock2.h>
#include <ws2tcpip.h>
#define  CLOSE_SOCKET closesocket
#define  SOCKET_FD_TYPE SOCKET
#define  BAD_SOCKET_FD INVALID_SOCKET
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <arpa/inet.h>
#include <unistd.h>
#define  CLOSE_SOCKET close
#define  SOCKET_FD_TYPE int
#define  BAD_SOCKET_FD  -1
#endif

//------------------------------------------------------------------------------------------------
// Types
//------------------------------------------------------------------------------------------------

typedef struct
{
    SOCKET_FD_TYPE UdpFd;
} TUdpLocalPort;

typedef struct
{
    struct sockaddr_in remaddr;
} TUdpDest;

class UDPSocket {

public:

    TUdpLocalPort* OpenUdpPort(short localport);

    void CloseUdpPort(TUdpLocalPort **UdpLocalPort);

    TUdpDest * GetUdpDest(const char *remotehostname, const char * remoteportno);

    void DeleteUdpDest(TUdpDest **dest);

    int SendUDPMsg(TUdpLocalPort * UdpLocalPort,TUdpDest *dest, unsigned char *msg, size_t length);

    int RecvUDPMsg(TUdpLocalPort * UdpLocalPort, unsigned char *msg, size_t length,struct sockaddr *src_addr, socklen_t *addrlen);

private:

};


#endif //LGDEMOCODEDIST_CUDPSOCKET_H
