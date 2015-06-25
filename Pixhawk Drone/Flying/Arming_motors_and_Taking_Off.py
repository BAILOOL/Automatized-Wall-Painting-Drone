import sys
sys.path.append(r"C:\Python27\Lib")

takeoff_throttle = 1350

def setup_rc():
	print("Set up all RCs to neutral")
	for chan in range(1,9):
		Script.SendRC(chan, 1500, False)
	Script.SendRC(3, Script.GetParam('RC3_MIN'), True)
	Script.Sleep(5000)
	print("Done")
	return True

def arm_motors():
	#"Arming motors"
	print('APM: ARMING MOTORS')  
	print("Setting mode to Stabilize")
	Script.ChangeMode("STABILIZE")  # STABILIZE MODE
	Script.SendRC(5, 1750, True)
	print("Done")
	print('Setting Throttle to minimum')
	Script.SendRC(3,1000,True)
	print("Done")
	print('Set Yaw')
	Script.SendRC(4,2000,True)
	print("Done")
	print('Waiting for Arming Motors')
	cs.messages.Clear()
	Script.WaitFor('ARMING MOTORS',3000)       #3000(5sec)
	
	if cs.armed:
		print("APM: Morors are Armed")
	print('Reset Yaw')
	Script.SendRC(4,1500,True)
	
	print "keep motors working"
	Script.SendRC(3,takeoff_throttle,True) 
	Script.Sleep(5000)
	print("Exiting arm_motor Function")
	return True

# def land():
# 	print("STARTING LANDING")
# 	print("Changing Mode to LAND")
# 	Script.ChangeMode("LAND") # land mode
# 	Script.SendRC(5, 1300, True)
# 	print("Done")
# 	Script.WaitFor('LAND', 5000)
# 	print("Entered Landing Mode")
	#ret = wait_altitude(-5, 1)
	#print("LANDING: ok= %s" % ret)
	#print("Landing complete")
	#return ret

def land():
	current_throttle = 1225
	print current_throttle
	print("STARTING LANDING")
	print("Gradually decrease the throttle")
	while current_throttle >= 1050:
		Script.SendRC(3, current_throttle, True)
		Script.Sleep(500)
		print current_throttle
		current_throttle -= 20
		cs.messages.Clear()
	print("Landing complete")


def disarm_motors():
	#''disarm motors'''
	print("Disarming motors")
	print("Change mode to stabilize")
	Script.ChangeMode("STABILIZE") # stabilize mode
	print("Done")
	#Script.WaitFor('STABILIZE', 5000)
	#Script.Sleep(3000)
	Script.SendRC(3, 1000, True)
	Script.SendRC(4, 1000, True)
	Script.WaitFor('DISARMING MOTORS',5000)
	Script.SendRC(4, 1500, True)
	#mav.motors_disarmed_wait()
	print("MOTORS DISARMED OK")
	return True

#'''Main'''
setup_rc()
arm_motors()
land()
Script.Sleep(3000)
disarm_motors()
setup_rc()