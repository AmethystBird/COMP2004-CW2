//Sebastan Nicholas Outram
#include "EnvDataBuffer.h"

EnvDataBuffer::EnvDataBuffer() : bufferTopCap(11), bufferBottomCap(0), redLED(TRAF_RED1_PIN) {
    bufferNextIndex = 0;
    bufferSize = 11;
}

//Pushes environmental data to FIFO buffer
void EnvDataBuffer::Push(double light, double temp, double pressure) {
    //Decrements buffer max size semaphore; will lock if buffer is already full
    bufferTopCap.acquire();
    bufferLock.lock();
    //bufferNextIndex++;

    //Shifts buffer across
    if (bufferNextIndex <= bufferSize)
    {
        //Shifts buffer elements across by one
        for (int i = bufferSize; i > 0; i--)
        {
            buffer[i][0] = buffer[i - 1][0];
            buffer[i][1] = buffer[i - 1][1];
            buffer[i][2] = buffer[i - 1][2];
        }

        //Assigns new value
        buffer[0][0] = light, buffer[0][1] = temp, buffer[0][2] = pressure;
        bufferNextIndex++;
    }
    else {
        //Critical error; full buffer
        redLED = 1;
    }
    //Increases buffer min size due to prior addition of data
    bufferLock.unlock();
    bufferBottomCap.release();
}

EnvData EnvDataBuffer::Pop() {
    //Decrements buffer min size semaphore; will lock if buffer is already empty
    bufferBottomCap.acquire();
    bufferLock.lock();

    EnvData extractedValues;
    int lastIndex = bufferNextIndex;
    lastIndex--;
    extractedValues.light = buffer[lastIndex][0];
    extractedValues.temperature = buffer[lastIndex][1];
    extractedValues.pressure = buffer[lastIndex][2];
    bufferNextIndex--;

    //Shifts buffer elements across by one
    for (int i = 0; i < bufferSize - 1; i++)
    {
        buffer[i][0] = buffer[i + 1][0];
        buffer[i][1] = buffer[i + 1][1];
        buffer[i][2] = buffer[i + 1][2];
    }

    //Increases buffer max size due to prior extraction of data
    bufferLock.unlock();
    bufferTopCap.release();

    //Returns popped values
    return extractedValues;
}

//Pushes environmental data to FIFO buffer
void EnvDataBuffer::OldPush(double light, double temp, double pressure) {
    //Decrements buffer max size semaphore; will lock if buffer is already full
    bufferTopCap.acquire();
    bufferLock.lock();
    //bufferNextIndex++;

    //Shifts buffer across
    if (bufferNextIndex <= bufferSize)
    {
        //Shifts buffer elements across by one
        for (int i = bufferSize; i > 0; i--)
        {
            buffer[i][0] = buffer[i - 1][0];
            buffer[i][1] = buffer[i - 1][1];
            buffer[i][2] = buffer[i - 1][2];
        }

        //Assigns new value
        buffer[0][0] = light, buffer[0][1] = temp, buffer[0][2] = pressure;
    }
    else {
        //Critical error; full buffer
        redLED = 1;
    }
    //Increases buffer min size due to prior addition of data
    bufferLock.unlock();
    bufferBottomCap.release();
}

EnvData EnvDataBuffer::OldPop() {
    //Decrements buffer min size semaphore; will lock if buffer is already empty
    bufferBottomCap.acquire();
    bufferLock.lock();

    EnvData extractedValues;
    extractedValues.light = buffer[0][0];
    extractedValues.temperature = buffer[0][1];
    extractedValues.pressure = buffer[0][2];

    //Shifts buffer elements across by one
    for (int i = 0; i < bufferSize - 1; i++)
    {
        buffer[i][0] = buffer[i + 1][0];
        buffer[i][1] = buffer[i + 1][1];
        buffer[i][2] = buffer[i + 1][2];
    }

    //Increases buffer max size due to prior extraction of data
    bufferLock.unlock();
    bufferTopCap.release();

    //Returns popped values
    return extractedValues;
}

int EnvDataBuffer::GetSize() {
    return bufferNextIndex;
}