from pymodbus.client.sync import ModbusTcpClient
import time

UNIT = 0x00

client = ModbusTcpClient('192.168.0.40')
#client.write_coil(1, True)

f = open("log.txt", 'a')
f.write("\n----------------------------------------------------------------------\n\n"+time.ctime()+"\n\n")

while True:
	rr = client.read_holding_registers(0, 8, unit=UNIT)
	#result = client.read_coils(1,1)
	print(rr.registers)
	time.sleep(0.01)
	f.write(str(rr.registers)+"\n")

f.close()

client.close()
