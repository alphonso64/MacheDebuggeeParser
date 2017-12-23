#include "machinedebugparam.h"
#include <ostream>
#include <fstream>
#include <QString>
#include <QDebug>
#include <sstream>

template<typename T> string toString(const T& t){
    ostringstream oss;  //创建一个格式化输出流
    oss<<t;             //把值传递如流中
    return oss.str();
}

void ProductConfig::writeFile(const char *path)
{
     map<int,DeviceParam > deviceParams;

     {
         DeviceParam device;

         CamParam camParam1(1,1,3,1,"/home/isee/code/RAW/config/side_net_G_v3.pth",1.2,1.4,40,40,80,80,1,400,2);
         CamParam camParam2(2,1,3,2,"/home/isee/code/RAW/config/side_net_G_v3.pth",1.2,1.4,40,40,80,80,1,300,33);
         CamParam camParam3(3,2,2,3,"/home/isee/code/RAW/config/back_net_G_728.pth",1.3,1.2,100,100,80,80,1,200,44);
         CamParam camParam4(4,2,2,4,"/home/isee/code/RAW/config/back_net_G_728.pth",1.2,1.4,100,100,120,120,1,100,55);
         device.camparams.insert(pair<int,CamParam>(1,camParam1));
         device.camparams.insert(pair<int,CamParam>(2,camParam2));
         device.camparams.insert(pair<int,CamParam>(3,camParam3));
         device.camparams.insert(pair<int,CamParam>(4,camParam4));


         device.lightParams.lightSerial = "ttyS9";
         LightParam light_a;
         light_a.lightPort = "sa";
         light_a.lightStep = 255;
         device.lightParams.listLightParam.push_back(light_a);

         LightParam light_b;
         light_b.lightPort = "sb";
         light_b.lightStep = 255;
         device.lightParams.listLightParam.push_back(light_b);

         deviceParams.insert(pair<int,DeviceParam >(1,device));
     }

     {
         DeviceParam device;
         device.lightParams.lightSerial = "ttyS9";
         CamParam camParam4(2,1,3,2,"/home/isee/code/RAW/config/side_net_G_v3.pth",1.2,1.4,40,40,80,80,1,300,33);
         device.camparams.insert(pair<int,CamParam>(4,camParam4));


         LightParam light_b;
         light_b.lightPort = "sc";
         light_b.lightStep = 255;
         device.lightParams.listLightParam.push_back(light_b);

         deviceParams.insert(pair<int,DeviceParam >(2,device));
     }

     list<ListShiftParam> shifts;
     ControlParam controlParam;
     ListShiftParam l1,l2,l3,l4;

     l1.description = "front";
     l2.description = "side_left";
     l3.description = "side_right";
     l4.description = "back";
     controlParam.CONFIG_INFO_MASTER_BELT_SPEED = 1000;
     controlParam.CONFIG_INFO_SLAVE_BELT_SPEED = 2000;
     controlParam.CONFIG_INFO_PILE_COUNTER = 12;
     controlParam.CONFIG_INFO_PILE_DELAY = 200;
     controlParam.CONFIG_INFO_PILE_SPEED = 111;
     controlParam.CONFIG_INFO_SORTER_COUNTER = 99;
     controlParam.CONFIG_INFO_SORTER_DELAY = 88;
     controlParam.CONFIG_INFO_SORTER_INIT_COUNTER = 77;
     controlParam.CONFIG_INFO_SORTER_INIT_DELAY = 66;


     for(int i=0;i<4;i++)
     {
        ShiftParam servo_p1,servo_p2,servo_p3,servo_p4;
        ShiftParam step_p1,step_p2,step_p3,step_p4;

        servo_p1.id = i;
        servo_p2.id = i+4;
        servo_p3.id = i+8;
        servo_p4.id = i+12;

        servo_p1.num = i*100;
        servo_p2.num = i*200;
        servo_p3.num = i*300;
        servo_p4.num = i*400;

        servo_p1.flag = -1;
        servo_p2.flag = -2;
        servo_p3.flag = -3;
        servo_p4.flag = -4;


        step_p1.id = 20+i;
        step_p2.id = 24+i;
        step_p3.id = 28+i;
        step_p4.id = 32+i;

        step_p1.num = i*1001;
        step_p2.num = i*2001;
        step_p3.num = i*3001;
        step_p4.num = i*4001;

        step_p1.flag = 1;
        step_p2.flag = 2;
        step_p3.flag = 3;
        step_p4.flag = 4;

        l1.servoParam.push_back(servo_p1);
        l1.stepParam.push_back(step_p1);

        l2.servoParam.push_back(servo_p2);
        l2.stepParam.push_back(step_p2);

        l3.servoParam.push_back(servo_p3);
        l3.stepParam.push_back(step_p3);

        l4.servoParam.push_back(servo_p4);
        l4.stepParam.push_back(step_p4);

     }
    shifts.push_back(l1);
    shifts.push_back(l2);
    shifts.push_back(l3);
    shifts.push_back(l4);

    Json::Value root;
    Json::Value AllShiftParams;
    Json::Value controlParams_json;
    root["productName"] = "test";

    list<ListShiftParam>::iterator iter = shifts.begin();

    controlParam.CONFIG_INFO_MASTER_BELT_SPEED = 1000;
    controlParam.CONFIG_INFO_SLAVE_BELT_SPEED = 2000;
    controlParam.CONFIG_INFO_PILE_COUNTER = 12;
    controlParam.CONFIG_INFO_PILE_DELAY = 200;
    controlParam.CONFIG_INFO_PILE_SPEED = 111;
    controlParam.CONFIG_INFO_SORTER_COUNTER = 99;
    controlParam.CONFIG_INFO_SORTER_DELAY = 88;
    controlParam.CONFIG_INFO_SORTER_INIT_COUNTER = 77;
    controlParam.CONFIG_INFO_SORTER_INIT_DELAY = 66;

    controlParams_json["MASTER_BELT_SPEED"] = QString::number(controlParam.CONFIG_INFO_MASTER_BELT_SPEED).toStdString() ;
    controlParams_json["SLAVE_BELT_SPEED"] = QString::number(controlParam.CONFIG_INFO_SLAVE_BELT_SPEED).toStdString() ;
    controlParams_json["PILE_COUNTER"] =  QString::number(controlParam.CONFIG_INFO_PILE_COUNTER).toStdString() ;
    controlParams_json["PILE_DELAY"] =  QString::number(controlParam.CONFIG_INFO_PILE_DELAY).toStdString() ;
    controlParams_json["PILE_SPEED"] =  QString::number(controlParam.CONFIG_INFO_PILE_SPEED).toStdString() ;
    controlParams_json["SORTER_COUNTER"] =  QString::number(controlParam.CONFIG_INFO_SORTER_COUNTER).toStdString() ;
    controlParams_json["SORTER_DELAY"] =  QString::number(controlParam.CONFIG_INFO_SORTER_DELAY).toStdString() ;
    controlParams_json["SORTER_INIT_COUNTER"] =  QString::number(controlParam.CONFIG_INFO_SORTER_INIT_COUNTER).toStdString() ;
    controlParams_json["SORTER_INIT_DELAY"] = QString::number(controlParam.CONFIG_INFO_SORTER_INIT_DELAY).toStdString() ;

    for (; iter != shifts.end(); ++iter)
    {
        Json::Value ShiftParams;
        ShiftParams["description"] = iter->description;
        list<ShiftParam>::iterator servoParam_iter = iter->servoParam.begin();
        list<ShiftParam>::iterator stepParam_iter = iter->stepParam.begin();
        Json::Value servos;
        Json::Value steps;
        for (; servoParam_iter != iter->servoParam.end(); ++servoParam_iter)
        {
            Json::Value value;
            value["id"] = QString::number(servoParam_iter->id).toStdString();
            value["num"] = QString::number(servoParam_iter->num).toStdString();
            value["flag"] = QString::number(servoParam_iter->flag).toStdString();
            servos.append(value);
        }
        for (; stepParam_iter != iter->stepParam.end(); ++stepParam_iter)
        {
            Json::Value value;
            value["id"] = QString::number(stepParam_iter->id).toStdString();
            value["num"] = QString::number(stepParam_iter->num).toStdString();
            value["flag"] = QString::number(stepParam_iter->flag).toStdString();
            steps.append(value);
        }
        ShiftParams["servoParam"] = servos;
        ShiftParams["stepParam"] = steps;

        AllShiftParams.append(ShiftParams);
    }
    root["ShiftParams"]  = AllShiftParams;
    root["controlParam"] = controlParams_json;


    map<int,DeviceParam >::iterator it;
    map<int,CamParam>::iterator it_inner;
    it = deviceParams.begin();

    Json::Value devices;

    while(it != deviceParams.end())
    {
        Json::Value device;
        Json::Value camParams;
        Json::Value lightsParams;
        device["devicesNo"] = QString::number(it->first).toStdString();;
        it_inner = it -> second.camparams.begin();
        while(it_inner != it -> second.camparams.end())
        {
            Json::Value camParam;
            CamParam cam = it_inner->second;
            camParam["camNo"] = QString::number(cam.camNo).toStdString();
            camParam["segW"] = QString::number(cam.segW).toStdString();
            camParam["segH"] = QString::number(cam.segH).toStdString();
            camParam["netPath"] = cam.netPath;
            camParam["ratioW"] =  toString(cam.ratioW);
            camParam["ratioH"] = toString(cam.ratioH);
            camParam["limitH"] = QString::number(cam.limitH).toStdString();
            camParam["limitW"] = QString::number(cam.limitW).toStdString();
            camParam["threadH"] = QString::number(cam.threadH).toStdString();
            camParam["threadW"] = QString::number(cam.threadW).toStdString();
            camParam["area"] = QString::number(cam.resArea).toStdString();
            camParam["delayTime"] = QString::number(cam.delayTime).toStdString();
            camParam["camPosition"] = QString::number(cam.camPosition).toStdString();
            camParam["exposureTime"] = QString::number(cam.exposureTime).toStdString();
            it_inner++;
            camParams.append(camParam);

            {
                Json::Value lightsList;
                list<LightParam> ::iterator lit = it -> second.lightParams.listLightParam.begin();
                for(;lit!=it -> second.lightParams.listLightParam.end();++lit)
                {
                    Json::Value light;
                    light["lightPort"] = lit->lightPort ;
                    light["lightStep"] = QString::number(lit->lightStep).toStdString();;
                    lightsList.append(light);

                }
                lightsParams["lightparam"] = lightsList;
                lightsParams["lightSerial"] = "ttyS8";

            }
        }

        device["camparams"] = camParams;
        device["lightsParams"] = lightsParams;
        devices.append(device);
        it++;
    }
    root["devices"] = devices;

    string json_file = root.toStyledString();
    ofstream ofs;
    ofs.open(path);
    ofs<<json_file;
}

void ProductConfig::printInfo()
{
    qDebug()<<"productName"<<productName.c_str();
    list<ListShiftParam>::iterator iter = shiftParams.begin();
    for(;iter!=shiftParams.end();++iter)
    {
        qDebug()<<" "<<iter->description.c_str();
        list<ShiftParam> ::iterator iter_shift= iter->servoParam.begin();
        qDebug()<<"servo";
        for(;iter_shift!= iter->servoParam.end();++iter_shift)
        {
            qDebug()<<iter_shift->id<<iter_shift->num<<iter_shift->flag;
        }
        iter_shift = iter->stepParam.begin();
        qDebug()<<"step";
        for(;iter_shift!= iter->stepParam.end();++iter_shift)
        {
            qDebug()<<iter_shift->id<<iter_shift->num<<iter_shift->flag;
        }

    }
    {
        qDebug()<<"control "<<"CONFIG_INFO_MASTER_BELT_SPEED "<<controlParam.CONFIG_INFO_MASTER_BELT_SPEED;
        qDebug()<<"control "<<"CONFIG_INFO_SLAVE_BELT_SPEED "<<controlParam.CONFIG_INFO_SLAVE_BELT_SPEED;
        qDebug()<<"control "<<"CONFIG_INFO_PILE_COUNTER "<<controlParam.CONFIG_INFO_PILE_COUNTER;
        qDebug()<<"control "<<"CONFIG_INFO_PILE_DELAY "<<controlParam.CONFIG_INFO_PILE_DELAY;
        qDebug()<<"control "<<"CONFIG_INFO_PILE_SPEED "<<controlParam.CONFIG_INFO_PILE_SPEED;
        qDebug()<<"control "<<"CONFIG_INFO_SORTER_COUNTER "<<controlParam.CONFIG_INFO_SORTER_COUNTER;
        qDebug()<<"control "<<"CONFIG_INFO_SORTER_DELAY "<<controlParam.CONFIG_INFO_SORTER_DELAY;
        qDebug()<<"control "<<"CONFIG_INFO_SORTER_INIT_COUNTER "<<controlParam.CONFIG_INFO_SORTER_INIT_COUNTER;
        qDebug()<<"control "<<"CONFIG_INFO_SORTER_INIT_DELAY "<<controlParam.CONFIG_INFO_SORTER_INIT_DELAY;

    }

    {
        map<int,DeviceParam >::iterator it;
        map<int,CamParam>::iterator it_inner;
        list <LightParam> ::iterator light_it;
        it = deviceParams.begin();
        while(it != deviceParams.end())
        {
            printf("devicesNo %d\n",it->first);
            it_inner = it -> second.camparams.begin();
            while(it_inner != it -> second.camparams.end())
            {
               CamParam cam = it_inner->second;
                it_inner++;
                printf("-----%d %d %d %s %f %f %d %d %d\n",cam.camNo,cam.segW,cam.segH,
                       cam.netPath.c_str(),cam.ratioW,cam.ratioH,cam.resArea,cam.exposureTime,cam.delayTime);
            }


           ListLightParam lightParams = it -> second.lightParams;
           printf("-----%s\n",lightParams.lightSerial.c_str());
           light_it = lightParams.listLightParam.begin();

           for(;light_it!=lightParams.listLightParam.end();++light_it)
           {
               printf("---------%s %d\n",light_it->lightPort.c_str(),light_it->lightStep);
           }

           it++;
        }
    }

}

void ProductConfig::readFile(const char *path)
{
    ifstream ifs;
    ifs.open(path);
    Json::Reader reader;
    Json::Value root;
    if (!reader.parse(ifs, root, false))
    {
        return ;
    }
    this->productName = root["productName"].asString();
    Json::Value allShiftParams = root["ShiftParams"];
    Json::Value controlParam = root["controlParam"];
    for(unsigned int i=0;i<allShiftParams.size();i++)
    {
        ListShiftParam shifts;
        shifts.description     = allShiftParams[i]["description"].asString();
        Json::Value servoParam = allShiftParams[i]["servoParam"];
        Json::Value stepParam  = allShiftParams[i]["stepParam"];
        for(unsigned int k=0;k<servoParam.size();k++)
        {
            QString id = servoParam[k]["id"].asString().c_str();
            QString num = servoParam[k]["num"].asString().c_str();
            QString flag = servoParam[k]["flag"].asString().c_str();
            ShiftParam shift;
            shift.id = id.toInt();
            shift.num = num.toInt();
            shift.flag = flag.toInt();
            shifts.servoParam.push_back(shift);
        }
        for(unsigned int k=0;k<stepParam.size();k++)
        {
            QString id = stepParam[k]["id"].asString().c_str();
            QString num = stepParam[k]["num"].asString().c_str();
            QString flag = stepParam[k]["flag"].asString().c_str();
            ShiftParam shift;
            shift.id = id.toInt();
            shift.num = num.toInt();
            shift.flag = flag.toInt();
            shifts.stepParam.push_back(shift);
        }
        shiftParams.push_back(shifts);
    }

    {
       QString val = controlParam["MASTER_BELT_SPEED"].asString().c_str();
       this->controlParam.CONFIG_INFO_MASTER_BELT_SPEED =  val.toInt();

       val = controlParam["SLAVE_BELT_SPEED"].asString().c_str();
       this->controlParam.CONFIG_INFO_SLAVE_BELT_SPEED =  val.toInt();

       val = controlParam["PILE_COUNTER"].asString().c_str();
       this->controlParam.CONFIG_INFO_PILE_COUNTER =  val.toInt();

       val = controlParam["PILE_DELAY"].asString().c_str();
       this->controlParam.CONFIG_INFO_PILE_DELAY =  val.toInt();

       val = controlParam["PILE_SPEED"].asString().c_str();
       this->controlParam.CONFIG_INFO_PILE_SPEED =  val.toInt();

       val = controlParam["SORTER_COUNTER"].asString().c_str();
       this->controlParam.CONFIG_INFO_SORTER_COUNTER =  val.toInt();

       val = controlParam["SORTER_DELAY"].asString().c_str();
       this->controlParam.CONFIG_INFO_SORTER_DELAY =  val.toInt();

       val = controlParam["SORTER_INIT_COUNTER"].asString().c_str();
       this->controlParam.CONFIG_INFO_SORTER_INIT_COUNTER =  val.toInt();

       val = controlParam["SORTER_INIT_DELAY"].asString().c_str();
       this->controlParam.CONFIG_INFO_SORTER_INIT_DELAY =  val.toInt();

    }


    Json::Value json_devices = root["devices"];
    for(unsigned int i=0;i<json_devices.size();i++)
    {
        Json::Value json_cams = json_devices[i]["camparams"];
        Json::Value json_lightParam = json_devices[i]["lightsParams"];
        Json::Value json_lights = json_lightParam["lightparam"];
        int deviceNO = QString(json_devices[i]["devicesNo"].asString().c_str()).toInt();
        DeviceParam device;
        for(unsigned int j=0;j<json_cams.size();j++)
        {
            int delayTime = QString(json_cams[j]["delayTime"].asString().c_str()).toInt();
            int exposureTime = QString(json_cams[j]["exposureTime"].asString().c_str()).toInt();
            int camNo = QString(json_cams[j]["camNo"].asString().c_str()).toInt();
            int segW  = QString(json_cams[j]["segW"].asString().c_str()).toInt();
            int segH  = QString(json_cams[j]["segH"].asString().c_str()).toInt();
            string netPath = json_cams[j]["netPath"].asString();
            float ratioW = atof(json_cams[j]["ratioW"].asString().c_str());
            float ratioH = atof(json_cams[j]["ratioH"].asString().c_str());
            int limitH =  QString(json_cams[j]["limitH"].asString().c_str()).toInt();
            int limitW =  QString(json_cams[j]["limitW"].asString().c_str()).toInt();
            int threadH = QString(json_cams[j]["threadH"].asString().c_str()).toInt();
            int threadW = QString(json_cams[j]["threadW"].asString().c_str()).toInt();
            int area =    QString(json_cams[j]["area"].asString().c_str()).toInt();
            int camPosition = QString(json_cams[j]["camPosition"].asString().c_str()).toInt();
            CamParam camParam1(camNo,camPosition,segH,segW,netPath,ratioH,ratioW,limitH,limitW,
                               threadH,threadW,area,exposureTime,delayTime);
            device.camparams.insert(pair<int,CamParam>(camNo,camParam1));
        }
        device.lightParams.lightSerial = json_lightParam["lightSerial"].asString();

        for(unsigned int j=0;j<json_lights.size();j++)
        {
            LightParam light;
            light.lightPort = json_lights[j]["lightPort"].asString();
            light.lightStep = QString(json_lights[j]["lightStep"].asString().c_str()).toInt();
            device.lightParams.listLightParam.push_back(light);

        }
        qDebug()<<"serial"<<device.lightParams.lightSerial.c_str();
        deviceParams.insert(pair<int,DeviceParam >(deviceNO,device));
    }

}



