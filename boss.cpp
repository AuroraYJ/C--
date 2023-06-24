#include "boss.h"

boss::boss(int id, string name, int age, int dselect)
{
    this->p_id = id;
    this->p_dselect = dselect;
    this->p_age = age;
    this->p_name = name;
}

void boss::showInfo()
{
    cout << "角色编号：" << this->p_id 
    << "\t角色姓名：" << this->p_name 
    << "\t角色年龄：" << this->p_age 
    << "\t身份地位：" << this->getdepartname()
    << "\t身份职责：维系贾府氏族大家的体面" << endl;
}

string boss::getdepartname()
{
    string departname = "大家长";
    return departname;
}