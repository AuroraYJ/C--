#include "manager.h"

manager::manager(int id, string name, int age, int dselect)
{
    this->p_id = id;
    this->p_dselect = dselect;
    this->p_age = age;
    this->p_name = name;
}

void manager::showInfo()
{
    cout << "角色编号：" << this->p_id 
    << "\t角色姓名：" << this->p_name 
    << "\t角色年龄：" << this->p_age 
    << "\t身份地位：" << this->getdepartname()
    << "\t身份职责：履行作为贾府晚辈的职责" << endl;
}

string manager::getdepartname()
{
    string departname = "世家子弟";
    return departname;
}
