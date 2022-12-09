//Sebastan Nicholas Outram
#include "EnvironmentalSensors.h"

EnvironmentalSensors::EnvironmentalSensors() : lightReal(PC_0)
{
    //Sets initial interrupt value to 0; won't run
    SetValueUpdaterRun(0);
}

//Updates sensor data when interrupt fires
void EnvironmentalSensors::MeasureSensorData()
{
    while (true)
    {
        if (GetValueUpdaterRun() == 1)
        {
            printf("EnvironmentalSensors ISR started");

            SetLightValue((float) lightReal);
            SetTempValue((float) sensors.getTemperature());
            SetPressureValue((float) sensors.getPressure());

            leENVDataBuffer.Push(GetLightValue(), GetTempValue(), GetPressureValue());
            leENVDataBufferNetwork.Push(GetLightValue(), GetTempValue(), GetPressureValue());

            SetValueUpdaterRun(0);
            printf("EnvironmentalSensors ISR ended");
        }
    }
}

//Starts endless data updating function and utilises it when interrupt fires every 10s
void EnvironmentalSensors::StartSensorThread()
{
    startUpdateAndReadData.start(callback(this, &EnvironmentalSensors::MeasureSensorData));
    printf("EnvironmentalSensors thread started");
    valueUpdater.attach(callback(this, &EnvironmentalSensors::MeasureDataPeriodically), 10s);
    printf("EnvironmentalSensors ISR activated");
}

//Interrupt service routine that allows data updating function to be utilised
void EnvironmentalSensors::MeasureDataPeriodically()
{
    SetValueUpdaterRun(1);
}

double EnvironmentalSensors::GetLightValue()
{
    return lightValue;
}

double EnvironmentalSensors::GetTempValue()
{
    return tempValue;
}

double EnvironmentalSensors::GetPressureValue()
{
    return pressureValue;
}

void EnvironmentalSensors::SetLightValue(double lightValueUpdated)
{
    lightValue = lightValueUpdated;
}

void EnvironmentalSensors::SetTempValue(double tempValueUpdated)
{
    tempValue = tempValueUpdated;
}

void EnvironmentalSensors::SetPressureValue(double pressureValueUpdated)
{
    pressureValue = pressureValueUpdated;
}

int EnvironmentalSensors::GetValueUpdaterRun()
{
    return valueUpdaterRun;
}

void EnvironmentalSensors::SetValueUpdaterRun(int valueUpdaterRunUpdated)
{
    valueUpdaterRun = valueUpdaterRunUpdated;
}