#pragma once
#include <string>
#include <iostream>
using namespace std;

class worker
{
public:
    int p_id;
    string p_name;
    int p_age;
    int p_dselect;

    virtual void showInfo() = 0;

    virtual string getdepartname() = 0;
};