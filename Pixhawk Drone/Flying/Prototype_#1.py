import sys, time
sys.path.append(r"C:\Python27\Lib")

#RC1
ROLL = 1
#RC2
PITCH = 2
#RC3
THROTTLE = 3
#RC4
YAW = 4
#RC5
MODE = 5

takeoff_throttle = 1600

def setup_rc():
	print("Set up all RCs to neutral")
	for chan in range(1,9):
		Script.SendRC(chan, 1500, False)
	Script.SendRC(THROTTLE, Script.GetParam('RC3_MIN'), True)
	Script.Sleep(5000)
	print("Done")
	return True

def arm_motors():
	#"Arming motors"
	print('APM: ARMING MOTORS')  
	print("Setting mode to Stabilize")
	Script.ChangeMode("STABILIZE")  # STABILIZE MODE
	#Script.SendRC(MODE, 1750, True)
	print("Done")
	print('Setting Throttle to minimum')
	Script.SendRC(THROTTLE,1000,True)
	print("Done")
	print('Set Yaw')
	Script.SendRC(YAW,2000,True)
	print("Done")
	print('Waiting for Arming Motors')
	
	cs.messages.Clear()
	Script.WaitFor('ARMING MOTORS',2000)       #2000(5sec)
	
	if cs.armed:
		print("APM: Morors are Armed")
		print('Reset Yaw')
		Script.SendRC(YAW,1500,True)
		print("Exiting arm_motor Function")
		return True



def takeoff():
	needed_altitude = 0.7
	current_throttle = cs.ch3in
	count = 0
	print("Entered takeoff")
	print("About to takeoff")
	print("Make sure we are in stabilise mode")
	Script.ChangeMode("STABILIZE")
	Script.SendRC(MODE, 1750, True)
	print("Done")
	print("Gradually increase the throttle")
	cs.messages.Clear()
	while current_throttle <= takeoff_throttle:
		Script.SendRC(THROTTLE, current_throttle, True)
		Script.Sleep(500)
		print current_throttle
		current_throttle += 50
		cs.messages.Clear()
	print("Takeoff completed")

	#reach and hold altitude
	while True:
		if cs.alt <= needed_altitude - 0.3:
			print ("Going up")
			print current_throttle
			print cs.alt
			Script.SendRC(THROTTLE, current_throttle, True)
			if current_throttle + 20 <= 1600:
				current_throttle += 20
			cs.messages.Clear()
		elif cs.alt >= needed_altitude + 0.3:
			print ("Going down")
			print current_throttle
			print cs.alt
			Script.SendRC(THROTTLE, current_throttle, True)
			if current_throttle - 20 >= 1400:
				current_throttle -= 20
			cs.messages.Clear()
		
		#needed altitude is reached
		elif count >= 100 and ((cs.alt >= needed_altitude - 0.2) and (cs.alt <= needed_altitude + 0.2)):
			print ("Entering AltHold")
			print cs.alt
			Script.ChangeMode("AltHold")
			Script.SendRC(THROTTLE,1400,True)
			Script.Sleep(3000)
			cs.messages.Clear()
			break	

		elif (cs.alt >= needed_altitude - 0.2) and (cs.alt <= needed_altitude + 0.2): 
			while (count <= 100) and ((cs.alt >= needed_altitude - 0.2) and (cs.alt <= needed_altitude + 0.2)):
				count += 1
				Script.Sleep(50)
				print "Accumulating count for the AltHold"
				print count

		else: 
			print "Some kind of error occured"

def hover():
	hover_throttle = 1500
	print("Entering Hover mode")
	print("Setting hover throttle")
	Script.SendRC(THROTTLE, hover_throttle, True)
	#cs.messages.Clear()
	print("Done")
	print("Hovering for 3 seconds")
	Script.Sleep(3000)
	print("Hover Complete")	


def land():
	current_throttle = cs.ch3in
	print current_throttle
	print("STARTING LANDING")
	print("Gradually decrease the throttle")
	while current_throttle >= 1000:
		Script.SendRC(THROTTLE, current_throttle, True)
		Script.Sleep(500)
		print current_throttle
		current_throttle -= 50
		cs.messages.Clear()
	print("Landing complete")

def disarm_motors():
	#''disarm motors'''
	print("Disarming motors")
	print("Change mode to stabilize")
	Script.ChangeMode("STABILIZE") # stabilize mode
	print("Done")
	#Script.WaitFor('STABILIZE', 5000)
	Script.SendRC(THROTTLE, 1000, True)
	Script.SendRC(YAW, 1000, True)
	cs.messages.Clear()
	Script.WaitFor('DISARMING MOTORS',3000)
	Script.SendRC(THROTTLE, 1500, True)
	if cs.armed == 0:
		print("MOTORS DISARMED OK")
	return True

#'''Main'''
setup_rc()
arm_motors()
takeoff()
land()
disarm_motors()
setup_rc()