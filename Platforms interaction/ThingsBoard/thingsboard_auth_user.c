#include "thingsboard.h"

#define HOST        "thingsboard.sysats.tech"
#define PORT        80

#define LOGIN_PATH        "/api/auth/login"
#define API			"/api/auth/user"

#define USER        "tranphucvinh96@gmail.com"
#define PASSWORD    "iotdev_admin"

#define TOKEN_SIZE			600
#define REFRESH_TOKEN_SIZE	500 

char token[TOKEN_SIZE], refreshToken[REFRESH_TOKEN_SIZE];

char *http_response = NULL;

int main(int argc, char *argv[]){
	server_side_api_param_init(HOST, PORT, LOGIN_PATH, USER, PASSWORD);

	bzero(token, TOKEN_SIZE);
	bzero(refreshToken, REFRESH_TOKEN_SIZE);

	get_jwt(token, refreshToken);
	// printf("debug token: %s\n", token);
	// printf("debug refreshToken: %s\n", refreshToken);

	http_response = http_request_for_api_with_jwt(API, "GET", token);
	printf("%s\n", http_response);
	free(http_response);

	return 0;
}