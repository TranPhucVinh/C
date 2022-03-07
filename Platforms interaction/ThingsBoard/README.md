## Telemetry

Send data to ThingsBoard Live Demo HTTP server (not HTTPS):

* Using TCP socket as HTTP client: ``tcp_client_send_data.c``
* Using libcurl as HTTP client: ``libcurl_send_data.c``

## Server side API

Get JWT and parsed into ``token`` and ``refreshToken``: ``raw_api_get_jwt.c``

Get JWT and parsed into ``token`` and ``refreshToken`` with ``thingsboard`` library: ``thingsboard_get_jwt.c``

Read response from ``/api/auth/user``: ``thingsboard_auth_user.c``

Get customer ID: ``thingsboard_get_customer_id.c``

Get customer device infos: ``thingsboard_get_device_infos.c``