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
    //_testfail();
    sockaddr_in s_addr{AF_INET,htons(port),addr};
    s_addr.sin_family=AF_INET;
    s_addr.sin_port=htons(port);
    s_addr.sin_addr=addr;
    if(::connect(_handle,reinterpret_cast<sockaddr*>(&s_addr),sizeof(s_addr))==-1){
        throw std::runtime_error("Failed to create connection");
    }
}

void TcpSocket::connect(const std::string &address, unsigned short port)
{
    //_testfail();
    in_addr addr;
    if(!inet_aton(address.c_str(),&addr)){
        throw std::runtime_error("Failed to translate address");
    }
    connect(addr,port);
}

ssize_t TcpSocket::send(const void *data, size_t size,int flags)
{
    //_testfail();
    auto res = ::send(_handle,data,size,flags);
    if(res<0){
        throw(std::runtime_error("Failed to send message"));
    }
    return res;
}
ssize_t TcpSocket::send(const std::string &s,int flags){
    return send(reinterpret_cast<const void *>(s.c_str()),s.size(),flags);
}
void TcpSocket::_testfail()
{
    if(_handle==-1){
        throw(std::runtime_error("Invalid socket"));
    }
}

