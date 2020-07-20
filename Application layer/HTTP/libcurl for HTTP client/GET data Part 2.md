### GET data from multiple route

* Get data every 1 second
* Working with route ``/`` and ``/test``

**HTTP Server**

```py
from http.server import HTTPServer, BaseHTTPRequestHandler

class Server(BaseHTTPRequestHandler):
    def do_GET(self): #do_GET is a built-in method and can't be renamed
        if self.path == "/":
            self.send_response(200)
            self.end_headers()   
            #A bytes-like object is required, not 'str'
            self.wfile.write(bytes("Hello World", "utf-8")) 
        elif self.path == "/test":
            self.send_response(200)
            self.end_headers()   
            #A bytes-like object is required, not 'str'
            self.wfile.write(bytes("test route", "utf-8"))     

http = HTTPServer(("localhost", 8000), Server)
http.serve_forever()
```

**httpClient.c**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct receivedDataStruct {
  char *receivedData;
  size_t dataSize;
};

size_t receivedDataCallbackFunction(char *ptr, size_t size, size_t nmemb, void *userdata) {
  size_t dataReceivedSize = size*nmemb; //get size of the newly received data

  //convert void *userdata to struct receivedDataStruct*
  struct receivedDataStruct *internalReceivedDataStruct = (struct receivedDataStruct*) userdata;

  //Reallocated the size of receivedData in receivedDataStruct
  internalReceivedDataStruct->receivedData = realloc(internalReceivedDataStruct->receivedData, internalReceivedDataStruct->dataSize + dataReceivedSize + 1);

  //Now copy the content in ptr to userdata
  memcpy(internalReceivedDataStruct->receivedData, ptr, dataReceivedSize);

  internalReceivedDataStruct->dataSize += dataReceivedSize;

  return size*nmemb;
}

void curl_thread(char *urlPointer){
  CURL *curl;
  CURLcode res;
  struct receivedDataStruct receivedDataChunk;

  receivedDataChunk.receivedData = NULL;
  receivedDataChunk.dataSize = 0;

  /* get a curl handle */ 
  curl = curl_easy_init();
  
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, urlPointer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, receivedDataCallbackFunction);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &receivedDataChunk);

    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }

  printf("Result outside: %s \n", receivedDataChunk.receivedData);
  //Result outside: Hello World 

  curl_global_cleanup();
}

int main(void)
{
  
  char *url1 = "localhost:8000";
  char *url2 = "localhost:8000/test";
  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);
 
  while(1){
    sleep(1);
    curl_thread(url1);
    curl_thread(url2);
  }
  return 0;
}
```