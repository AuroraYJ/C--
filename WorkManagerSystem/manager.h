#pragma once
#include <string>
#include <iostream>
using namespace std;
#include "worker.h"

class manager:public worker
{
public:

    manager(int id, string name, int age, int dselect);

    virtual void showInfo();

    virtual string getdepartname();
};
