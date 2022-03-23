# Library

cJSON library from ``DaveGamble/cJSON``, [version 1.7.15, released this Aug 25, 2021](https://github.com/DaveGamble/cJSON/releases/tag/v1.7.15). For software implementations, download the source code from this release link.

cJSON accepts ``""`` for field name, and doesn't accept ``''``.

# Implementations

* [Form JSON](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/JSON/Form%20JSON.md)
* Parse JSON
* Update JSON

## Parse JSON

Initial step to parse a char pointer JSON:

```c
const char *json_string = "{\"id\": 100, \"text\":\"hello, world\"}";
cJSON *json = cJSON_Parse(json_string);
```

**Example**: Parse char pointer JSON read from a file into string, int and array fields [parse_json_by_fields.c](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/JSON/parse_json_by_fields.c)

**Example**: Parsing with ``cJSON_GetObjectItem()``

```c
const char *json_string = "{\"id\": 100, \"text\":\"hello, world\"}";

int main(){
    cJSON *id, *text;
    cJSON *json = cJSON_Parse(json_string);

    id = cJSON_GetObjectItem(json, "id");
    printf("%d\n", id->valueint);

    text = cJSON_GetObjectItem(json, "text");
    printf("%s\n", text->valuestring);
    return 0;
}
```

## Update JSON

Value of JSON fields can be updated with:

* ``cJSON_SetValuestring()``
* ``cJSON_SetIntValue()``

Update value for a specific field: [change_by_field.c]()