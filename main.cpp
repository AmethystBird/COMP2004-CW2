//Sebastan Nicholas Outram

#include "mbed.h"
#include "uop_msb.h"
#include "rtos/ThisThread.h"
#include "NTPClient.h"
#include "azure_c_shared_utility/xlogging.h"
#include <cstring>
#include <string.h>

//My classes
#include "SDCard.h"
#include "EnvironmentalSensors.h"
#include "EnvDataBuffer.h"
#include "NetworkData.h"

using namespace uop_msb;

extern void azureDemo();
extern NetworkInterface *_defaultSystemNetwork;

//Objects derived from my classes
SDCard leSDCard;
EnvironmentalSensors leEnvironmentalSensors; //Updates sensor data
EnvDataBuffer leENVDataBuffer; //Buffer for general data
EnvDataBuffer leENVDataBufferNetwork; //Buffer for network data
NetworkData leNetworkData; //Sends data to Azure server

bool connect()
{
    LogInfo("Connecting to the network");

    _defaultSystemNetwork = NetworkInterface::get_default_instance();
    if (_defaultSystemNetwork == nullptr) {
        LogError("No network interface found");
        return false;
    }

    int ret = _defaultSystemNetwork->connect();
    if (ret != 0) {
        LogError("Connection error: %d", ret);
        return false;
    }
    LogInfo("Connection success, MAC: %s", _defaultSystemNetwork->get_mac_address());
    return true;
}

bool setTime()
{
    LogInfo("Getting time from the NTP server");

    NTPClient ntp(_defaultSystemNetwork);
    ntp.set_server("time.google.com", 123);
    time_t timestamp = ntp.get_timestamp();
    if (timestamp < 0) {
        LogError("Failed to get the current time, error: %ud", timestamp);
        return false;
    }
    LogInfo("Time: %s", ctime(&timestamp));
    set_time(timestamp);
    return true;
}

int main() {

    // START - UNCOMMENT THE FOLLOWING TWO LINES TO TEST YOUR BOARD AND SEE THE DEMO CODE WORKING
    //UOP_MSB_TEST  board;  //This class is purely for testing. Do no use it otherwise!!!!!!!!!!!
    //board.test();         //Look inside here to see how this works
    // END

    if (!connect()) return -1;

    if (!setTime()) return -1;

    // The two lines below will demonstrate the features on the MSB. See uop_msb.cpp for examples of how to use different aspects of the MSB
    //UOP_MSB_TEST board;  //Only uncomment for testing - DO NOT USE OTHERWISE
    //board.test();        //Only uncomment for testing - DO NOT USE OTHERWISE

    LogInfo("Starting tasks");
    leEnvironmentalSensors.StartSensorThread();
    leSDCard.StartWritingThread();
    leNetworkData.StartNetworkThread();

    LogInfo("Tasks ended");

    return 0;
}
