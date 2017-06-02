#include "Drone.h"


using namespace Matrice;

Drone::Drone() {
    
    serialDevice = new LinuxSerialDevice(UserConfig::deviceName, UserConfig::baudRate);
    api = new CoreAPI(serialDevice);
    flight = new Flight(api);
    waypoint = new WayPoint(api);
    camera = new Camera(api);

}
