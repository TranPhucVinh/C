#include <stdio.h>
#include <curl/curl.h>

void curl_function(char *urlPointer){
  CURL *curl;
  CURLcode res;
 
  struct curl_slist *headers = NULL;

  /*
    From a proper HTTP request with link list database
    Accept: application/json
    Content-Type: application/json

    headers must be assigned after every curl_slist_append for proper linklist
  */
  headers = curl_slist_append(headers, "Accept: application/json");
  headers = curl_slist_append(headers, "Content-Type: application/json");

  /* get a curl handle */ 
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */ 
    curl_easy_setopt(curl, CURLOPT_URL, urlPointer);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"libcurl\": \"Hello, World!\"}");
 
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
  char *url1 = "demo.thingsboard.io/api/v1/gG5svlcW9VB5fVQBpCNC/telemetry";
  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);

  while(1){
    sleep(1);
    curl_function(url1);
  }

  return 0;
}