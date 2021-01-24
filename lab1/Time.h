// Denna fil ska innehålla deklarationer för de typer och funktioner
// som behövs
#include <stdexcept>
#include <string>
#include <iostream>
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
    std::string to_string(bool format=false);
    std::string construct_string(int h, int m, int s);
    std::string format_string(std::string const& time);
private:
    int h;
    int m;
    int s;
    bool am;
    //void convert(int const h, int const m, int const s);
};
