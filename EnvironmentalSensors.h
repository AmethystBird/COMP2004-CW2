//Sebastan Nicholas Outram
#include "mbed.h"
#include "uop_msb.h"
#include "EnvDataBuffer.h"

extern EnvDataBuffer leENVDataBuffer;
extern EnvDataBuffer leENVDataBufferNetwork;

class EnvironmentalSensors {
public:
    EnvironmentalSensors();

    double GetLightValue();
    double GetTempValue();
    double GetPressureValue();
    void SetLightValue(double lightValueUpdated);
    void SetTempValue(double tempValueUpdated);
    void SetPressureValue(double pressureValueUpdated);
    
    int GetValueUpdaterRun();
    void SetValueUpdaterRun(int valueUpdaterRunUpdated);

    //Called outside object to start sensor measuring and data collection
    void StartSensorThread();

private:
    AnalogIn lightReal;
    uop_msb::EnvSensor sensors;
    
    //Acquires current sensor values
    double lightValue, tempValue, pressureValue;

    //Threads
    Thread startUpdateAndReadData;

    //Interrupts
    Ticker valueUpdater;
    int valueUpdaterRun;

    //Called by sensor thread to execute perpetual interrupt
    void MeasureDataPeriodically();

    //Called by interrupt to measure data periodically
    void MeasureSensorData();
};