#include "tcpsocket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
TcpSocket::TcpSocket()
{
    _handle = socket(AF_INET,SOCK_STREAM,0);
}

TcpSocket::operator bool()
{
    return _handle!=-1;
}

void TcpSocket::connect(in_addr addr, unsigned short port)
{
    sockaddr_in s_addr{AF_INET,htons(port),addr};

    if(::connect(_handle,reinterpret_cast<sockaddr*>(&s_addr),sizeof(addr))){
        throw std::runtime_error("Failed to create connection");
    }
}

void TcpSocket::connect(const std::string &address, unsigned short port)
{
    in_addr addr;
    if(!inet_aton(address.c_str(),&addr)){
        throw std::runtime_error("Failed to translate address");
    }
    connect(addr,port);
}



