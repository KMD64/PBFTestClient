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
    ssize_t send(const void *data, size_t size,int flags);
    ssize_t send(const std::string &s, int flags);
};

#endif // TCPSOCKET_H
