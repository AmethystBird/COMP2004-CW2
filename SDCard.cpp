//Sebastan Nicholas Outram
#include "SDCard.h"
#include <cstdio>

SDCard::SDCard() : sd(PB_5, PB_4, PB_3, PF_3) {
    //Sets initial interrupt value to 0; won't run
    SetWritingUpdaterRun(0);
}

void SDCard::TestObject()
{
    printf("SDCard: Test()");
}

//Starts endless data writing function and utilises it when interrupt fires every 10s
void SDCard::StartWritingThread()
{
    writingThread.start(callback(this, &SDCard::WriteSDCardSensorValues));
    writingUpdater.attach(callback(this, &SDCard::WriteDataPeriodically), 60s);
}

//Interrupt service routine that allows data writing function to be utilised
void SDCard::WriteDataPeriodically()
{
    SetWritingUpdaterRun(1);
}


//Writes data to SD card when interrupt fires
void SDCard::WriteSDCardSensorValues()
{
    while (true)
    {
        if (GetWritingUpdaterRun() == 1)
        {
            printf("SDCard ISR started");

            printf("Initialise and write to a file\n");
        int err;
        // call the SDBlockDevice instance initialisation method.

        err=sd.init();
        if ( 0 != err) {
            printf("Init failed %d\n",err);
            //return -1;
        }
        
        FATFileSystem fs("sd", &sd);
        FILE *fp = fopen("/sd/test.txt","a");
        if(fp == NULL) {
            error("Could not open file for write\n");
            sd.deinit();
            //return -1;
        } else {
            //Put some text in the file...

            int lastIndex = leENVDataBuffer.GetSize();

            //Unloads all data from the buffer and writes to SD card
            string message = "";
            for (int i = 0; i <= lastIndex; i++)
            {
                EnvData dataToWrite;
                dataToWrite = leENVDataBuffer.Pop();
                string lightValueFormatted = to_string(dataToWrite.light);
                string tempValueFormatted = to_string(dataToWrite.temperature);
                string pressureValueFormatted = to_string(dataToWrite.pressure);
                message = message + lightValueFormatted + tempValueFormatted + pressureValueFormatted;
            }
            char messageFormatted[480];
            strcpy(messageFormatted, message.c_str());

            fprintf(fp, "Martin Says Hi!\n");
            //Tidy up here
            fclose(fp);
            printf("SD Write done...\n");
            sd.deinit();
            //return 0;
        }
        SetWritingUpdaterRun(0);
        printf("EnvironmentalSensors ISR ended");
        }
    }
}

//Getters & setters

int SDCard::GetWritingUpdaterRun()
{
    return writingUpdaterRun;
}

void SDCard::SetWritingUpdaterRun(int writingUpdaterRunUpdated)
{
    writingUpdaterRun = writingUpdaterRunUpdated;
}