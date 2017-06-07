#include <LinuxSerialDevice.h>
#include <LinuxCamera.h>
#include <DJI_Follow.h>
#include <DJI_Flight.h>
#include <DJI_Version.h>
#include <DJI_WayPoint.h>
#include <string>

using namespace DJI::onboardSDK;

using namespace DJI;

namespace Matrice {

    class Drone {

        public:

            Drone(std::string);

            int initialize();

            int cleanup();

            ackReturnData takeControl();

            ackReturnData releaseControl();

            ackReturnData engage();

            ackReturnData disengage();

            ackReturnData takeoff();

            ackReturnData land();

            ackReturnData returnHome();

        private:

            LinuxSerialDevice* serialDevice;

            CoreAPI* api;

            Flight* flight;

            WayPoint* waypoint;

            Camera* camera;

            std::string filename;

    };

}
