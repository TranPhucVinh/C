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