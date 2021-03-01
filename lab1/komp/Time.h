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

    //Functions
    std::string to_string(bool format = false) const;

    //Operators
    operator std::string() const;
    Time& operator++();
    Time operator++(int);
    Time& operator--();
    Time operator--(int);
    Time operator+(const int add);
    Time operator-(const int sub);
    bool operator>(Time const& tr) const;
    bool operator<(Time const& tr) const;
    bool operator>=(Time const& tr) const;
    bool operator<=(Time const& tr) const;
    bool operator==(Time const& tr) const;
    bool operator!=(Time const& tr) const;

private:
    int h;
    int m;
    int s;

    //Helper-functions
    int convert_to_seconds(Time const time) const;
    std::string construct_string(int const hour, int const minute,
                                 int const second, bool format = false) const;
    int transform_format(int const hour, bool format = false) const;
    void apply_period(std::string &input, bool const format) const;
    void isValid(int const hour, int const minute, int const second) const;
};
//Custom operator
std::ostream &operator<< (std::ostream &os, Time time);
std::istream &operator>> (std::istream &in, Time&time);
