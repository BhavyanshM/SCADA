import kivy
kivy.require('1.0.6') # replace with your current kivy version !

from kivy.app import App
from kivy.uix.label import Label

from pymodbus.client.sync import ModbusTcpClient
import time

UNIT = 0x00

client = ModbusTcpClient('192.168.0.40')
#client.write_coil(1, True)

f = open("log.txt", 'a')
f.write("\n----------------------------------------------------------------------\n\n"+time.ctime()+"\n\n")

# while True:
rr = client.read_holding_registers(0, 8, unit=UNIT)
#result = client.read_coils(1,1)
print(rr.registers)
time.sleep(0.1)
data = str(rr.registers)
f.write(data+"\n")

f.close()

client.close()

class MyApp(App):

    def build(self):
        return Label(text=str(rr.registers))


if __name__ == '__main__':
    MyApp().run()
