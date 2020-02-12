### Send data to HTTP server with POST request

**server.py**

```py
from http.server import HTTPServer, BaseHTTPRequestHandler

class Server(BaseHTTPRequestHandler):
  def do_POST(self): #do_GET is a built-in method and can't be renamed
    if self.path == "/":
      self.send_response(200)
      content_length = int(self.headers['Content-Length']) # <--- Gets the size of data
      received_data = self.rfile.read(content_length)
      print("POST request,\nPath: %s,\nHeaders:%s,\nData: %s" % (str(self.path), str(self.headers), received_data.decode('utf-8')))
      self.end_headers()

# http = HTTPServer(("localhost", 8000), Server)
http = HTTPServer(("192.168.1.21", 8000), Server)
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
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */ 
    curl_easy_setopt(curl, CURLOPT_URL, "192.168.1.21:8000");
    /* Now specify the POST data */ 
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "Hello World");
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;
}
```

### Send data every 1 second to server

```c
#include <stdio.h>
#include <curl/curl.h>
 
void curl_function(char *urlPointer){
  CURL *curl;
  CURLcode res;
 
  /* get a curl handle */ 
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */ 
    curl_easy_setopt(curl, CURLOPT_URL, urlPointer);
    /* Now specify the POST data */ 
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "Hello World");
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
}
int main(void)
{ 
  char *url1 = "localhost:8000";
  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);
 
  while(1){
    sleep(1);
    curl_function(url1);
  }

  return 0;
}
```