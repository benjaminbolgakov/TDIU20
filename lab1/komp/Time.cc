// I denna fil läggs definitionerna (implementationen) av de funktioner
// som deklarerats i Time.h
// w++17 test_main.o Time.cc time_test.cc
#include "Time.h"

Time::Time(int hour, int minute, int second)
    : h{hour}, m{minute}, s{second}
{
    isValid(hour,minute,second);
}
Time::Time(std::string const& time)
    : h{}, m{}, s{}
{
    char c;
    std::stringstream ss;
    ss << time;
    ss >> h >> c >> m >> c >> s;
    isValid(h,m,s);
}

void Time::isValid(int const hour, int const minute, int const second) const
{
    if(hour < 0 || hour > 23 ||
       minute < 0 || minute > 59 ||
       second < 0 || second > 59)
    {
        throw std::logic_error{"Invalid time value"};
    }
}

std::string Time::to_string(bool format) const
{
    std::string formatted;
    //format indicates wether or not to use 12hr format
    formatted = construct_string(h,m,s,format);
    return formatted;
}
int Time::transform_format(int const hour, bool format) const
{
    int result = hour;
    if(format && hour > 12)
    {
        //Transform from 24h format to 12h
        result = hour-12;
    }
    return result;
}
std::string Time::construct_string(int const hour, int const minute,
                                   int const second, bool format) const
{
    std::string time;
    std::vector<int> v = {transform_format(hour,format),minute,second};
    for(int n : v)
    {
        if(n < 10)
        {
            time += '0';
            time += n+'0';
        }else
        {
            time += std::to_string(n);
        }
        time += ':';
    }
    time.pop_back(); //Remove trailing ':' (Fix this in a better way?)
    apply_period(time, format);
    return time;
}

std::ostream &operator<< (std::ostream &os, Time time){
    os << time.to_string();
    return os;
}
std::istream &operator>> (std::istream &in, Time& time)
{
    std::string input;
    in >> input;
    Time t{input};
    if(t.to_string() != input)
    {
        in.setstate(std::ios_base::failbit);
    }
    else{
        time = t;
    }
    return in;
}

Time::operator std::string() const
{
    std::string time = construct_string(h,m,s,false);
    return time;
}

int Time::convert_to_seconds(Time const time) const
{
    int res;
    res = (time.hour()*3600) + (time.minute()*60) + time.second();
    return res;
}

bool Time::operator>(Time const& tr) const
{
    if(h == tr.hour())
    {
        if(m == tr.minute())
        {
            if(s == tr.second())
            {
                return false;
            }
            else if(s < tr.second())
            {
                return false;
            }
        }
        else if(m < tr.minute())
        {
            return false;
        }
    }
    else if(h < tr.hour())
    {
        return false;
    }
    return true;
}
bool Time::operator<(Time const& tr) const
{
    if (*this>=tr)
    {
        return false;
    }
    return true;
}
bool Time::operator<=(Time const& tr) const
{
    if (*this>tr)
    {
        return false;
    }
    return true;
}
bool Time::operator>=(Time const& tr) const
{
    if (tr>*this)
    {
        return false;
    }
    return true;
}

bool Time::operator==(Time const& tr) const
{
    if (*this>=tr && *this<=tr)
    {
        return true;
    }
    return false;
}
bool Time::operator!=(Time const& tr) const
{
    if (*this == tr)
    {
        return false;
    }
    return true;
}

Time& Time::operator--()
{
    *this = *this-1;
    return *this;
}

Time Time::operator--(int)
{
    Time old = *this;
    Time::operator--();
    return old;
}

Time& Time::operator++()
{
    *this = *this+1;
    return *this;
}

Time Time::operator++(int)
{
    Time old = *this;
    Time::operator++();
    return old;
}

Time Time::operator+(int add)
{
    int res = convert_to_seconds(*this)+add;
    int n_time{res};
    if(res < 0)
    {
        while(n_time < 0)
        {
            n_time += 86400;
        }
    }
    else if(res > 86400)
    {
        n_time = res%86400;
    }
    else
    {
        n_time = res;
    }

    h = n_time/3600;

    m =(n_time%3600)/60;

    s = (n_time%60);
    return *this;
}

Time Time::operator-(int sub)
{
    *this = *this+(-sub);
    return *this;
}

void Time::apply_period(std::string &input, bool const format) const
{
    //Apply proper "period" if 12h format
    if(format)
    {
        std::string meridiem = " pm";
        if(h < 12)
        {
            meridiem = " am";
            input += meridiem;
        }else
        {
            meridiem = " pm";
            input += meridiem;
        }
    }
}
bool Time::is_am() const
{
    if(h < 12)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int Time::hour() const
{
    return h;
}
int Time::minute() const
{
    return m;
}
int Time::second() const
{
    return s;
}
