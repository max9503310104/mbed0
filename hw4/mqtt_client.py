import paho.mqtt.client as paho
import time
import matplotlib.pyplot as plt

ax = []
ay = []
az = []
t = []
start = time.time()

# https://os.mbed.com/teams/mqtt/wiki/Using-MQTT#python-client

# MQTT broker hosted on local machine
mqttc = paho.Client()

# Settings for connection
# TODO: revise host to your ip
host = "192.168.43.44"
topic = "Mbed"

# Callbacks
def on_connect(self, mosq, obj, rc):
      print("Connected rc: " + str(rc))

def on_message(mosq, obj, msg):
      #print("[Received] Topic: " + msg.topic + ", Message: " + str(msg.payload) + "\n");
      #print(msg.payload)
      char = [chr(msg.payload[0]), chr(msg.payload[1]), chr(msg.payload[2]), chr(msg.payload[3]),
              chr(msg.payload[4]), chr(msg.payload[5]), chr(msg.payload[6]),
              chr(msg.payload[8]), chr(msg.payload[9]), chr(msg.payload[10]), chr(msg.payload[11]),
              chr(msg.payload[12]), chr(msg.payload[13]), chr(msg.payload[14]),
              chr(msg.payload[16]), chr(msg.payload[17]), chr(msg.payload[18]), chr(msg.payload[19]),
              chr(msg.payload[20]), chr(msg.payload[21]), chr(msg.payload[22])]
      s0 = char[0] + char[1] + char[2] + char[3] + char[4] + char[5] + char[6]
      s1 = char[7] + char[8] + char[9] + char[10] + char[1] + char[12] + char[13]
      s2 = char[14] + char[15] + char[16] + char[17] + char[18] + char[19] + char[20]
      a0 = float(s0)
      a1 = float(s1)
      a2 = float(s2)
      t0 = time.time() - start
      t0 = int(t0 * 10000)
      t0 /= 10000
      print(a0, a1, a2, t0)
      ax.append(a0)
      ay.append(a1)
      az.append(a2)
      t.append(t0)
      if (t0 > 20):
            mqttc.disconnect()

def on_subscribe(mosq, obj, mid, granted_qos):
      print("Subscribed OK")

def on_unsubscribe(mosq, obj, mid, granted_qos):
      print("Unsubscribed OK")

# Set callbacks
mqttc.on_message = on_message
mqttc.on_connect = on_connect
mqttc.on_subscribe = on_subscribe
mqttc.on_unsubscribe = on_unsubscribe

# Connect and subscribe
print("Connecting to " + host + "/" + topic)
mqttc.connect(host, port=1883, keepalive=60)
mqttc.subscribe(topic, 0)

# Loop forever, receiving messages
mqttc.loop_forever()

# Plot
plt.plot(t, ax, label = "x")
plt.plot(t, ay, label = "y")
plt.plot(t, az, label = "z")
plt.legend(loc = 'upper right')
plt.xlabel("t")
plt.ylabel("a")
plt.show()

