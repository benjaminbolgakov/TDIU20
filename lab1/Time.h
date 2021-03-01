// Denna fil ska innehålla deklarationer för de typer och funktioner
// som behövs
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

class Time{
public:
    //Constructors
    Time(int hour = 0, int minute = 0, int second = 0);
    Time(std::string const& time);
    //Getters
    int hour() const;
    int minute() const;
    int second() const;
    bool is_am() const;
    //Operators
    operator std::string();
    
    //Functions
    int convert_to_seconds(Time const time);
    std::string to_string(bool format = false);
    std::string construct_string(int const h, int const m, int const s, bool format = false);
    int transform_format(int const h, bool format = false);
    void apply_period(std::string &input, bool const format);
    //Operators
    Time& operator++();
    Time& operator--();
    Time operator+(const int add);
    Time operator-(const int sub);
    bool operator>(Time const tl, Time const tr);
    bool operator<(Time const tl, Time const tr);
    bool operator>=(Time const tl, Time const tr);
    bool operator<=(Time const tl, Time const tr);
    bool operator==(Time const tl, Time const tr);
    bool operator!=(Time const tl, Time const tr);
        
private:
    int h;
    int m;
    int s;
    bool am;
};
//Custom operator
std::ostream &operator<< (std::ostream &os, Time time);
std::istream &operator>> (std::istream &in, Time&time);
