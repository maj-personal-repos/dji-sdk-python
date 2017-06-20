import djisdkpy
import time

drone = djisdkpy.Drone('UserConfig.txt')
drone.initialize()
time.sleep(1)
drone.takeControl()
drone.arm()
drone.takeoff()
time.sleep(5)
drone.land()
drone.disarm()
drone.releaseControl()
drone.shutdown()


