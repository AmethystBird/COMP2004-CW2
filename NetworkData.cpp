//Sebastan Nicholas Outram
#include "NetworkData.h"
extern void SendDataToAzureServer(void);

//Sets initial interrupt value to 0; won't run
NetworkData::NetworkData()
{
    SetValueUpdaterRun(0);
}

//Starts endless data sending function and utilises it when interrupt fires every 10s
void NetworkData::StartNetworkThread()
{
    startSendData.start(SendDataToAzureServer); //fix this
    printf("NetworkData thread started");
    networkSender.attach(callback(this, &NetworkData::SendDataPeriodically), 10s);
    printf("NetworkData ISR activated");
}

//Interrupt service routine that allows data sending function to be utilised
void NetworkData::SendDataPeriodically()
{
    SetValueUpdaterRun(1);
}

int NetworkData::GetValueUpdaterRun()
{
    return networkSenderRun;
}

void NetworkData::SetValueUpdaterRun(int valueUpdaterRunUpdated)
{
    networkSenderRun = valueUpdaterRunUpdated;
}