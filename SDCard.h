//Sebastan Nicholas Outram
//#ifdef USE_SD_CARD
#include "mbed.h"
#include "SDBlockDevice.h"
#include "FATFileSystem.h"
#include "EnvDataBuffer.h"
#include <string.h>
#include <cstring>
#include <iostream>

extern EnvDataBuffer leENVDataBuffer;
extern EnvDataBuffer leENVDataBufferNetwork;

class SDCard {
public:
    void TestObject();

    SDCard();

    void StartWritingThread();

    //Getters & setters
    int GetWritingUpdaterRun();
    void SetWritingUpdaterRun(int writingUpdaterRunUpdated);

private:
    SDBlockDevice sd;

    //Threads
    Thread writingThread;

    //Interrupts
    Ticker writingUpdater;
    int writingUpdaterRun;

    //Called by writing thread to execute perpetual interrupt
    void WriteDataPeriodically();

    //int WriteSDCardSensorValues(char lightValue, char tempValue, char pressureValue);
    void WriteSDCardSensorValues();
};