#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <chrono>
#include <iomanip>
using namespace std::chrono_literals;
using namespace std::chrono;
using std::endl;
using std::cout;
using std::cerr;

const char *date_template = "[%Y-%m-%d %H:%M:%S]";
struct message{
    time_t time;
    std::string name;
    operator std::string(){
        std::ostringstream oss;
        std::tm* tm = std::gmtime(&time);
        oss<<std::put_time(tm,date_template)<<name;
        return oss.str();
    }
};

int main()
{
    cout<<"Configuration started"<<endl;
    int c_handle = socket(AF_UNIX,SOCK_DGRAM,0);
    if(c_handle){
        cerr<<"Error: can't create socket"<<endl;
        return -1;
    }
    sockaddr_in s_address{AF_UNIX,htons(4223),INADDR_LOOPBACK};
    if(bind(c_handle,reinterpret_cast<sockaddr *>(&s_address),sizeof(s_address))){
        cerr<<"Error: can't bind socket"<<endl;
        return -1;
    }
    cout<<"Configuration finished."<<endl;
    cout<<"Sending data. Press Esc for exit.";
    while (true) {
        message m{system_clock::now().time_since_epoch().count(),"Test"};
        std::this_thread::sleep_for(20s);
    }
    return 0;
}
