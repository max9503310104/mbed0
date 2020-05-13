import serial
import time
serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)

s.write(bytes("/LEDControl/run 4 5\r", 'UTF-8'))
#line=s.readline() # Read an echo string from K66F terminated with '\n' (pc.putc())
#print(line)


