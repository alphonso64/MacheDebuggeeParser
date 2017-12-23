#ifndef MACHINEDEBUGPARAM_H
#define MACHINEDEBUGPARAM_H

#include<string>
#include <list>
#include <map>
#include <json/json.h>
using namespace std;
#define FLAG_SERVO 2
#define FLAG_STEP 1

class ShiftParam
{
public:
    int id;
    int flag;
    int num;
};


class ListShiftParam
{
public:
    string description;
    list<ShiftParam> servoParam;
    list<ShiftParam> stepParam;
};

class ControlParam
{
public:
      int CONFIG_INFO_MASTER_BELT_SPEED   ;//主皮带
      int CONFIG_INFO_SLAVE_BELT_SPEED    ;//翻转皮带

      int CONFIG_INFO_PILE_SPEED         ;    //堆叠速度
      int CONFIG_INFO_PILE_DELAY          ;//堆叠延时
      int CONFIG_INFO_PILE_COUNTER       ;//堆叠距离

      int CONFIG_INFO_SORTER_DELAY      ;//分拣延时
      int CONFIG_INFO_SORTER_COUNTER     ;//分拣距离
      int CONFIG_INFO_SORTER_INIT_DELAY  ;//分拣初始化延时
      int CONFIG_INFO_SORTER_INIT_COUNTER ;//分拣初始化距离
};

class CamParam
{
    public:
        CamParam(int camNo,int  camPosition,int segH,int segW,string netPath,
                 float ratioH,float ratioW,int limitH,int limitW,
                 int threadH,int threadW,int area,int exposureTime,
                 int delayTime)
        {
            this->camNo = camNo;
            this->camPosition = camPosition;
            this->exposureTime = exposureTime;
            this->delayTime = delayTime;
            this->segW = segW;
            this->segH = segH;
            this->netPath = netPath;
            this->ratioW = ratioW;
            this->ratioH = ratioH;
            this->limitH = limitH;
            this->limitW = limitW;
            this->resArea = area;
            this->threadH = threadH;
            this->threadW = threadW;
        }
        int exposureTime;
        int delayTime;
        int camNo;
        int camPosition;
        int segW;
        int segH;
        string netPath;
        float ratioW;
        float ratioH;
        int threadH;
        int threadW;
        int limitH;
        int limitW;
        int resArea;
};

class LightParam
{
public:
    int lightStep;
    string lightPort;
};

class ListLightParam
{
public:
    list<LightParam> listLightParam;
    string lightSerial;
};

class DeviceParam
{
public:
    map<int,CamParam> camparams;
    ListLightParam lightParams;
};

class ProductConfig
{
public:
    void readFile(const char *path);
    static void writeFile(const char *path);
    void printInfo();

    list<ListShiftParam> shiftParams;
    ControlParam controlParam;
    string productName;
    map<int,DeviceParam > deviceParams;
};






#endif // MACHINEDEBUGPARAM_H
