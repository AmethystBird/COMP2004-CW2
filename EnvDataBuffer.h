//Sebastan Nicholas Outram
#ifndef __ENV_DATA_BUFFER__
#define __ENV_DATA_BUFFER__

#include "mbed.h"
#include "uop_msb.h"

typedef struct {
    double light;
    double temperature;
    double pressure;
} EnvData;

class EnvDataBuffer {
public:
    EnvDataBuffer();

    void Push(double light, double temp, double pressure);
    EnvData Pop();

    void OldPush(double light, double temp, double pressure);
    EnvData OldPop();

    int GetSize();

private:
    double buffer[12][3];
    int bufferNextIndex;
    int bufferSize;
    DigitalOut redLED;
    Semaphore bufferTopCap;
    Semaphore bufferBottomCap;
    Mutex bufferLock;
};

#endif