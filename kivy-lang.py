import kivy
kivy.require('1.0.6') # replace with your current kivy version !

from kivy.clock import Clock
from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.garden.gauge import Gauge
from kivy.properties import BoundedNumericProperty
from pymodbus.client.sync import ModbusTcpClient



global i, client
i = 0
client = ModbusTcpClient('192.168.0.40')

class ScatterTextWidget(BoxLayout):
	pass

class MyApp(App):
    def build(self):
    	Clock.schedule_interval(self.gauge_update, 0.1)
    	return ScatterTextWidget()

    def gauge_update(self, *args):
    	global i, client
    	i += 1
    	rr = client.read_holding_registers(0, 8, unit=0x00)
    	myGauge = self.root.ids.my_gauge
    	regValue = rr.registers[1]
    	myGauge.value = regValue
    	print('Update:' + str(regValue))


if __name__ == '__main__':
    MyApp().run()
