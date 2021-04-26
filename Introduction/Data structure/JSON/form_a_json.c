#include <stdio.h>
#include "cJSON.h"

char *formJSONString(){
   cJSON *name = NULL;

   cJSON *json = cJSON_CreateObject();

   if (json == NULL) return;
   name = cJSON_CreateString("User name");
   if (name == NULL) return;

   cJSON_AddItemToObject(json, "name", name);
   char *jsonString = cJSON_Print(json);//Form a JSON string with cJSON_Print()
   return jsonString;
}

int main(){
   printf("JSON string: %s", formJSONString());
   return 0;
}