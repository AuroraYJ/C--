#include <string>
#include <iostream>
#include <ctime>
#include "speechManager.h"

int main()
{
    srand((unsigned int)time(NULL));//以时间创建随机数种子

    SpeechManager sm;

    //test
    // for (map<int,speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end(); it++)
    // {
    //     cout << "选手编号：" << it->first << "姓名：" << it->second.s_Name 
    //     << "分数：" << it->second.s_Score[0] << endl;
    // }

    int choice;

    while (true)
    {
        //展示程序面板
        sm.showMenu();
        cout << "请输入您的选择：";
        cin >> choice;

        switch (choice)
        {
        case 1:
            sm.startSpeech();
            break;
        case 2:
            sm.showRecord();
            break;
        case 3:
            sm.clearRecord();
            break;
        case 0:
            sm.exitSystem();
            break;
        default:
            cout << "输入有误！" << endl;
            system("pause");
            system("cls");
            break;
        }
    }

    system("pause");
    return 0;
}

//第一轮比赛随机分为两组，每组6人

//第二轮比赛选取每组前3名，组成6人一组

//每组顺序抽签决定，展示抽签顺序

//第二轮结束后产生冠亚季军，保存结果至csv文件

//每届比赛结果都可查询

//清空比赛记录

//退出比赛程序