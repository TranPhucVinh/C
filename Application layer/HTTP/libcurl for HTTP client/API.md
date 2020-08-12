#### curl_easy_init()

``curl_easy_init()``: Start a libcurl easy session

### curl_global_init()

``curl_global_init(long flags)``: sets up the program environment that libcurl needs, this function must be called at least once within a program before the program calls any other function in libcurl.

**CURL_GLOBAL_ALL**: Initialize everything possible. 

### curl_easy_setopt()

```c
CURLcode curl_easy_setopt(CURL *handle, CURLoption option, parameter);
```

### CURLoption option

**CURLOPT_TIMEOUT**: set maximum time the request is allowed to take.

**CURLOPT_FOLLOWLOCATION**

This will follow ``HTTP response 3xx redirection``

```c
CURLcode curl_easy_setopt(CURL *handle, CURLOPT_FOLLOWLOCATION, long enable);
```

``long enable``: 0, disable; 1, enable

**CURLOPT_WRITEFUNCTION**

Set callback function to writing received data.

```c
size_t receivedDataCallbackFunction(char *ptr, size_t size, size_t nmemb, void *userdata)
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, receivedDataCallbackFunction);
```

* ``char *ptr``: A pointer where received data is stored
* ``size_t size``: Always 1
* ``size_t nmemb``: number of member

### curl_slist_append()

```c
struct curl_slist *curl_slist_append(struct curl_slist *list, const char * string);
```

``curl_slist_append`` appends a string to a linked list of strings.