#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

const char host[] = "arduino.vn";

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
    curl_easy_setopt(curl, CURLOPT_URL, host);
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