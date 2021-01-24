// I denna fil läggs definitionerna (implementationen) av de funktioner
// som deklarerats i Time.h
#include "Time.h"

Time::Time(int hour, int minute, int second)
    : h{hour}, m{minute}, s{second}, am{false}
{
    //Error initializing object (incorrect format)
    if(hour < 0 || hour > 23 ||
       minute < 0 || minute > 59 ||
       second < 0 || second > 59){
        throw std::logic_error{"Invalid time value"};
    }
    if(hour < 12){
        am = true;
    }
}

Time::Time(std::string const& time)
    : h{stoi(time.substr(0,2))}, m{stoi(time.substr(3,2))},
      s{stoi(time.substr(6,2))}, am{false}
{
    if(h < 0 || h > 23 ||
       m < 0 || m > 59 ||
       s < 0 || s > 59){
        throw std::logic_error{"Invalid time value"};
    }
}
int Time::hour() const{
    return h;
}
int Time::minute() const{
    return m;
}
int Time::second() const{
    return s;
}
bool Time::is_am() const{
    return am; 
}
//Construct and convert time to string
//Converts into 12h format if "format" is true
std::string Time::to_string(bool format){
    std::string formatted;
    if(format){
        formatted = construct_string(h,m,s);
    }else{
        formatted = construct_string(h,m,s);
    }
//    std::cout << formatted << std::endl;
    return formatted;
}

std::string Time::construct_string(int h, int m, int s){
    std::string time;
    std::vector<int> v = {h,m,s};
    for(int n : v){
        if(n < 10){
            time += '0';
            time += n+'0';
        }else{
            time += std::to_string(n);
        }
        time += ':';
    }
    return time;
}

std::string Time::format_string(std::string const& time){
    
}
