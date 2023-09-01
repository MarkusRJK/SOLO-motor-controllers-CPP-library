// Copyright: (c) 2021-2022, SOLO motor controllers project
// GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)

/*
*    Title: SOLO Motor Controllers CPP Library
*    Author: SOLOMotorControllers
*    Date: 2023
*    Code version: 1.2.0
*    Availability: https://github.com/Solo-FL/SOLO-motor-controllers-CPP-library
This Library is made by SOLOMotorControllers.com
To learn more please visit:  https://www.SOLOMotorControllers.com/
*/

#include <iostream>

#include <conio.h>
#include "Kvaser.h"
#include "SOLOMotorControllersKvaser.h"

int main(void)
{
    float readingValue;
    int error;

	CommunicationInterface* ci = new Kvaser(SOLOMotorControllers::CanbusBaudrate::rate1000);

    //Initialize the SOLO object
    //Equivalent, avoiding the default parameter of SOLO Device Address:  solo = new SOLOMotorControllersKvaser(0);
    SOLOMotorControllers *solo = new SOLOMotorControllersKvaser(ci);

    //TRY CONNECT LOOP
    while(solo->CommunicationIsWorking() == false ){
        std::cout << "Solo connection failed. Retry" << std::endl;
        Sleep(500);
        solo->Connect();
    }
    std::cout << "Solo connected!" << std::endl;

    //PRINT LOOP
    while (true)
    {
        readingValue = solo->GetBusVoltage(error);
        if(error == SOLOMotorControllers::Error::noErrorDetected)
        {
            std::cout << "Succesfully read from solo, Value: " << readingValue << std::endl;
        }
        else
        {
            std::cout << "Failed to set solo, Error: " <<  error << std::endl;
        }
    }
    solo->Disconnect();

    std::cout << "Press Enter to Exit";
    getch();
    return 0;
}
