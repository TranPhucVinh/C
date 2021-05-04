cJSON library from ``DaveGamble/cJSON``

cJSON accepts ``""`` for field name, and doesn't accept ``''``.

### Examples

* ``parse_multiple_fields.c``: Parse a JSON string with multiple fields
* ``parse_from_file.c``: Parse JSON value from file ``json.txt``
* ``form_a_json.c``: Form a JSON string to print out.

``json.txt``:

```
{"string": "Text"}
```