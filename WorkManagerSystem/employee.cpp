//头文件中已经引用了库，无需重新引用
#include "employee.h"

employee::employee(int id, string name, int age, int dselect)
{
    this->p_id = id;
    this->p_dselect = dselect;
    this->p_age = age;
    this->p_name = name;
}

void employee::showInfo()
{
    cout << "角色编号：" << this->p_id 
    << "\t角色姓名：" << this->p_name 
    << "\t角色年龄：" << this->p_age 
    << "\t身份地位：" << this->getdepartname()
    << "\t身份职责：完成诗书簪缨世家吩咐的任务" << endl;
}

string employee::getdepartname()
{
    string departname = "仆从丫鬟";
    return departname;
}
