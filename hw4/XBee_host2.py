import serial
import time
import threading
import matplotlib.pyplot as plt

serdev = '/dev/ttyUSB0'
s = serial.Serial(serdev, 9600)

start = time.time()
n = []
t = []

first = 1
print("start sending RPC")
i = 20
while i > 0:
    i = i - 1
    s.write("/query/run\r".encode())
    char = s.read(2)
    print(char)

    n.append(int(char))
    t0 = time.time() - start
    t0 = int(t0 * 100) / 100
    t.append(t0)
    
    time.sleep(1)

n[0] = 0
print(n)
print(t)
plt.plot(t, n)
plt.show()

s.close()