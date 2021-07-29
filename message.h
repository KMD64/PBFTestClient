#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <chrono>
#include <sstream>
using namespace std::chrono;

struct Message
{
    time_point<system_clock> time;
    std::string name;
    operator std::string();
};

#endif // MESSAGE_H
