//
// Created by bluem on 2017-10-25.
//

#ifndef LGDEMOCODEDIST_CTCPSOCKET_H
#define LGDEMOCODEDIST_CTCPSOCKET_H


#if  defined(_WIN32) || defined(_WIN64)
#pragma comment (lib, "Ws2_32.lib")
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
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
    SOCKET_FD_TYPE ListenFd;
} TTcpListenPort;

typedef struct
{
    SOCKET_FD_TYPE ConnectedFd;
} TTcpConnectedPort;


class CTCPSocket {
public:
    TTcpListenPort *OpenTcpListenPort(short localport);
    void CloseTcpListenPort(TTcpListenPort **TcpListenPort);
    TTcpConnectedPort *AcceptTcpConnection(TTcpListenPort *TcpListenPort,
                                           struct sockaddr_in *cli_addr,socklen_t *clilen);
    TTcpConnectedPort *OpenTcpConnection(const char *remotehostname, const char * remoteportno);
    void CloseTcpConnectedPort(TTcpConnectedPort **TcpConnectedPort);
    ssize_t ReadDataTcp(TTcpConnectedPort *TcpConnectedPort,unsigned char *data, size_t length);
    ssize_t WriteDataTcp(TTcpConnectedPort *TcpConnectedPort,unsigned char *data, size_t length);
};


#endif //LGDEMOCODEDIST_CTCPSOCKET_H
