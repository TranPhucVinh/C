# Fundamental concept

For network devices like router, the link layer is implemented in **the router’s line card**. For the most part, the link layer is implemented in a **network adapter**, also sometimes known as a **network interface card** (NIC). At the heart of the **network adapter** is the **link-layer controller**, usually a **single, special-purpose chip** that implements many of the link-layer services (**framing**, **link access**, **error detection**, and so on). Thus, much of a link-layer controller’s functionality is implemented in hardware.

While most of the link layer is implemented in hardware, **part of the link layer** is implemented in **software** that runs on the host’s CPU. The **software** components of the link layer implement **higher-level link-layer** functionality such as **assembling link-layer addressing information** and **activating the controller hardware**. On the receiving side, **link-layer software** responds to **controller interrupts** (e.g., due to the receipt of one or more frames), **handling error conditions** and **passing a datagram up to the network layer**. Thus, the data-link layer is **a combination of hardware and software**, the place in the protocol stack where software meets hardware.

# Handling error conditions

* [CRC](CRC.md)
