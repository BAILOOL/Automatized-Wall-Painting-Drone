import sys, os
sys.path.append(r"c:\Python27\Lib\site-packages")
sys.path.append(r"C:\Python27\Lib")
import serial, clr
clr.AddReference('System')
from System import *

with IO.Ports.SerialPort("COM15") as ser:
	ser.BaudRate = 9600
	ser.DataBits = 8
	ser.Open()

	received = []

	filename = "InputWord.txt"
	path = "C:\Users\Mid\Desktop\Sam&Alex\mission planner & python"
	print "Opening the file..."

	fullpath = os.path.join(path, filename)
	target = open(fullpath, 'r')

	print "Reseting arduino"
	#reset arduino first!!!
	ser.write(bytes("&"))
	if ser.read() == '&':
		while True:
			received.append(ser.read())
			length = len(received)
			#print received
			if received[length-1] == '*':
				receivedstring = ''.join(map(str,received[:length-1]))
				print receivedstring
				if  receivedstring == 'Please input a word!':
					input_word = target.readline()
					target.close()
					print "Sending word input to xbee"
					ser.write(bytes(input_word))
				if  receivedstring == 'Printing is completed. Congratulations!':
					print "Exiting the program"
					ser.close()
					sys.exit("Mission is completed")
				del received[:]