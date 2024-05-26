NTP (**Network Time Protocol**) works on UDP socket.

NTP uses two types of messages: **clock synchronization** and **NTP control messages**.

A clock synchronization message is encapsulated in a UDP message, in the format shown:

```c
struct ntp_packet {
    uint8_t li_vn_mode;      // Eight bits. li, vn, and mode.
    uint8_t stratum;         // Eight bits. Stratum level of the local clock.
    uint8_t poll;            // Eight bits. Maximum interval between successive messages.
    uint8_t precision;       // Eight bits. Precision of the local clock.
    uint32_t rootDelay;      // 32 bits. Total round-trip delay time.
    uint32_t rootDispersion; // 32 bits. Max error aloud from primary clock source.
    uint32_t refId;          // 32 bits. Reference clock identifier.
    uint32_t refTm_s;        // 32 bits. Reference time-stamp seconds.
    uint32_t refTm_f;        // 32 bits. Reference time-stamp fraction of a second.
    uint32_t origTm_s;       // 32 bits. Originate time-stamp seconds.
    uint32_t origTm_f;       // 32 bits. Originate time-stamp fraction of a second.
    uint32_t rxTm_s;         // 32 bits. Received time-stamp seconds.
    uint32_t rxTm_f;         // 32 bits. Received time-stamp fraction of a second.
    uint32_t txTm_s;         // 32 bits and the most important field the client cares about. Transmit time-stamp seconds.
    uint32_t txTm_f;         // 32 bits. Transmit time-stamp fraction of a second.
};
```

NTP is a MSB protocol. For **li_vn_mode** setup, with LI = 0, VN = 3 (IPv4 only), Mode = 3 (client), the value will be: (00 li) (011 vn) (011 mode) = 0x1b

``li_vn_mode`` includes:
| li | vn | mode|
| ------- |:------:|:------:|
| 0 - 1 | 2 - 4 | 5 - 7 |

* **LI** (**Leap Indicator**): A 2-bit leap indicator. When set to 11, it warns of an alarm condition (clock unsynchronized); when set to any other value, it is not to be processed by NTP.
* **VN** (**Version Number**): A 3-bit version number that indicates the version of NTP. The latest version is version 4.
* **Mode**: A 3-bit code that indicates the work mode of NTP. This field can be set to these values:
   * 0: reserved
   * 1: symmetric active
   * 2: symmetric passive
   * 3: client
   * 4: server
   * 5: broadcast or multicast
   * 6: NTP control message
   * 7: reserved for private use

**NTP_TIMESTAMP_DELTA** is a constant used to convert Network Time Protocol (NTP) time to Unix time. NTP timestamps are measured in seconds since 00:00 (midnight) on January 1, 1900, while Unix time (also known as POSIX time or Epoch time) is measured in seconds since 00:00 (midnight) on January 1, 1970 (the Unix epoch).

Source code: [ntp_clock_synchronization.c](ntp_clock_synchronization.c)