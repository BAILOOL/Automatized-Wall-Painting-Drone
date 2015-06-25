import sys, os
import serial

ser = serial.Serial('COM15', 9600)
received = []

print "Reseting arduino"
#reset arduino first!!!
ser.write(bytes("&"))
print "Waiting for response from arduino"
if ser.read() == '&':
	while True:
		received.append(ser.read())
		length = len(received)
		#print received
		if received[length-1] == '*':
			receivedstring = ''.join(map(str,received[:length-1]))
			print receivedstring
			if  receivedstring == 'Please input a word!':
				input_word = raw_input()
				print "Sending word input to xbee"
				ser.write(bytes(input_word))
			if  receivedstring == 'Printing is completed. Congratulations!':
				print "Exiting the program"
				ser.close()
				ser.close()
				ser.close()
				ser.close()
				ser.close()	
				sys.exit("Mission is completed")
			del received[:]