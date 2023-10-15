# Modbus RTU
Modbus RTU master/client reads multiple holding register of **ES-SM-TH-01S** soil sensor as a slave every 1 second [ES-SM-TH-01S.c](ES-SM-TH-01S.c).
# Modbus TCP
Modbus TCP master/client reads multiple holding register of Modbus TCP slave/server on localhost, port 8000: [modbus_tcp_master.c](modbus_tcp_master.c). This program is intended for comprehensive and easy to understand the Modbus TCP frame's initialization.

Modbus TCP slave/server is initiated by [diagslave](). Result when running [modbus_tcp_master.c](modbus_tcp_master.c):

```sh
tranphucvinh@tranphucvinh:~/Documents/Gitlab/work-in-progress/CPP_workspace$  diagslave -m tcp -p 8000 -a 1

Protocol configuration: MODBUS/TCP
Slave configuration: address = 1, master activity t/o = 3.00s
IP configuration: port = 8000, connection t/o = 60.00s

Server started up successfully.
Listening to network (Ctrl-C to stop)
..........
validateMasterIpAddr: accepting connection from 127.0.0.1
Slave   1: readHoldingRegisters from 2, 1 references
```