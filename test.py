import osdkpy

drone = osdkpy.Drone('UserConfig.txt')
drone.initialize()
print "Drone inialized from python."
drone.cleanup()
print "Drone cleanuped from python."

