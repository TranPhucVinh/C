## Telemetry

### Telemetry with TCP client has HTTP client

Features:

* WiFi not connected when program starts: Print ``gethostbyname: Host name lookup failure``
* WiFi connected with Internet when program starts: Start the ThingsBoard telemetry process with HTTP request
* While telemetry process is happening, network is disconnected: With ``DEBUG`` mode is on, program will get blocked. If WiFi with Internet is then recovered, program exits.

Program: [tcp_client_for_telemetry.c](tcp_client_for_telemetry.c)

### Telemetry with libcurl as HTTP client

* Telemetry to ThingsBoard Live Demo HTTP server (not HTTPS) with libcurl as HTTP client
* Program: [libcurl_send_data.c](libcurl_send_data.c)

## Server side API

Get JWT and parsed into ``token`` and ``refreshToken``: ``raw_api_get_jwt.c``

### For [thingsboard](thingsboard) library

Source code are built with Bazel with attached [BUILD](BUILD) file and file architecture like below:

```
|--cJSON-1.7.15 //cJSON-1.7.15 folder to store cJSON source code
|--thingsboard //thingsboard folder to store thingsboard source code
|--main.c
|--WORKSPACE
|--BUILD
```

Get JWT and parsed into ``token`` and ``refreshToken``: [thingsboard_get_jwt.c](thingsboard_get_jwt.c)

Read response from ``/api/auth/user``: [thingsboard_auth_user.c](thingsboard_auth_user.c)

Get customer device infos: [thingsboard_get_device_infos.c](thingsboard_get_device_infos.c)

Get all access token from 10 devices: [thingsboard_get_access_token.c](thingsboard_get_access_token.c)

An example of a customer devices info json file: [customer_device_infos.json](customer_device_infos.json)
