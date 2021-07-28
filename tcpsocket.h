#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <string>
#include <netinet/in.h>
class TcpSocket
{
    int _handle{0};

public:
    TcpSocket();
    operator bool();
    void connect(in_addr addr, unsigned short port);
    void connect(const std::string &address,unsigned short port);
    void send();
};

#endif // TCPSOCKET_H
