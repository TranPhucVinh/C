## Form JSON

Form a JSON string

```c
#include <stdio.h>
#include "cJSON-1.7.15/cJSON.h"

char *form_json_string(){
   	cJSON *name = NULL, *id = NULL;

	cJSON *json = cJSON_CreateObject();
	if (json == NULL) return "NULL";

   	name = cJSON_CreateString("User name");
   	if (name == NULL) return "NULL";
	cJSON_AddItemToObject(json, "name", name);

	id = cJSON_CreateNumber(123);
	if (id == NULL) return "NULL";
	cJSON_AddItemToObject(json, "id", id);


	char *json_string = cJSON_Print(json);//Form a JSON string with cJSON_Print()
	return json_string;
}

int main(){
   printf("%s\n", form_json_string());
   return 0;
}
```

```json
{
	"name":	"User name"
}
```

# Array as member

* ``cJSON_CreateIntArray``: Create int array (e.g: ``int array[] = {1, 2, 3}``) as a field of the JSON
* ``cJSON_CreateFloatArray()``
* ``cJSON_CreateStringArray()``
* ``cJSON_CreateArray``: For all types of array: int array, float array, string array and array includes JSON

Array include JSON:

```json
{
	"json_array":	[{"number":	0}, {"number":	1}, {"number":	2}, {"number":	3}, {"number":	4}]
}
```

To get JSON value inside every member of a JSON array, use ``cJSON_ArrayForEach()``, check ``parse_array_field()`` function inside ``parse_json_by_fields.c`` example for its implementation.

## Form a JSON string with int array field

```c
#include <stdio.h>
#include "cJSON.h"

int array[] = {1, 2, 3};

char *formJSONString(){
	cJSON *name = NULL, *int_array = NULL;

	cJSON *json = cJSON_CreateObject();

	if (json == NULL) return NULL;

	name = cJSON_CreateString("User name");
	if (name == NULL) return NULL;

	int_array = cJSON_CreateIntArray(array, 3);
	if (int_array == NULL) return NULL;

	cJSON_AddItemToObject(json, "name", name);
	cJSON_AddItemToObject(json, "int_array", int_array);

	char *jsonString = cJSON_Print(json);//Form a JSON string with cJSON_Print()
	return jsonString;
}

int main(){
   printf("%s\n", formJSONString());
   return 0;
}
```
**Result**
```json
{
	"name":	"User name",
	"int_array":	[1, 2, 3]
}
```
### Form a JSON string with an array that includes JSON

```c
#include <stdio.h>
#include "cJSON.h"

char *formJSONString(){
	cJSON *name = NULL, *json_array = NULL, *json_array_member = NULL;
	cJSON *number = NULL;

	cJSON *json = cJSON_CreateObject();

	if (json == NULL) return NULL;

	name = cJSON_CreateString("User name");
	if (name == NULL) return NULL;

	json_array = cJSON_CreateArray();
	if (json_array == NULL) return NULL;

	cJSON_AddItemToObject(json, "name", name);
	cJSON_AddItemToObject(json, "json_array", json_array);

	for (int index = 0; index < 5; index++){
		json_array_member = cJSON_CreateObject();
		if (json_array_member == NULL) return NULL;
		cJSON_AddItemToArray(json_array, json_array_member);

		number = cJSON_CreateNumber(index);
		if (number == NULL) return NULL;
		cJSON_AddItemToObject(json_array_member, "number", number);
	}

	char *jsonString = cJSON_Print(json);//Form a JSON string with cJSON_Print()
	return jsonString;
}

int main(){
   printf("%s\n", formJSONString());
   return 0;
}
```
**Result**
```json
{
	"name":	"User name",
	"json_array":	[{"number":	0}, {"number":	1}, {"number":	2}, {"number":	3}, {"number":	4}]
}
```
