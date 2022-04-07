## Telemetry

Send data to ThingsBoard Live Demo HTTP server (not HTTPS):

* Using TCP socket as HTTP client: ``tcp_client_send_data.c``
* Using libcurl as HTTP client: ``libcurl_send_data.c``

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
