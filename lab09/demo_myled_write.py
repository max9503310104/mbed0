import serial
import time
serdev = '/dev/ttyACM0'                # use the device name you get from `ls /dev/ttyACM*`
s = serial.Serial(serdev)

s.write(bytes("/myled1/write 1\r", 'UTF-8'))
s.write(bytes("/myled2/write 1\r", 'UTF-8'))
s.write(bytes("/myled3/write 1\r", 'UTF-8'))

while 1:
    s.write(bytes("/myled1/write 0\r", 'UTF-8'))
    time.sleep(1)
    s.write(bytes("/myled1/write 1\r", 'UTF-8'))
    s.write(bytes("/myled3/write 0\r", 'UTF-8'))
    time.sleep(1)
    s.write(bytes("/myled3/write 1\r", 'UTF-8'))

s.close()