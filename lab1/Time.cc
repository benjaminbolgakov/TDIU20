// I denna fil läggs definitionerna (implementationen) av de funktioner
// som deklarerats i Time.h
// w++17 test_main.o Time.cc time_test.cc
#include "Time.h"

Time::Time(int hour, int minute, int second)
    : h{hour}, m{minute}, s{second}, am{false}
{
    if(hour < 0 || hour > 23 ||
       minute < 0 || minute > 59 ||
       second < 0 || second > 59)
    {
        throw std::logic_error{"Invalid time value"};
    }
    if(hour < 12)
    {
        am = true;
    }
}
Time::Time(std::string const& time)
    : h{}, m{}, s{}, am{}
{
    char c;
    std::stringstream ss;
    ss << time;
    ss >> h >> c >> m >> c >> s;
    if(h < 0 || h > 23 ||
       m < 0 || m > 59 ||
       s < 0 || s > 59)
    {
        throw std::logic_error("Invalid time value");
    }
}


std::string Time::to_string(bool format)
{
    std::string formatted;
    //format indicates wether or not to use 12hr format
    formatted = construct_string(h,m,s,format);
    return formatted;
}
int Time::transform_format(int const h, bool format)
{
    int result = h;
    if(format && h > 12)
    {
        //Transform from 24h format to 12h
        result = h-12;
    }else
    {
        //Transform from 12h to 24h
        //TODO
    }
    return result;
}
std::string Time::construct_string(int const h, int const m, int const s, bool format)
{
    std::string time;
    std::vector<int> v = {transform_format(h,format),m,s};
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

Time::operator std::string()
{
    std::string time = construct_string(h,m,s,false);
    return time;
}

bool operator>(Time const tl, Time const tr)
{
    if(tl.hour() == tr.hour())
    {
        if(tl.minute() == tr.minute())
        {
            if(tl.second() == tr.second())
            {
                return false;
            }
            else if(tl.second() < tr.second())
            {
                return false;
            }
        }
        else if(tl.minute() < tr.minute())
        {
            return false;
        }
    }
    else if(tl.hour() < tr.hour())
    {
        return false;
    }
    return true;
}

bool operator<=(Time const tl, Time const tr)
{
    if (tl>tr)
    {
        return false;
    }
    return true;
}
bool operator>=(Time const tl, Time const tr)
{
    if (tr>tl)
    {
        return false;
    }
    return true;
}
bool operator<(Time const tl, Time const tr)
{
    if (tl>=tr)
    {
        return false;
    }
    return true;
}
bool operator==(Time const tl, Time const tr)
{
    if (tl>=tr && tl<=tr)
    {
        return true;
    }
    return false;
}
bool operator!=(Time const tl, Time const tr)
{
    if (tl == tr)
    {
        return false;
    }
    return true;
}

Time& Time::operator--()
{
    if (s > 0)
    {
        s-=1;
    }
    else if (m > 0 && s == 0)
    {
        s=59;
        m-=1;
    }
    else if (h > 0 && m == 0 && s == 0)
    {
        s=59;
        m=59;
        h-=1;
    }
    else
    {
        s=59;
        m=59;
        h=23;
    }
    return *this;
}

Time& Time::operator++()
{
    if (s < 59)
    {
        s+=1;
    }
    else if (m < 59 && s == 59)
    {
        s=0;
        m+=1;
    }
    else if (h < 23 && m == 59 && s == 59)
    {
        s=0;
        m=0;
        h+=1;
    }
    else
    {
        s=0;
        m=0;
        h=0;
    }
    return *this;
}

int Time::convert_to_seconds(Time const time)
{
    int res;
    res = (time.hour()*3600) + (time.minute()*60) + time.second();
    return res;
}

Time Time::operator+(int add)
{
    int res = convert_to_seconds(*this)+add;
    int n_time;
    if (res < 0)
    {
        n_time = 86400+res;
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

//Using reference
void Time::apply_period(std::string &input, bool const format)
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
    return am;
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
