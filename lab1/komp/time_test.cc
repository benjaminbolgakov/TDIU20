#include <string>
#include <iostream>
#include <sstream>

#include "catch.hpp"
#include "Time.h"

using namespace std;

TEST_CASE ("Default constructor")
{
    Time t;

    CHECK(t.hour() == 0);
    CHECK(t.minute() == 0);
    CHECK(t.second() == 0);
}

TEST_CASE ( "Constructor with numeric arguments" )
{
    Time t{12,13,14};
    CHECK(t.hour() == 12);
    CHECK(t.minute() == 13);
    CHECK(t.second() == 14);
}

TEST_CASE ("Constructor with faulty argument")
{
    CHECK_THROWS( Time{41,0,0} );
    CHECK_THROWS( Time{0,99,0} );
    CHECK_THROWS( Time{0,0,99} );
}

TEST_CASE ("String constructor")
{
    Time t{"12:23:12"};
    CHECK(t.hour() == 12);
    CHECK(t.minute() == 23);
    CHECK(t.second() == 12);

    SECTION ("Throws as well")
    {
        CHECK_THROWS( Time{"02:11:74"} );
    }
}

TEST_CASE ("am or pm")
{
    Time t{12,12,31};
    CHECK_FALSE(t.is_am());
    Time t2{1,2,3};
    CHECK(t2.is_am());
}

TEST_CASE ("Convert to string" )
{
    CHECK( Time{12,12,12}.to_string()     ==    "12:12:12" );
    CHECK( Time{12, 1, 2}.to_string()     ==    "12:01:02" );
    CHECK( Time{14,33,12}.to_string(true) == "02:33:12 pm" );
}

TEST_CASE ("Conversion to string" )
{
    CHECK( string(Time{2,4,1}) == "02:04:01" );
}

TEST_CASE ("Output operator" )
{
    stringstream ss;
    SECTION("Simple output")
    {
        ss << Time{2,5,1};
        CHECK(ss.str() == "02:05:01");
    }
    SECTION("Chained output")
    {
        ss << Time{23,10,32} << "---";
        CHECK(ss.str() == "23:10:32---");
    }
    SECTION("Const time")
    {
        Time const t{23,23,23};
        ss << t;
        CHECK(ss.str() == "23:23:23");
    }
}

TEST_CASE ("Input operator" )
{
    SECTION("Simple output")
    {
        istringstream iss{"02:02:0a"};
        Time t{};
        iss >> t;
        CHECK(iss.fail());
        CHECK(t.to_string() == "00:00:00");
    }
}

TEST_CASE ("Add integer N in seconds pos/neg")
{
    Time t{10,10,10};
    t+(-86401);
    CHECK(t.to_string() == "10:10:09");
    t+(10);
    CHECK(t.to_string() == "10:10:19");
}

TEST_CASE ("Decrement by one")
{
    Time t{10,0,0};
    --t;
    CHECK(t.to_string() == "09:59:59");
}
TEST_CASE ("Post inc")
{
    Time t1{};
    Time t2{};
    t1 = t2++;
    CHECK(t1.to_string() == "00:00:00");
    CHECK(t2.to_string() == "00:00:01");
}
TEST_CASE ("Pre inc")
{
    Time t1{};
    Time t2{};
    t1 = ++t2;
    CHECK(t1.to_string() == "00:00:01");
    CHECK(t2.to_string() == "00:00:01");
}
TEST_CASE ("Post dec")
{
    Time t1{};
    Time t2{};
    t1 = t2--;
    CHECK(t1.to_string() == "00:00:00");
    CHECK(t2.to_string() == "23:59:59");
}
TEST_CASE ("Pre dec")
{
    Time t1{};
    Time t2{};
    t1 = --t2;
    CHECK(t1.to_string() == "23:59:59");
    CHECK(t2.to_string() == "23:59:59");
}
TEST_CASE ("Compare")
{
    Time t1{13,12,12};
    Time t2{14,12,12};
    CHECK_FALSE(t1>t2);
    CHECK(t2>=t1);
    CHECK(t1!=t2);
    CHECK(t1<t2);
    CHECK(t1<=t2);
    Time t3{12,12,12};
    Time t4{12,12,12};
    CHECK(t3>=t4);
    CHECK(t4<=t3);
    CHECK(t4==t3);
}

TEST_CASE ("Sub integer N in seconds pos/neg")
{
    Time t{10,10,10};
    t-(11);
    CHECK(t.to_string() == "10:09:59");
    t-(-1);
    CHECK(t.to_string() == "10:10:00");
    Time t2{};
    CHECK((t2 - 259200).to_string() == "00:00:00");
}

#if 0
#endif
