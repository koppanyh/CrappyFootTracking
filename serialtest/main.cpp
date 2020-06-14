#include <iostream>
#include "SerialPort.h"
//#include <windows.h>
using namespace std;

#define DATA_LENGTH 256

int main(void)
{
    char com[32] = "\\\\.\\COM3";
    /*cout << "COM number: "; //uncomment this if you want to be able to type in the com number
    cin >> com + 7;*/

    char receivedString[DATA_LENGTH];
    SerialPort* arduino = new SerialPort(com);

    int c = 0;

    while(arduino->isConnected()){
        if(c >= 40){ //after 40 prints use a new line
            cout << endl;
            c = 0;
        }
        //Sleep(5);
        int hasRead = arduino->readSerialPort(receivedString, DATA_LENGTH);
        if(!hasRead) //don't print anything if there's nothing to print
            continue;
        cout << (int) receivedString[hasRead-1] << ' '; //print the newest read and discard other data
        c++;
    }
}
