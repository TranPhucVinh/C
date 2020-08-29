## Install

``libcurl`` is an open-source library support several application protocols.

**Install libary libcurl**

``sudo apt-get install libcurl4 libcurl4-openssl-dev -y``

To build a program with libcurl (as an external library): ``gcc httpClient.c -lcurl``

## Example

* Read return data from GET request to HTTP server with ``CURLOPT_FOLLOWLOCATION``: ``get_with_curl_followlocation.c``

* Read return data from GET request to HTTP server with ``CURLOPT_WRITEFUNCTION``: ``get_with_curl_writefunction.c``

* Read return data from GET request to HTTP server with ``CURLOPT_WRITEDATA``: ``get_with_curl_writedata.c``

All 3 examples work fine with all HTTP webpage, HTTPS webpage and local Python HTTP server.

### Example: GET data from multiple route

* Get data every 1 second
* Working with route ``/`` and ``/test``

**HTTP Server**: ``http_server_send_data.py``

**HTTP Client**: ``http_client_handle_multiple_route.c``

### Example: Send data

Send data every 1 second to server with POST request

**HTTP server**: ``http_server_receive_data.py``

**HTTP client**: ``http_client_send_data.c``