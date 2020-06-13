#define DATA_LENGTH 256

#include <iostream>
#include "SerialPort.h"
#include <windows.h>

using namespace std;

int main(void)
{
    char com[32] = "hello world";
    cout << "COM number: ";
    cin >> com;
    cout << "Number: " << com << endl;
    for(int i=0; i<32; i++){
        cout << (int) com[i] << " " << com[i] << endl;
    }
    return 0;

    char receivedString[DATA_LENGTH];
    SerialPort* arduino = new SerialPort("\\\\.\\COM3");
    int hasRead = 1;

    while(arduino->isConnected() && hasRead){
        Sleep(5);
        hasRead = arduino->readSerialPort(receivedString, DATA_LENGTH);
        //while(arduino->isConnected() && !arduino->readableSize());
        if (hasRead) //cout << (int) receivedString[255]; // << endl;
            for(int i=0; i<DATA_LENGTH; i++)
                cout << (int) receivedString[i] << ' ';
        else cerr << endl << endl << "Error occured reading data" << endl;
    }
}
