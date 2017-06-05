#include "LinuxSerialDevice.h"
#include "LinuxCamera.h"
#include <DJI_Follow.h>
#include <DJI_Flight.h>
#include <DJI_Version.h>
#include <DJI_WayPoint.h>


using namespace DJI;
using namespace DJI::onboardSDK;

namespace Matrice {

    class Drone {

        public:

            Drone();

            int init();

            ackReturnData takeControl();

            ackReturnData releaseControl();

            ackReturnData arm();

            ackReturnData disarm();

            ackReturnData takeoff();

            ackReturnData land();

            ackReturnData goHome();

            LinuxSerialDevice* serialDevice;

            CoreAPI* api;

            Flight* flight;

            WayPoint* waypoint;

            Camera* camera;

    };
}


