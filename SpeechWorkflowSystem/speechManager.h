#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <deque>
#include <functional>
#include <numeric>
#include "speaker.h"

using namespace std;

class SpeechManager
{
public:
    //构造函数
    SpeechManager();

    //保存第一轮比赛选手编号容器
    vector<int> v1;

    //保存第二轮比赛选手编号容器
    vector<int> v2;

    //保存冠亚季军选手编号容器
    vector<int> vVectory;

    //保存编号及对应具体选手的容器
    map<int, speaker> m_speaker;

    //比赛轮数
    int m_Index;

    //菜单功能
    void showMenu();

    //退出系统
    void exitSystem();

    //初始化容器和属性，凡是在类里面定义的变量，在init函数中都要有初始化操作
    void initSpeech();

    //判断文件是否存在
    bool fileIsexist;

    //创建选手
    void CreateSpeaker();

    //开始比赛
    void startSpeech();

    //选手抽签
    void speechDraw();

    //选手比赛
    void speechContest();

    //显示比赛结果
    void showScore();

    //保存比赛结果
    void saveRecord();

    //保存每届数据
    map<int, vector<string>> m_record;

    //读取比赛记录
    void loadRecord();

    //显示往届记录
    void showRecord();

    //清除比赛记录
    void clearRecord();

    //析构函数
    ~SpeechManager();
};