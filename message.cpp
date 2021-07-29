#include "message.h"
#include <string>
#include <iomanip>

Message::operator std::string(){
    std::ostringstream oss;
    auto ms = time_point_cast<milliseconds>(time)-time_point_cast<seconds>(time);
    auto tt = system_clock::to_time_t(time);
    std::tm tm = *std::gmtime(&tt);
    const char *date_template = "%Y-%m-%d %X";
    oss<<'['<<std::put_time(&tm,date_template)<<"."<<ms.count()<<"] "<<name;
    return oss.str();
}
