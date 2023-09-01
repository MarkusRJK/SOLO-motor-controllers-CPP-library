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

//know more reading the CAN manual or Library Documentation 
//Getting the Speed Feedback after 4 SYNC Message

#include <iostream>
#ifdef ARDUINO
#include "MCP2515.hpp"
#else
#include "Kvaser.h"
#endif
#include <conio.h>

#include "SOLOMotorControllersImpl.h"


SOLOMotorControllersImpl *solo;
int error;

int main(void){
#ifdef ARDUINO
	CommunicationInterface* ci = new MCP2515(CommunicationInterface::CanbusBaudrate::rate1000);
#else
	CommunicationInterface* ci = new Kvaser(CommunicationInterface::CanbusBaudrate::rate1000);
#endif
	solo = new SOLOMotorControllersImpl(ci, 0, CommunicationInterface::CanbusBaudrate::rate1000);

	// 1 time needed CONFIGURATION:
    std::cout << "PdoParameterConfig:" << std::endl;
	PdoParameterConfig config;
	config.parameterName = PdoParameterName::speedFeedback;
	config.parameterCobId = 0x280;
	config.isPdoParameterEnable = true;
	config.isRrtParameterEnable = true;
	config.syncParameterCount = 4; 
	//send the configuration to SOLO
	solo->SetPdoParameterConfig(config, error);	
	Sleep(100);

	// if CONFIGURATION already done you can avoid and use the next commad:
	//solo->pdoParameterCobIdByPdoParameterName[PdoParameterName::speedFeedback] = 0x280;

	//ACTIVE section
    //send the sync messages
	solo->SendPdoSync(error);
	solo->SendPdoSync(error);
	solo->SendPdoSync(error);
	solo->SendPdoSync(error);
	Sleep(50);

    //read the older value in the PDO buffer
    long myRead = solo->GetPdoSpeedFeedback(error);
	std::cout << "READ VALUE: "<< myRead << " ERROR: "<< error <<"\n"; 

    //send the sync messages
	solo->SendPdoSync(error);
	solo->SendPdoSync(error);
	solo->SendPdoSync(error);
	solo->SendPdoSync(error);
	Sleep(50);

    //read the older value in the PDO buffer
    myRead = solo->GetPdoSpeedFeedback(error);
	std::cout << "READ VALUE: "<< myRead << " ERROR: "<< error <<"\n"; 

}
