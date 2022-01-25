import bluetooth
import sys

targname = "ESP32test"
targaddr = "8C:AA:B5:8B:53:02"

sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)

devices = bluetooth.discover_devices(lookup_names=True)
print(type(devices))
print("Found %s devices" % len(devices))

for item in devices:
    print(item)
    #print([_ for _ in bluetooth.find_service(address=item) if 'RFCOMM' in _['protocol'] ])

#port = [_ for _ in bluetooth.find_service(address=targaddr) if 'RFCOMM' in _['protocol']][0]['port']

#sock.connect((targaddr,port))
#sock.send("yo")
#sock.send("what's")
#sock.send("up")
#print("sent to " + targname)
