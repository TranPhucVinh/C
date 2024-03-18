#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseBytes(const char* stringParameter, char sep, unsigned long* stringResult, int maxBytes, int base);

int main(){
	char ipString[] = "192.168.255.255";
    /*
		ip array must be unsigned long for being converted by strtoul. If set as char ip[4], the result will be signed number as char by default is signed number
	*/	
	unsigned long ip[4];

	parseBytes(ipString, '.', ip, 4, 10);

	printf("ip[1]: %d\n", ip[0]);
	printf("ip[2]: %d\n", ip[1]);
	printf("ip[3]: %d\n", ip[2]);
	printf("ip[4]: %d\n", ip[3]);
}

void parseBytes(const char* stringParameter, char sep, unsigned long* stringResult, int maxBytes, int base) {
    for (int i = 0; i < maxBytes; i++) {
        stringResult[i] = strtoul(stringParameter, NULL, base);  // Convert byte: strtoul: string to unsigned long
        stringParameter = strchr(stringParameter, sep);               // Find next separator
        if (stringParameter == NULL || *stringParameter == '\0') {
            break;                            // No more separators, exit
        }
        stringParameter++;                                // Point to next character after separator
    }
}
