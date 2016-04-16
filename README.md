## Milestones

1. Connect two RIOT nodes over bridged TAP devices and talk UDP
2. Connect one RIOT node to a Python UDP node and talk UDP
3. Create a fuzzing UDP bridge that can drop, delay and reorder UDP datagrams


## Resources

* https://github.com/RIOT-OS/RIOT/wiki/Introduction#native-riot---run-riot-on-your-pc
* https://github.com/RIOT-OS/RIOT/wiki/Family:-native
* https://github.com/RIOT-OS/RIOT/wiki/Virtual-riot-network
* https://www.kernel.org/doc/Documentation/networking/tuntap.txt
* http://riot-os.org/files/2015-riotlab-tutorial.pdf


## Prerequisites

The following was tested on Ubuntu 14.04. Install some tools

```console
sudo apt-get install gcc-multilib bridge-utils
```

Clone the RIOT repo:

```console
git clone https://github.com/RIOT-OS/RIOT.git
cd RIOT/examples/posix_sockets
make BOARD=native
```

Create two bridged TAP devices:

```console
cd RIOT
./dist/tools/tapsetup/tapsetup -c 2
```

## Sending over UDP between two RIOT nodes

Build the [UDP example](https://github.com/RIOT-OS/RIOT/tree/master/examples/posix_sockets):

```console
cd RIOT/examples/posix_sockets
make BOARD=native
```

This should produce `./bin/native/posix_sockets.elf`.

In a first terminal, start node 1:

```console
oberstet@thinkpad-t430s:~/scm/3rdparty/RIOT/examples/posix_sockets$ sudo make term
[sudo] password for oberstet:
/home/oberstet/scm/3rdparty/RIOT/examples/posix_sockets/bin/native/posix_sockets.elf tap0
RIOT native interrupts/signals initialized.
LED_RED_OFF
LED_GREEN_ON
RIOT native board initialized.
RIOT native hardware initialization complete.

main(): This is RIOT! (Version: 2016.03-devel-1699-g0aa0-thinkpad-t430s)
RIOT socket example application
All up, running the shell now
> help
help
Command              Description
---------------------------------------
udp                  send data over UDP and listen on UDP ports
reboot               Reboot the node
ps                   Prints information about running threads.
random_init          initializes the PRNG
random_get           returns 32 bit of pseudo randomness
ifconfig             Configure network interfaces
txtsnd               Sends a custom string as is over the link layer
ncache               manage neighbor cache by hand
routers              IPv6 default router list
> ifconfig
ifconfig
Iface  5   HWaddr: ce:c7:93:47:8a:94

           MTU:1500  HL:64
           Source address length: 6
           Link type: wired
           inet6 addr: ff02::1/128  scope: local [multicast]
           inet6 addr: fe80::ccc7:93ff:fe47:8a94/64  scope: local
           inet6 addr: ff02::1:ff47:8a94/128  scope: local [multicast]

> udp
udp
usage: udp [send|server]
> udp server start 9000
udp server start 9000
Success: started UDP server on port 9000
> ps
ps
    pid | name                 | state    Q | pri | stack ( used) | location
      1 | idle                 | pending  Q |  15 |  8192 ( 6240) | 0x8070180
      2 | main                 | running  Q |   7 | 12288 ( 9312) | 0x806d180
      3 | ipv6                 | bl rx    _ |   4 |  8192 ( 6240) | 0x807d3c0
      4 | udp                  | bl rx    _ |   5 |  8192 ( 6240) | 0x8081200
      5 | gnrc_netdev2_tap     | bl rx    _ |   4 |  8192 ( 6240) | 0x807b380
      6 | UDP server           | bl rx    _ |   6 |  8192 ( 6240) | 0x8079200
        | SUM                  |            |     | 53248 (40512)
> Received data: hello, world!
```

In a second terminal start node 2:

```console
oberstet@thinkpad-t430s:~/scm/3rdparty/RIOT/examples/posix_sockets$ sudo PORT=tap1 make term
[sudo] password for oberstet:
/home/oberstet/scm/3rdparty/RIOT/examples/posix_sockets/bin/native/posix_sockets.elf tap1
RIOT native interrupts/signals initialized.
LED_RED_OFF
LED_GREEN_ON
RIOT native board initialized.
RIOT native hardware initialization complete.

main(): This is RIOT! (Version: 2016.03-devel-1699-g0aa0-thinkpad-t430s)
RIOT socket example application
All up, running the shell now
> udp send fe80::ccc7:93ff:fe47:8a94 9000 "hello, world!"
udp send fe80::ccc7:93ff:fe47:8a94 9000 "hello, world!"
Success: send 13 byte to fe80::ccc7:93ff:fe47:8a94:9000
>
```
