### Set up

In order to allow other HTTP client to interact with Firebase realtime database, the rule is needed to be changed.

In ``Realtime Database``, go to ``Rules`` then ``Edit rules``. Chnage ``read`` and ``write`` to ``true``.

### Examples

* ``read_data.c``: Read data from database ``test.json``
* ``send_data.c``: Send data to database ``test.json``