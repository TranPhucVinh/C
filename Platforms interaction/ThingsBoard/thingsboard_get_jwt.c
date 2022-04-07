#include "thingsboard.h"

#define HOST        "thingsboard.sysats.tech"
#define PORT        80
#define LOGIN_PATH        "/api/auth/login"

#define USER        "tranphucvinh96@gmail.com"
#define PASSWORD    "iotdev_admin"

#define BUFFSIZE        	4096 //Size must be big to get all JWT
#define TOKEN_SIZE			600
#define REFRESH_TOKEN_SIZE	500 

char token[TOKEN_SIZE], refreshToken[REFRESH_TOKEN_SIZE];

int main(int argc, char *argv[]){
	server_side_api_param_init(HOST, PORT, LOGIN_PATH, USER, PASSWORD);

	bzero(token, TOKEN_SIZE);
	bzero(refreshToken, REFRESH_TOKEN_SIZE);

	get_jwt(token, refreshToken, BUFFSIZE);
	printf("token: %s\n", token);
	printf("refreshToken: %s\n", refreshToken);
	return 0;
}
