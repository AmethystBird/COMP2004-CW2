//Sebastan Nicholas Outram
#include "mbed.h"
#include "uop_msb.h"
#include "EnvDataBuffer.h"
#ifndef __NETWORK_DATA__
#define __NETWORK_DATA__

class NetworkData {
public:
    NetworkData();

int GetValueUpdaterRun();
    void SetValueUpdaterRun(int valueUpdaterRunUpdated);

    //Called outside object to start sensor measuring and data collection
    void StartNetworkThread();

private:
    //Threads
    Thread startSendData;

    //Interrupts
    Ticker networkSender;
    int networkSenderRun;

    //Called by sensor thread to execute perpetual interrupt
    void SendDataPeriodically();

    //Called by interrupt to measure data periodically
    void MeasureSensorData();
};

#endif