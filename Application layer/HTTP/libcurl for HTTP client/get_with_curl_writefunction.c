#include <stdio.h>
#include <curl/curl.h>

// const char host[] = "localhost:8000";
const char host[] = "arduino.vn";

/*
    nmemb: number of member
    size: always 1
*/
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
 
  curl_global_init(CURL_GLOBAL_ALL); // In Windows, this will init the winsock stuff 
 
  curl = curl_easy_init();   // get a curl handle
  
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, host);
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