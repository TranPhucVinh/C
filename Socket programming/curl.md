
**CURLOPT_URL - provide the URL to use in the request**

``CURLcode curl_easy_setopt(CURL *handle, CURLOPT_URL, char *URL);``

**CURLOPT_POSTFIELDS - specify data to POST to server**

``CURLcode curl_easy_setopt(CURL *handle, CURLOPT_POSTFIELDS, char *postdata);``

```c
#include <iostream>
#include <curl/curl.h>

using namespace std;

main() {
	CURL *curl_handle;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);// init curl goes with CURL_GLOBAL_ALL

	curl_handle = curl_easy_init(); // create pointer curl
	if(curl_handle){
		cout << "CURL has been initiated \n";
		curl_easy_setopt(curl_handle, CURLOPT_URL, "192.168.0.121:89"); // curl set option
		curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, "transfer data");
		res = curl_easy_perform(curl_handle);
		if (res != CURLE_OK){
			cout << "curl_easy_perform() failed "  <<curl_easy_strerror(res);
		}
		else {
			cout << "OK";
			curl_easy_cleanup(curl_handle);
		}
	}
	curl_global_cleanup();
}
```

Reference: [libcurl API](https://curl.haxx.se/libcurl/c/)
