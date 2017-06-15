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

            int setAttitude(float32_t roll, float32_t pitch, float32_t yaw);

            int setAttitudeAndAltitude(float32_t roll, float32_t pitch, float32_t yaw, float32_t z);

            int setOffset(float32_t xOffset, float32_t yOffset, float32_t zOffset, float32_t yaw);

            int setVelocity(float32_t xVelocity, float32_t yVelocity, float32_t zVelocity, float32_t yawRate);

        private:

            LinuxSerialDevice* serialDevice;

            CoreAPI* api;

            Flight* flight;

            WayPoint* waypoint;

            Camera* camera;

            std::string filename;

    };

}
