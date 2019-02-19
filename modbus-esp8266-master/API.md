# Modbus Master-Slave Library for ESP8266/ESP32

## API

### Add [multiple] regs

```c
bool addHreg(uint16_t offset, uint16_t value = 0, uint16_t numregs = 1);
bool addCoil(uint16_t offset, bool value = false, uint16_t numregs = 1);
bool addIsts(uint16_t offset, bool value = false, uint16_t numregs = 1);
bool addIreg(uint16_t offset, uint16_t value = 0, uint16_t nemregs = 1);
```

### Write reg

```c
bool Hreg(uint16_t offset, uint16_t value);
bool Coil(uint16_t offset, bool value);
bool Ists(uint16_t offset, bool value);
bool Ireg(uint16_t offset, uint16_t value);
```

### Read reg

```c
uint16_t Hreg(uint16_t offset);
bool Coil(uint16_t offset);
bool Ists(uint16_t offset);
uint16_t Ireg(uint16_t offset);
```

### Remove reg

```c
bool removeHreg(uint16_t offset, uint16_t numregs = 1);
bool removeCoil(uint16_t offset, uint16_t numregs = 1);
bool removeIsts(uint16_t offset, uint16_t numregs = 1);
bool removeIreg(uint16_t offset, uint16_t numregs = 1);
```

### Query [multiple] regs from remote slave

```c
uint16_t pullCoil(IPAddress ip, uint16_t from, uint16_t to, uint16_t numregs = 1, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
uint16_t pullIsts(IPAddress ip, uint16_t from, uint16_t to, uint16_t numregs = 1, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
uint16_t pullHreg(IPAddress ip, uint16_t from, uint16_t to, uint16_t numregs = 1, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
uint16_t pullIreg(IPAddress ip, uint16_t from, uint16_t to, uint16_t numregs = 1, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
uint16_t pullHregToIreg(IPAddress ip, uint16_t offset, uint16_t startreg, uint16_t numregs = 1, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
uint16_t pullCoilToIsts(IPAddress ip, uint16_t offset, uint16_t startreg, uint16_t numregs = 1, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
```

Result is saved to local registers. Method returns corresponding transaction id. [ip/from] or [ip/offset] - slave, [to] or [startreg] - local

### Send [multiple] regs to remote slave

```c
uint16_t pushCoil(IPAddress ip, uint16_t to, uint16_t from, uint16_t numregs = 1, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
uint16_t pushHreg(IPAddress ip, uint16_t to, uint16_t from, uint16_t numregs = 1, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
uint16_t pushIstsToCoil(IPAddress ip, uint16_t to, uint16_t from, uint16_t numregs = 1, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
uint16_t pushIregToHreg(IPAddress ip, uint16_t to, uint16_t from, uint16_t numregs = 1, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
```

Write Register/Coil or Write Multiple Registers/Coils Modbus function selected automaticly depending on 'numregs' value. [ip/to] - slave, [from] - local

### Write [multiple] values to remote slave reg

```c
uint16_t writeCoil(IPAddress ip, uint16_t offset, bool value, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
uint16_t writeHreg(IPAddress ip, uint16_t offset, uint16_t value, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
```

Write single value to remote Hreg/Coil.

```c
uint16_t writeCoil(IPAddress ip, uint16_t offset, bool* value, uint16_t numregs = 1, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
uint16_t writeHreg(IPAddress ip, uint16_t offset, uint16_t* value, uint16_t numregs = 1, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
```

Write multiple values from array to remote Coil/Hreg.

### Read values from multiple remote slave regs

```c
uint16_t readCoil(IPAddress ip, uint16_t offset, bool* value, uint16_t numregs = 1, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
uint16_t readIsts(IPAddress ip, uint16_t offset, bool* value, uint16_t numregs = 1, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
uint16_t readHreg(IPAddress ip, uint16_t offset, uint16_t* value, uint16_t numregs = 1, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
uint16_t readIreg(IPAddress ip, uint16_t offset, uint16_t* value, uint16_t numregs = 1, cbTransaction cb = nullptr, uint8_t uint = MODBUSIP_UNIT);
```

Read values from remote Hreg/Coil/Ireg/Ists to array.

```c
void autoConnect(bool enabled = true);
```

Set mode for automatic connect on read*\write*\push*\pull* calls. Disabled by default.

### Callbacks

```c
void cbEnable(bool state = TRUE);
void cbDisable();
```

Callback generation control. Callback generation is enabled by default. *Has no effect on transactions callbacks.*

```c
void onConnect(cbModbusConnect cb);
void onDisonnect(cbModbusConnect cb);
```

Assign callback function on new incoming connection event.

```c
typedef bool (*cbModbusConnect)(IPAddress ip);
```

Connect event callback function definition. For onConnect event client's IP address is passed as argument. onDisconnect callback function always gets INADDR_NONE as parameter.

```c
typedef uint16_t (*cbModbus)(TRegister* reg, uint16_t val);
```

Get/Set register callback function definition. Pointer to TRegister structure (see source for details) of the register and new value are passed as arguments.

```c
typedef bool (*cbTransaction)(Modbus::ResultCode event, uint16_t transactionId, void* data);
```

Transaction end callback function definition. *data* is currently reserved.

```c
IPAddress eventSource();
```

Should be called from onGet/onSet or transaction callback function. Returns IP address of remote requesting operation or INADDR_NONE for local.

*Note:* For transaction callback INADDR_NONE returned in case if transaction is timedout.

```c
bool onSetCoil(uint16_t address, cbModbus cb = nullptr, uint16_t numregs = 1);
bool onSetHreg(uint16_t address, cbModbus cb = nullptr, uint16_t numregs = 1);
bool onSetIsts(uint16_t address, cbModbus cb = nullptr, uint16_t numregs = 1);
bool onSetIreg(uint16_t address, cbModbus cb = nullptr, uint16_t numregs = 1);
```

Assign callback function on register modify event. Multiple sequental registers can be affected by specifing `numregs` parameter.


```c
bool onGetCoil(uint16_t address, cbModbus cb = nullptr, uint16_t numregs = 1);
bool onGetHreg(uint16_t address, cbModbus cb = nullptr, uint16_t numregs = 1);
bool onGetIsts(uint16_t address, cbModbus cb = nullptr, uint16_t numregs = 1);
bool onGetIreg(uint16_t address, cbModbus cb = nullptr, uint16_t numregs = 1);
```

Assign callback function on register query event. Multiple sequental registers can be affected by specifing `numregs` parameter.

```c
bool removeOnGetCoil(uint16_t offset, cbModbus cb = nullptr, uint16_t numregs = 1);
bool removeOnSetCoil(uint16_t offset, cbModbus cb = nullptr, uint16_t numregs = 1);
bool removeOnGetHreg(uint16_t offset, cbModbus cb = nullptr, uint16_t numregs = 1);
bool removeOnSetHreg(uint16_t offset, cbModbus cb = nullptr, uint16_t numregs = 1);
bool removeOnGetIsts(uint16_t offset, cbModbus cb = nullptr, uint16_t numregs = 1);
bool removeOnSetIsts(uint16_t offset, cbModbus cb = nullptr, uint16_t numregs = 1);
bool removeOnGetIreg(uint16_t offset, cbModbus cb = nullptr, uint16_t numregs = 1);
bool removeOnSetIreg(uint16_t offset, cbModbus cb = nullptr, uint16_t numregs = 1);
```

Disconnect specific callback function or all callbacks of the type if cb=NULL.

### Macros

```c
#define COIL_VAL(v)
#define COIL_BOOL(v)
#define ISTS_VAL(v)
#define ISTS_BOOL(v)
```

### ModBus IP specific

```c
void task();
```

### ModBus IP Slave specific

```c
void begin(); // Depricated. Use slave() instead.
void slave();
```

### ModBus IP Master specific

```c
void master();
bool connect(IPAddress ip);
bool disconnect(IPAddress ip);
bool isTransaction(uint16_t id);
bool isConnected(IPAddress ip);
void dropTransactions();
```

```c
void autoConnect(bool enabled);
```

Select behavior of executing read/write/pull/push. If autoConnect disabled (default) execution returns error if connection to slave is not already established. If autoConnect is enabled trying to establish connection during read/write/pull/push function call.

### Callback example

```arduino
ModbusIP mb;
bool coil = false; // Define external variable to get/set value
uint16_t cbCoilSet(TRegister* reg, uint16_t val) { // 'reg' is pointer to reg structure to modify, 'val' is new register value
  Serial.print("Set query from ");
  Serial.println(mb.eventSource().toString());
  coil = COIL_BOOL(val);  // Assign value to external variable
  return val; // Returns value to be saved to TRegister structure
}
uint16_t cbCoilGet(TRegister* reg, uint16_t val) {
  Serial.print("Get query from ");
  Serial.println(mb.eventSource().toString());
  return COIL_VAL(coil); // Override value to be returned to ModBus master as reply for current request
}
bool cbConn(IPAddress ip) {
  Serial.println(ip);
  return true; // Return 'true' to allow connection or 'false' to drop connection
}
ModbusIP mb; // ModbusIP object
void setup() {
...
  mb.onConnect(cbConn); // Add callback on connection event
  mb.slave(); // Accept incoming Modbus connections
  mb.addCoil(COIL_NR);     // Add Coil
  mb.onSetCoil(COIL_NR, cbCoilSet); // Add callback on Coil COIL_NR value set
  mb.onGetCoil(COIL_NR, cbCoilGet); // Add callback on Coil COIL_NR value get
...
}
void loop() {
...
  mb.task();
...
}
```

## Contributions

https://github.com/emelianov/modbus-esp8266

a.m.emelianov@gmail.com

Original version:

https://github.com/andresarmento/modbus-esp8266
https://github.com/andresarmento/modbus-arduino

prof (at) andresarmento (dot) com

## License

The code in this repo is licensed under the BSD New License. See LICENSE.txt for more info.
