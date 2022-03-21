# Library

cJSON library from ``DaveGamble/cJSON``

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