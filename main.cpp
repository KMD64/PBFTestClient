#include <iostream>
#include <sstream>
#include <thread>
#include <iomanip>
#include <errno.h>
#include <linux/input.h>
#include "tcpsocket.h"
#include "message.h"

using namespace std::chrono_literals;
using namespace std::chrono;
using std::endl;
using std::cout;
using std::cerr;




int main(int argc, char ** argv)
{
    cout<<"Configuration started"<<endl;

    if(argc<4)return 4;

    std::string client_name = argv[1];
    int port = std::atoi(argv[2]);
    seconds period{std::atoi(argv[3])};

    TcpSocket socket;
    try{
        socket.connect("127.0.0.1",port);

    //Here starts the cycle
    cout<<"Configuration finished."<<endl;
    cout<<"Sending data."<<endl;
    while (true) {
        Message m{system_clock::now(),client_name};
        std::string s(m);
        cout<<s<<endl;
        socket.send(s,0);
        std::this_thread::sleep_for(period);
    }
    }catch(std::runtime_error e){
        cerr<<e.what()<<":"<<errno<<endl;
        return errno;
    }
    return 0;
}
