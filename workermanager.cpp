#include <string>
#include <iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include "workerperson.h"

int main()
{
    workerperson wp;
    int select = 0;
    while(true)
    {
        wp.printPage();

        cout << "请输入您的选择:" << endl;
        cin >> select;

        switch (select)
        {
        case 0:
            cout << "欢迎下次使用" << endl;
            system("pause");
            exit(0);
            break;
        case 1:
            wp.addWorker();
            break;
        case 2:
            wp.showInfo();
            break;
        case 3:
            wp.delInfo();
            break;
        case 4:
            wp.modInfo();
            break;
        case 5:
            wp.findInfo();
            break;
        case 6:
            wp.sortWorker();
            break;
        case 7:
            wp.clearWorker();
            break;
        default:
            system("pause");
            break;
        }
    }
    system("pause");
    return 0;
}