from pymodbus.client.async import ModbusTcpClient as ModbusClient

UNIT = 0x00

client = ModbusClient('192.168.0.40')
client.write_coil(1, True)
rr = client.read_holding_registers(0, 8, unit=UNIT)
result = client.read_coils(1,1)
print(rr.registers)
client.close()
