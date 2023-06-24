#pragma once
#include <string>
#include <iostream>
using namespace std;
#include "worker.h"

class employee:public worker
{
public:

    employee(int id, string name, int age, int dselect);

    virtual void showInfo();

    virtual string getdepartname();
};