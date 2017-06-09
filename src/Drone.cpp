#include "Drone.h"
#include "LinuxFlight.h"
#include "LinuxSetup.h"
#include "LinuxCleanup.h"

Matrice::Drone::Drone(std::string filename) : filename(filename) {

   std::cout << "Setting up Drone." << std::endl;

   serialDevice = new LinuxSerialDevice(UserConfig::deviceName, UserConfig::baudRate);

   api = new CoreAPI(serialDevice);

   flight = new Flight(api);

   waypoint = new WayPoint(api);

   camera = new Camera(api);

   read = new LinuxThread(api, 2);

   std::cout << "Drone setup." <<std::endl;

}


int Matrice::Drone::initialize() {

    std::cout << "Initializing drone." << std::endl;

    int setupStatus = setup(serialDevice, api, read);

    if (setupStatus == -1) {
        
        std::cout << std::endl << "This program will exit now." << std::endl;

        return 0;
    }

    unsigned short broadcastAck = api->setBroadcastFreqDefaults(1);

    usleep(500000);

    if(broadcastAck == -1) {
        
        std::cout << std::endl << "Something happened when setting up broadcast defaults." << std::endl;

    }

    usleep(500000);

    std::cout << std::endl << "Drone initialized." << std::endl;

    return 0;

}

int Matrice::Drone::shutdown(){

    delete waypoint;

    delete camera;

    return cleanup(serialDevice, api, flight, read);

}


ackReturnData Matrice::Drone::getControl() {

    return takeControl(api);
}


ackReturnData Matrice::Drone::relControl() {

    return releaseControl(api);
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
