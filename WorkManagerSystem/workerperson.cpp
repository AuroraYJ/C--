#include "workerperson.h"

workerperson::workerperson()
{
    this->printPage();
    ifstream ifs;
    ifs.open(FILENAME, ios::in | ios::binary);
    char ch;
    ifs >> ch;
    if (!ifs.is_open())
    {
        cout << "文件打开失败" << endl;
        //要记得初始化角色人数和数组
        this->workerNum = 0;
        this->workerArray = NULL;
        ifs.close();
    }
    else if (ifs.eof())
    {
        cout << "暂无任何角色信息" << endl;
        this->workerNum = 0;
        this->workerArray = NULL;
        ifs.close();
    }
    else
    {
        this->initWorker();
    }
    system("pause");
    system("cls");
}

void workerperson::printPage()
{
    cout << "****************************" << endl;
    cout << "*****红楼梦角色管理系统*****" << endl;
    cout << "*******0.退出管理系统*******" << endl;
    cout << "*******1.增加角色信息*******" << endl;
    cout << "*******2.显示角色信息*******" << endl;
    cout << "*******3.删除角色信息*******" << endl;
    cout << "*******4.修改角色信息*******" << endl;
    cout << "*******5.查找角色信息*******" << endl;
    cout << "*******6.按照编号排序*******" << endl;
    cout << "*******7.清空角色信息*******" << endl;
    cout << "****************************" << endl;
    cout << endl;
}

void workerperson::initWorker()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in | ios::binary);
    int num = this->getNum();
    this->workerNum = num;
    this->workerArray = new worker *[this->workerNum];
    int id;
    string name;
    int age;
    int dselect;
    int index = 0;
    cout << "红楼梦角色总人数为：" << this->workerNum << endl;
    // 这种读取方式遇见空格即停止读取
    while (ifs >> id && ifs >> name && ifs >> age && ifs >> dselect)
    {
        worker *worker = NULL;
        if (dselect==1)
        {
            worker = new employee(id, name, age, dselect); 
        }
        else if (dselect==2)
        {
            worker = new manager(id, name, age, dselect);
        }
        else if (dselect==3)
        {
            worker = new boss(id, name, age, dselect);
        }
        else
        {
            cout << "角色信息有误" << endl;
            system("pause");
        }
        this->workerArray[index] = worker;
        index++;
    }
    ifs.close();
}

int workerperson::getNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in | ios::binary);
    int id;
    string name;
    int age;
    int dselect;
    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> age && ifs >> dselect)
    {
        index++;
    }
    ifs.close();
    return index;
}

bool workerperson::isRepid(int id)
{
    for (int i = 0; i < this->workerNum; i++)
    {
        if (id == this->workerArray[i]->p_id)
        {
            return true;
        }
    }
    return false;
}

void workerperson::addWorker()
{
    cout << "请输入新角色数目：" << endl;
    int addNum = 0;
    cin >> addNum;
    if (addNum > 0)
    {
        int newSize = this->workerNum + addNum;
        worker ** newSpace = new worker* [newSize];
        if (this->workerArray != NULL )
        {
            for (int i = 0; i < this->workerNum; i++)
            {
                newSpace[i] = this->workerArray[i];
            }
        }
        
        for (int i = 0; i < addNum; i++)
        {
            int id = -1;
            string name;
            int age;
            int dselect;
            cout << "请输入新人物第" << i + 1 << "个角色编号：" << endl;
            cin >> id;
            bool isrepid = true;
            while (isrepid)
            {
                for (int j = 0; j < this->workerNum + i; j++)
                {
                    if (id == newSpace[j]->p_id || this->isRepid(id))
                    {
                        cout << "角色编号" << id << "已存在" << endl;
                        cout << "请重新输入新人物第" << i + 1 << "个角色编号：" << endl;
                        cin >> id;
                    }
                    else
                    {
                        isrepid = false;
                    }
                }
            }                          
            cout << "请输入新人物第" << i + 1 << "个角色姓名：" << endl;
            cin >> name;
            cout << "请输入新人物第" << i + 1 << "个角色年龄：" << endl;
            cin >> age;
            cout << "请输入新人物第" << i + 1 << "个角色身份编码：" << endl;
            cout << "1.仆从丫鬟" << endl;
            cout << "2.世家子弟" << endl;
            cout << "3.大家长" << endl;
            cin >> dselect;

            worker* worker = NULL;
            switch (dselect)
            {
            case 1:
                worker = new employee(id, name, age, dselect); 
                break;
            case 2:
                worker = new manager(id, name, age, dselect);
                break;
            case 3:
                worker = new boss(id, name, age, dselect);
                break;
            default:
                cout << "输入有误" << endl;
                break;
            }
            newSpace[this->workerNum + i] = worker;
            cout << "添加成功" << endl;  
        }
        delete [] this->workerArray;
        this->workerNum = newSize;
        this->workerArray = newSpace;
        this->saveWorker();
        cout << "成功添加" << addNum << "名新角色" << endl;
    }
    else
    {
        cout << "输入有误" << endl;
    }
    system("pause");
    system("cls");
}

void workerperson::showInfo()
{
    if (this->isEmpty() == 1)
    {
        for (int i = 0 ; i < this->workerNum; i++)
        {
            this->workerArray[i]->showInfo();
        }
    }
    else
    {
        cout << "记录不存在" << endl;
    }
    system("pause");
    system("cls");
}

int workerperson::isEmpty()
{
    int isEmpty = 1;
    if (this->workerNum == 0)
    {
        cout << "暂无角色信息" << endl;
        isEmpty = -1;
    }
    return isEmpty;
}

int workerperson::isExist(int id)
{
    int index = -1;
    for (int i = 0 ; i < this->workerNum; i++)
    {
        if (this->workerArray[i]->p_id == id)
        {
            index = i;
            break;
        }
    }
    return index;
}

void workerperson::delInfo()
{
    cout << "请输入离开角色编号：" << endl;
    int id = 0;
    cin >> id;
    int del = 0;
    
    if (this->isExist(id) != -1)
    {
        cout << "找到角色编号为" << id << "的角色，角色信息如下所示：" << endl;
        this->workerArray[this->isExist(id)]->showInfo();
        cout << "请确认是否删除？\t1、确认\t2、取消" << endl;
        cin >> del;
        switch (del)
        {
        case 1:
            for (int i = id; i < this->workerNum - 1; i++)
            {
                this->workerArray[i] = this->workerArray[i+1];
            }
            this->workerNum--;
            cout << "成功删除该名角色" << endl;
            this->saveWorker();
            break;
        case 2:
            break;
        default:
            cout << "输入有误" << endl;
            break;
        }   
    }
    else
    {
        cout << "查无此人" << endl;
    }
    system("pause");
    system("cls");
}

void workerperson::modInfo()
{
    cout << "请输入需要修改的角色编号：" << endl;
    int id;
    cin >> id;

    if (this->isExist(id) != -1)
    {
        cout << "找到角色编号为" << id << "的角色，角色信息如下所示：" << endl;
        this->workerArray[this->isExist(id)]->showInfo();
        int newId;
        string newName;
        int newAge;
        int newDselect;
        cout << "请输入新编号:" << endl;
        cin >> newId;
        while(this->isRepid(newId) && newId != id)
        {
            cout << "角色编号" << newId << "已存在" << endl;
            cout << "请重新输入人物修改后的：" << endl;
            cin >> newId;
        }
        cout << "请输入新姓名:" << endl;
        cin >> newName;
        cout << "请输入新年龄:" << endl;
        cin >> newAge;
        cout << "请输入新身份:" << endl;
        cout << "1.仆从丫鬟" << endl;
        cout << "2.世家子弟" << endl;
        cout << "3.大家长" << endl;
        cin >> newDselect;

        worker * worker;
        switch (newDselect)
        {
        case 1:
            worker = new employee(newId, newName, newAge, newDselect); 
            break;
        case 2:
            worker = new manager(newId, newName, newAge, newDselect);
            break;
        case 3:
            worker = new boss(newId, newName, newAge, newDselect);
            break;
        default:
            cout << "输入有误" << endl;
            break;
        }
        this->workerArray[this->isExist(id)] = worker;
        this->saveWorker();
    }
    else
    {
        cout << "查无此人" << endl;
    }
    system("pause");
    system("cls");
}

void workerperson::findInfo()
{
    cout << "请输入查找方式：" << endl;
    cout << "1.查找角色编号" << endl;
    cout << "2.查找角色姓名" << endl;
    int choice = 0;
    cin >> choice;
    if (choice == 1)
    {
        cout << "请输入需要查找的角色编号：" << endl;
        int findId;
        cin >> findId;
        if (this->isExist(findId) != -1)
        {
            cout << "找到编号为" << findId << "的角色，角色信息如下所示：" << endl;
            this->workerArray[this->isExist(findId)]->showInfo();
        }
        else
        {
            cout << "查无此人" << endl;
        }
    }
    else if (choice == 2)
    {
        cout << "请输入需要查找的角色姓名：" << endl;
        string findName;
        int findId = -1;
        cin >> findName;
        for (int i = 0 ; i < this->workerNum; i ++)
        {
            if (this->workerArray[i]->p_name == findName)
            {
                findId = i;
                cout << "找到姓名为" << findName << "的角色，角色信息如下所示：" << endl;
                this->workerArray[this->isExist(findId)]->showInfo();
            }
        }
        if (findId == -1)
        {
            cout << "查无此人" << endl;
        }
    }
    else
    {
        cout << "输入有误" << endl;
    }
    
    system("pause");
    system("cls");
}

void workerperson::sortWorker()
{
    cout << "请输入排序方式:" << endl;
    cout << "1、升序\t2、降序" << endl;
    int sortMethod;
    cin >> sortMethod;
    for (int i = 0; i < this->workerNum; i++ )
    {
        int mIndex = i;
        for (int j = i + 1; j < this->workerNum; j++)
        {
            if (sortMethod==1)
            {
                if (this->workerArray[j]->p_id < this->workerArray[mIndex]->p_id)
                {
                    mIndex = j;
                }
            }
            else if (sortMethod==2)
            {
                if (this->workerArray[j]->p_id > this->workerArray[mIndex]->p_id)
                {
                    mIndex = j;
                }
            }            
        }
        if (i != mIndex)
        {
            worker *temp = this->workerArray[i];
            this->workerArray[i] = this->workerArray[mIndex];
            this->workerArray[mIndex] = temp;       
        }
    }
    this->saveWorker();
    cout << "排序成功" << endl;
    system("pause");
    system("cls");
}

void workerperson::clearWorker()
{
    cout << "清空操作将清空全部角色信息，是否继续?" << endl;
    cout << "1、确定\t2、取消" << endl;
    int clearInfo;
    cin >> clearInfo;
    switch (clearInfo)
    {
    case 1:
        {
            ofstream ofs;
            ofs.open(FILENAME, ios::trunc);
            ofs.close();
            if (this->workerArray != NULL)
            {
                for (int i = 0 ; i < this->workerNum; i ++)
                {
                    delete this->workerArray[i];
                    this->workerArray[i] = NULL;
                }
            }
            delete [] this->workerArray;
            this->workerArray = NULL;
            this->workerNum = 0;
            cout << "清空成功" << endl;
            break;
        }
    case 2:
        break;
    default:
        cout << "输入错误" << endl;
        break;
    }
    system("pause");
    system("cls");
}

void workerperson::saveWorker()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out | ios::binary);
    for (int i = 0 ; i < this->workerNum; i++)
    {
        ofs << this->workerArray[i]->p_id << " "
        << this->workerArray[i]->p_name << " "
        << this->workerArray[i]->p_age << " "
        << this->workerArray[i]->p_dselect << endl;
    }
    ofs.close();
    cout << "角色信息已保存" << endl;
}

workerperson::~workerperson()
{
    if (this->workerArray != NULL)
    {
        for (int i = 0 ; i < this->workerNum ; i ++ )
        {
            if (this->workerArray[i] != NULL)
            {
                delete this->workerArray[i];
            }
        }
        delete [] this->workerArray;
        this->workerArray = NULL;
    }
}
