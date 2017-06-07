#include "Drone.h"
#include "LinuxFlight.h"

Matrice::Drone::Drone(std::string filename) : filename(filename) {

    std::cout << "Setting up Drone." << std::endl;

   serialDevice = new LinuxSerialDevice(UserConfig::deviceName, UserConfig::baudRate);

   api = new CoreAPI(serialDevice);

   flight = new Flight(api);

   waypoint = new WayPoint(api);

   camera = new Camera(api);

   std::cout << "Drone setup." <<std::endl;

}

int Matrice::Drone::initialize() {

    std::cout << "Initializing drone." << std::endl;

    std::cout << "Parsing drone configuration." << std::endl;

    int readOK = parseUserConfig(filename);
    
    if(readOK == -1)

        return 0;
    
    unsigned short broadcastAck = api->setBroadcastFreqDefaults(1);

    usleep(500000);

    std::cout << "Drone initialized." << std::endl;
}

int Matrice::Drone::cleanup() {

  int broadcastStatus = api->setBroadcastFreqDefaults(1);

  if (broadcastStatus != 0) {

      std::cout << "Unable to set broadcast frequencies to defaults.\nPlease go to DJI Assistant 2 and change frequencies." << std::endl;

  }

  ackReturnData controlStatus = releaseControl();

  if (controlStatus.status == -1) {
      
      std::cout << "Unable to release control. \nYou should manually switch control by toggling the RC mode to P and back to F." << std::endl; 

  }

  delete serialDevice;

  delete api;

  delete flight;

  delete waypoint;

  delete camera;

  return 0;

}


ackReturnData Matrice::Drone::takeControl() {
    
    unsigned short controlAck;
  
    //! Obtain code 0x1
  
    unsigned char data = 0x1;
  
    ackReturnData takeControlData;
  
    takeControlData.ack = api->setControl(true, 1);
  
    switch (takeControlData.ack) {
    
        case  ACK_SETCONTROL_NEED_MODE_F:
      
            std::cout << std::endl << "Failed to obtain control.\nYour RC mode switch is not in mode F. (Is the RC connected and paired?)" << std::endl;
      
            takeControlData.status = -1;
      
            return takeControlData;
    
        case  ACK_SETCONTROL_NEED_MODE_P:
      
            std::cout << std::endl << "Failed to obtain control.\nFor newer firmware, your RC needs to be in P mode. (Is the RC connected and paired?)" << std::endl;
      
            takeControlData.status = -1;
      
            return takeControlData;
    
        case ACK_SETCONTROL_OBTAIN_SUCCESS:
      
            std::cout << std::endl << "Obtained control successfully."<< std::endl;
      
            break;

        case ACK_SETCONTROL_OBTAIN_RUNNING:

            std::cout << std::endl << "Obtain control running.."<< std::endl;

            takeControl();

            break;

        case ACK_SETCONTROL_IOC:

            std::cout << std::endl << "The aircraft is in IOC mode. Cannot obtain control.\nGo to DJI GO and stop all intelligent flight modes before trying this." << std::endl;

            takeControlData.status = -1;

            return takeControlData;

            break;

        default: 
            std::cout << std::endl << "Error in setControl API function." << std::endl;

            break;

    }
  
    takeControlData.status = 1;
  
    return takeControlData;
}


ackReturnData Matrice::Drone::releaseControl() {
    
    ackReturnData controlAck;
  
  
    //! Release code 0x0
  
    unsigned char data = 0x0;

  
    controlAck.ack = api->setControl(false, 1);

  
    switch (controlAck.ack) {
    
        case ACK_SETCONTROL_NEED_MODE_F:
        
            std::cout << std::endl << "Failed to release control.\nYour RC mode switch is not in mode F. (Is the RC still connected and paired?)" << std::endl;
            
            controlAck.status = -1;
          
            return controlAck;
          
            break;
    
        case ACK_SETCONTROL_NEED_MODE_P:
      
            std::cout << std::endl << "Failed to release control.\nFor newer firmware, your RC needs to be in P mode. (Is the RC connected and paired?)" << std::endl;
      
            controlAck.status = -1;
      
            return controlAck;
      
            break;
    
        case ACK_SETCONTROL_RELEASE_SUCCESS:
      
            std::cout << std::endl << "Released control successfully."<< std::endl;
      
            break;
    
        case ACK_SETCONTROL_RELEASE_RUNNING:
      
            std::cout << std::endl << "Release control running.."<< std::endl;
      
            releaseControl();
      
            break;
        
        case ACK_SETCONTROL_IOC:
      
            std::cout << std::endl << "The aircraft is in IOC mode. Cannot release control.\nGo to DJI GO and stop all intelligent flight modes before trying this." << std::endl;
      
            controlAck.status = -1;
      
            return controlAck;
      
            break;

        default:
      
            std::cout << std::endl << "Error in setControl API function." << std::endl;
      
            break;
    }
  
    controlAck.status = 1;
  
    return controlAck;
}

ackReturnData Matrice::Drone::engage() {

    return arm(flight);
}

ackReturnData Matrice::Drone::disengage() {

    return disArm(flight);
}

ackReturnData Matrice::Drone::takeoff() {

    return monitoredTakeoff(api, flight);
}

ackReturnData Matrice::Drone::land() {
    
    return landing(api, flight);
}

ackReturnData Matrice::Drone::returnHome() {

    return goHome(flight);

}
