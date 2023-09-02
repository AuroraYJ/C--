#include <iostream>
#include <fstream>
#include <algorithm>
#include "speechManager.h"
#include "speaker.h"

using namespace std;

SpeechManager::SpeechManager()
{
    //初始化容器和属性
    this->initSpeech();
    //创建12名学生
    this->CreateSpeaker();
    //加载往届记录
    this->loadRecord();
}

void SpeechManager::showMenu()
{
    cout << "****************************" << endl;
    cout << "******欢迎参加演讲比赛******" << endl;
    cout << "*******1.开始演讲比赛*******" << endl;
    cout << "*******2.查看往届记录*******" << endl;
    cout << "*******3.清空比赛记录*******" << endl;
    cout << "*******0.退出比赛程序*******" << endl;
    cout << "****************************" << endl;
    cout << endl;
}

void SpeechManager::initSpeech()
{
    this->v1.clear();
    this->v2.clear();
    this->vVectory.clear();
    this->m_speaker.clear();

    this->m_Index = 1;

    this->m_record.clear();
}

void SpeechManager::exitSystem()
{
    cout << "欢迎您下次使用！" << endl;
    system("pause");
    exit(0);
}

void SpeechManager::CreateSpeaker()
{
    string nameseed = "ABCDEFGHIJKL";

    for (int i=0; i < nameseed.size(); i++)
    {
        string name = "Speaker";
        name += nameseed[i];

        //初始化选手类
        speaker sp;
        //将每个选手复制到speaker类中成员函数
        sp.s_Name = name;
        for (int j = 0; j < 2; j++)
        {
            sp.s_Score[j] = 0.0;
        }

        //编号
        this->v1.push_back(i + 10001);
        //map容器插入insert
        this->m_speaker.insert(pair<int,speaker>(i+10001,sp));
    }

}

void SpeechManager::startSpeech()
{
    //第一轮比赛
    //1、抽签
    this->speechDraw();
    //2、比赛
    this->speechContest();
    //3、显示比赛结果
    this->showScore();
    //第二轮比赛
    this->m_Index++;
    //1、抽签
    this->speechDraw();
    //2、比赛
    this->speechContest();
    //3、显示比赛结果
    this->showScore();
    //4、保存前三名选手成绩
    this->saveRecord();

    //重置本届记录
    this->initSpeech();

    this->CreateSpeaker();

    this->loadRecord();

    cout << "本届比赛完毕！" << endl;

    system("pause");
    system("cls");
}

void SpeechManager::speechDraw()
{
    cout << "第" << this->m_Index << "轮比赛选手正在抽签" << endl;
    cout << "-----------------------------" << endl;
    cout << "抽签后演讲顺序如下" << endl;

    if (this->m_Index == 1)
    {
        //第一轮
        random_shuffle(v1.begin(),v1.end());//打乱v1容器的顺序，洗牌算法需要包括头文件algorithm

        //遍历输出打乱后选手编号
        for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
        {
            cout << *it << " ";
        }

        cout << endl;
    }
    else
    {
        //第二轮
        random_shuffle(v2.begin(),v2.end());

        for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
        {
            cout << *it << " ";
        }

        cout << endl;
    }
    cout << "-----------------------------" << endl;
    system("pause");
}

void SpeechManager::speechContest()
{
    cout << "-------第" << this->m_Index << "比赛正式开始-------" << endl;

    //准备临时容器存放小组成绩，存放前三名的平均分和编号，使用降序
    //set和map默认是升序less<T>
    multimap<double, int, greater<double>> groupScore;

    int num = 0; //记录人员个数6人一组

    vector<int> v_Scr;//比赛选手容器，第一轮赋值v1，第二轮赋值v2
    if (this->m_Index == 1)
    {
        v_Scr = v1;
    }
    else
    {
        v_Scr = v2;
    }

    //遍历全部选手进行比赛
    for (vector<int>::iterator it = v_Scr.begin(); it != v_Scr.end(); it++)
    {
        num++;
        //评委打分使用deque容器的原因：去除最高和最低分deque容器有pop_front和pop_back
        deque<double> d;
        for (int i = 0; i < 10; i++)
        {
            //对rand随机数的理解：rand()%401表示0至400的随机数，因为整数对401取余的值是0至400
            double score = (rand() % 401 + 600) / 10.f; //600 ~ 1000的随机数
            //cout << score << " ";
            d.push_back(score);
        }
        //cout << endl;

        sort(d.begin(), d.end(), greater<double>());//排序，从头到尾降序
        d.pop_back();//去掉最低分
        d.pop_front();//去掉最高分

        double sum = accumulate(d.begin(),d.end(),0.0f);//总分
        double avg = sum / (double)d.size();//平均分

        //打印平均分
        //cout << "编号：" << *it << "姓名：" << this->m_speaker[*it].s_Name
        //<< "获取的平均分为：" << avg << endl;

        //将平均分放入到map容器里，map容器重载了[]运算符*it即m_speaker的索引
        this->m_speaker[*it].s_Score[this->m_Index - 1] = avg;

        //将打分数据分数和编号放到临时小组容器中
        groupScore.insert(make_pair(avg, *it));//key为得分，value是具体选手编号，*it即m_speaker的索引

        //每6人取出前3名
        if (num % 6 == 0)
        {
            cout << "第" << num / 6 << "小组比赛名次：" << endl;
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
            {
                cout << "编号：" << it->second << "姓名：" << this->m_speaker[it->second].s_Name
                        << "成绩：" << this->m_speaker[it->second].s_Score[this->m_Index - 1] << endl;
            }

            //取走前三名
            int count = 0;
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
            {
                if (this->m_Index == 1)
                {
                    v2.push_back((*it).second);
                }
                else
                {
                    vVectory.push_back((*it).second);
                }
            }

            cout << endl;
            groupScore.clear();//小组容器清空，保证6个数据存一次
        }
    }
    cout << "---------第" << this->m_Index << "轮比赛完毕--------" << endl;
    system("pause");
}

void SpeechManager::showScore()
{
    cout << "-------第" << this->m_Index << "轮晋级选手信息如下------" << endl;
    vector<int> v;

    if (this->m_Index == 1)
    {
        v = v2;
    }
    else
    {
        v = vVectory;
    }

    //遍历输出 score也是数组，需要有索引值m_Index - 1
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "编号：" << *it << "姓名：" << this->m_speaker[*it].s_Name
        << "分数：" << this->m_speaker[*it].s_Score[this->m_Index - 1] << endl;
    }

    cout << endl;
    system("pause");
    system("cls");

    this->showMenu();
}

void SpeechManager::saveRecord()
{
    ofstream ofs;
    ofs.open("speech.csv", ios::out | ios::app);

    for (vector<int>::iterator it = vVectory.begin(); it != vVectory.end(); it++)
    {
        ofs << *it << "," << this->m_speaker[*it].s_Score[1] << ",";
    }
    ofs << endl;

    ofs.close();
    cout << "记录已经保存" << endl;

}

void SpeechManager::loadRecord()
{
    ifstream ifs("speech.csv", ios::in);

    //如果文件不存在则返回null
    if (!ifs.is_open())
    {
        this->fileIsexist = true;
        cout << "文件打开失败" << endl;
        ifs.close();
        return;
    }
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        cout << "文件为空" << endl;
        this->fileIsexist = true;
        ifs.close();
        return;
    }

    this->fileIsexist = false;

    //将上面ifs >> ch读取的单个字符放回来否则会少个字符
    ifs.putback(ch);

    string data;
    int index = 0; //默认第0届

    //ifs一直读data，直读到末尾，在此过程中一直输出data
    while (ifs >> data)
    {
        //cout << data << endl;
        vector<string> v;//存放6个string

        int pos = -1; //查到","位置的变量
        int start = 0; //起始位置

        while (true)
        {
            pos = data.find(",",start);//find第二个参数默认起始位置为0，若未找到返回-1
            if (pos == -1)
            {
                //没有找到
                break;
            }
            //第一个参数是开始截取的位置，第二个参数是截取的长度
            string temp = data.substr(start, pos - start);
            //cout << temp << endl;
            v.push_back(temp);

            start = pos + 1;//下一次进入循环是从逗号下一个字符开始判断
        }
        
        this->m_record.insert(make_pair(index, v));
        index++;
    }
    ifs.close();

    // for (map<int, vector<string>>::iterator it = m_record.begin(); it != m_record.end(); it++)
    // {
    //     cout << "第" << it->first << "届演讲比赛获胜者信息如下：" << endl;
    //     cout << "冠军编号：" << it->second[0] << " " << "分数：" << it->second[1] << endl;
    // }
}

void SpeechManager::showRecord()
{
    if (this->fileIsexist)
    {
        cout << "往届信息为空！" << endl;
    }
    else
    {
        for (map<int, vector<string>>::iterator it = this->m_record.begin(); it != this->m_record.end(); it++)
        {
            cout << "第" << it->first + 1 << "届演讲比赛获胜者信息如下：" << endl;
            cout << "冠军编号：" << it->second[0] << " " << "分数：" << it->second[1] << endl;
            cout << "亚军编号：" << it->second[2] << " " << "分数：" << it->second[3] << endl;
            cout << "季军编号：" << it->second[4] << " " << "分数：" << it->second[5] << endl;
        }
    }
    system("pause");
    system("cls");
}

void SpeechManager::clearRecord()
{
    cout << "是否确定清空文件？" << endl;
    cout << "1.是" << endl;
    cout << "2.否" << endl;

    int select = 0;
    cin >> select;

    if (select == 1)
    {
        //确认清空
        ofstream ofs("speech.csv", ios::trunc);
        ofs.close();

        //初始化容器
        this->initSpeech();

        //创建12名选手
        this->CreateSpeaker();

        //加载往届记录
        this->loadRecord();
        
        cout << "清空成功！" << endl;
    }

    system("pause");
    system("cls");
}

SpeechManager::~SpeechManager()
{
    
}