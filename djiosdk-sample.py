import time
import osdkpy

user_prompt = "\n" + \
  "|------------------DJI Onboard SDK Interactive Sample------------|\n" + \
  "|                                                                |\n" + \
  "| The interactive mode allows you to execute a few commands      |\n" + \
  "| to help you get a feel of the DJI Onboard SDK. Try them out!   |\n" + \
  "|                                                                |\n" + \
  "| Standard DJI Onboard SDK Usage Flow:                           |\n" + \
  "| 1. Activate (The sample has already done this for you)         |\n" + \
  "| 2. Obtain Control (The sample has already done this for you)   |\n" + \
  "| 3. Takeoff                                                     |\n" + \
  "| 4. Execute Aircraft control (Movement control/Missions/Camera) |\n" + \
  "| 5. Return to Home/Land                                         |\n" + \
  "| 6. Release Control (The sample will do this for you on exit)   |\n" + \
  "|                                                                |\n" + \
  "| Available commands:                                            |\n" + \
  "| [a] Request Control                                            |\n" + \
  "| [b] Release Control                                            |\n" + \
  "| [c] Arm the Drone                                              |\n" + \
  "| [d] Disarm the Drone                                           |\n" + \
  "| [e] Takeoff                                                    |\n" + \
  "| [f] Waypoint Sample                                            |\n" + \
  "| [g] Position Control Sample: Draw Square                       |\n" + \
  "| [h] Landing                                                    |\n" + \
  "| [i] Go Home                                                    |\n" + \
  "| [j] Set Gimbal Angle                                           |\n" + \
  "| [k] Set Gimbal Speed                                           |\n" + \
  "| [l] Take Picture                                               |\n" + \
  "| [m] Take Video                                                 |\n" + \
  "| [n] Exit this sample                                           |\n" + \
  "|                                                                |\n" + \
  "| Type one of these letters and then press the enter key.        |\n" + \
  "|                                                                |\n" + \
  "| If you're new here, try following the usage flow shown above.  |\n" + \
  "|                                                                |\n" + \
  "| Visit developer.dji.com/onboard-sdk/documentation for more.    |\n" + \
  "|                                                                |\n" + \
  "|------------------DJI Onboard SDK Interactive Sample------------|\n"

drone = osdkpy.Drone("UserCongif.txt")
drone.initialize()

def check_input(user_input):
    output = True
    if user_input == 'a':
        drone.takeControl()
    elif user_input == 'b':
        drone.releaseControl()
    elif user_input == 'c':
        drone.arm()
    elif user_input == 'd':
        drone.disarm()
    elif user_input == 'e':
        drone.takeoff()
    elif user_input == 'h':
        drone.land()
    elif user_input == 'i':
        drone.returnHome()
    elif user_input == 'n':
        output = False
    else:
        print "Please select a valid option."

    time.sleep(0.5)
    return output

if __name__ == '__main__':

    try:
        user_input = raw_input(user_prompt)
        while check_input(user_input):
            user_input = raw_input(user_prompt)
    except KeyboardInterrupt:
        pass

