#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <errno.h>

#include "Net/tcpsocket.h"
using namespace std::chrono_literals;
using namespace std::chrono;
using std::endl;
using std::cout;
using std::cerr;

const char *date_template = "[%Y-%m-%d %X]";
struct message{
    time_point<system_clock> time;
    std::string name;
    operator std::string(){
        std::ostringstream oss;
        auto ms = time_point_cast<milliseconds>(time)-time_point_cast<seconds>(time);
        auto tt = system_clock::to_time_t(time);
        std::tm tm = *std::gmtime(&tt);
        oss<<std::put_time(&tm,date_template)<<"."<<ms.count()<<"%"<<name;
        return oss.str();
    }
};

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

    cout<<"Configuration finished."<<endl;
    cout<<"Sending data."<<endl;
    while (true) {
        message m{system_clock::now(),client_name};
        cout<<(std::string)m<<endl;
        socket.send(m,0);
        std::this_thread::sleep_for(period);
    }
    }catch(std::runtime_error e){
        cerr<<e.what()<<endl;
        return errno;
    }
    return 0;
}
