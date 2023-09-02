#include <string>
#include <iostream>
#include <fstream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#define FILENAME "WorkerInformation.txt"

class workerperson
{
public:
    int workerNum ;
    worker ** workerArray;

    workerperson();

    void printPage();

    void initWorker();

    bool isRepid(int id);

    void addWorker();

    void showInfo();

    void delInfo();

    int isEmpty();

    int isExist(int id);

    void modInfo();

    void findInfo();

    void sortWorker();

    void clearWorker();

    void saveWorker();

    int getNum();

    ~workerperson();
};
