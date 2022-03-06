## Telemetry

Send data to ThingsBoard Live Demo HTTP server (not HTTPS):

* Using TCP socket as HTTP client: ``tcp_client_send_data.c``
* Using libcurl as HTTP client: ``libcurl_send_data.c``

## Server side API

Get JWT and parsed into ``token`` and ``refreshToken``: ``get_jwt.c``