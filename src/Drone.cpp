#include "Drone.h"

using namespace Matrice;


Drone::Drone() {
    
    serialDevice = new LinuxSerialDevice(UserConfig::deviceName, UserConfig::baudRate);
    
    api = new CoreAPI(serialDevice);
    
    flight = new Flight(api);
    
    waypoint = new WayPoint(api);
    
    camera = new Camera(api);

}


int Drone::init() {

    return 0;
}

ackReturnData Drone::takeControl() {

    ackReturnData returnData;

    return returnData;
}


ackReturnData Drone::releaseControl() {

    ackReturnData returnData;

    return returnData;

}

ackReturnData Drone::arm() {

    ackReturnData returnData;

    return returnData;
}

ackReturnData Drone::disarm() {

    ackReturnData returnData;

    return returnData;
}

ackReturnData Drone::takeoff() {

    ackReturnData returnData;

    return returnData;
}

ackReturnData Drone::land() {
    
    ackReturnData returnData;

    return returnData;
}

ackReturnData Drone::goHome() {

    ackReturnData returnData;

    return returnData;

}
