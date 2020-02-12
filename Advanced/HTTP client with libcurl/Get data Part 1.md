### Get data from server with CURLOPT_FOLLOWLOCATION

**server.py**

```py
from http.server import HTTPServer, BaseHTTPRequestHandler

class Server(BaseHTTPRequestHandler):
    def do_GET(self): #do_GET is a built-in method and can't be renamed
        if self.path == "/":
            self.send_response(200)
            self.end_headers()   
            #A bytes-like object is required, not 'str'
            self.wfile.write(bytes("Hello World", "utf-8")) 

http = HTTPServer(("localhost", 8000), Server)
http.serve_forever()
```

**HTTP client**

```c
#include <stdio.h>
#include <curl/curl.h>
 
int main(void)
{
  CURL *curl;
  CURLcode res;
 
  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* get a curl handle */ 
  curl = curl_easy_init();
  
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "localhost:8000");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();
  return 0;
}
```

**Result**

Read the compiled file ``./a.out``, this will be ``Hello World``.

### Get data from server with CURLOPT_WRITEFUNCTION

```c
#include <stdio.h>
#include <curl/curl.h>

//nmemb: number of member
//size is always 1
size_t receivedDataCallbackFunction(char *ptr, size_t size, size_t nmemb, void *userdata) {
  //As size*nmemb is long unsigned int, so it has to be %ld
  printf("%ld \n", size*nmemb);
  // printf("%ld \n", size); Result: 1

  //Then print out received data from server
  printf("%s \n", ptr);
  return size*nmemb;
}

int main(void)
{
  CURL *curl;
  CURLcode res;
 
  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* get a curl handle */ 
  curl = curl_easy_init();
  
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "localhost:8000");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, receivedDataCallbackFunction);
    
    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();
  return 0;
}
```

### Get data from server with CURLOPT_WRITEDATA 

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

  // Then print out received data from server
  printf("%s \n", internalReceivedDataStruct->receivedData);
  //Hello World 

  return size*nmemb;
}

int main(void)
{
  CURL *curl;
  CURLcode res;
  struct receivedDataStruct receivedDataChunk;

  receivedDataChunk.receivedData = NULL;
  receivedDataChunk.dataSize = 0;
 
  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* get a curl handle */ 
  curl = curl_easy_init();
  
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "localhost:8000");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, receivedDataCallbackFunction);
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
  return 0;
}
```

**Result**

```
Hello World 
Result outside: Hello World 
```