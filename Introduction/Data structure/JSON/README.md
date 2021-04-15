cJSON library from ``DaveGamble/cJSON``

cJSON accepts ``""`` for field name, and doesn't accept ``''``.

### Examples

* ``parse_one_field.c``: Parse a JSON string with one field
* ``parse_from_file.c``: Parse JSON value from file ``json.txt``

``json.txt``:

```
{"string": "Text"}
```