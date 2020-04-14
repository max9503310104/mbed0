import matplotlib.pyplot as plt
import numpy as np
import serial

t = np.arange(0, 10, 0.1)
x = []
y = []
z = []
tilt = []

serdev = '/dev/ttyACM0'
s = serial.Serial(serdev, baudrate = 115200)
for i in range(100):
    line = s.readline()
    value = float(line)
    x.append(value)
    line = s.readline()
    value = float(line)
    y.append(value)
    line = s.readline()
    value = float(line)
    z.append(value)
    line = s.readline()
    value = int(line)
    tilt.append(value)

plt.subplot(211)
plt.ylim(-1.2, 1.2)
plt.xlabel("t")
plt.ylabel("a")
plt.plot(t, x, label = "x")
plt.plot(t, y, label = "y")
plt.plot(t, z, label = "z")
plt.legend(loc = 'upper right')

plt.subplot(212)
plt.xlabel("t")
plt.ylabel("tilt")
plt.stem(t, tilt)

plt.show()

s.close()