#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <chrono>
#include <iomanip>
#include <errno.h>
#include "tcpsocket.h"
using namespace std::chrono_literals;
using namespace std::chrono;
using std::endl;
using std::cout;
using std::cerr;

const char *date_template = "[%Y-%m-%d %H:%M:%S]";
const char *name="Test";
struct message{
    time_point<system_clock> time;
    std::string name;
    operator std::string(){
        std::ostringstream oss;
        auto tt = system_clock::to_time_t(time);
        std::tm tm = *std::gmtime(&tt);
        oss<<std::put_time(&tm,date_template)<<"%"<<name;
        return oss.str();
    }
};

int main()
{
    cout<<"Configuration started"<<endl;
    TcpSocket socket;
    try{
        socket.connect("127.0.0.1",32276);
    }catch(std::runtime_error e){
        cerr<<e.what()<<endl;
        return errno;
    }
    cout<<"Configuration finished."<<endl;
    cout<<"Sending data. Press Esc for exit."<<endl;
    while (true) {
        message m{system_clock::now(),name};
        cout<<(std::string)m<<endl;
        socket.send(m,0);
        std::this_thread::sleep_for(2s);
    }
    return 0;
}
