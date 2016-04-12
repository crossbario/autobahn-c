# AutobahnC

## Motivation

So, why another Autobahn? Why yet another WAMP client library?

In one word: because IoT.

Because we want to allow small, embedded devices to be first-class WAMP citizens.

And without requiring bridging from some other protocol.

For example, using AutobahnCpp and C++, it is possible to create an (essentially) completely statically linked, small executable.

However, the fact that AutobahnCpp uses a couple of C++ features only available in C++ 11 and later (better C++ 14), and the fact that it deeply depends on Boost (in particular Boost ASIO) can make it hard when using C/C++ toolchains for embedded devices, which often are not as current as your modern GCC or Clang. Even Windows requires a very recent incarnation of VSS. Modern C++ is a weapon, but its also a biest.

Then Boost, and ASIO in particular is written against Posix/Win32 APIs. Of course, no issue when on a full blown *nix, *BSD or Windows system. But it is a problem on smallish embedded devices that can't run such OSs.

Then, while AutobahnCpp now implements multiple WAMP transports, namely WebSocket and RawSocket, all these run over TCP (or in general, a reliable stream transport .. besides TCP, another one would be Unix domain sockets).

However, TCP (and TLS) require non-trivial and complex implementations. Eg there are "Wifi/TCP on a chip" solutions, but I have yet to see one that provides a *robust, full and interoperable* implementation. For example, the TI CC chips (eg used in Tessel 1) or ESP86xx suck big time. The Wifi is flaky. The TCP is. Not to speak of TLS. Not recommended.

Of course, when you can run a full Linux, all of above are non-issues. Linux has (obviously) capable and robust TCP, and GCC and Clang, and Open/LibreSSL. etc etc

But you can't get Linux onto a 64kB RAM 32 bit MMU-less MCU. No way. You can strip it down to maybe 1MB RAM. But not much below. And that already require screwing the GNU glibc and moving to a "non-standard" C run-time - and that means pain, pain, pain already anyway.

> Sidenote: There is a modern development called "Rump kernels". The *BSDs are again innovating here. But this is more a research thing right now, and more directed towards server loads, not embedded. And I doubt it can run without a MMU and hardware assisted virtual memory.

So, how do we get WAMP onto say an ARM Cortex M3 with 64kB RAM, but no MMU?


## Requirements

32 bit MCU (no MMU), at least 64kB RAM (eg ARM Cortex M devices)
RIOT OS
6LoWPAN/UDP WAMP transport
CBOR serialization support

DTLS

WAMP-cryptosign
WAMP-cryptobox


1. AutobahnC must is implemented in ANSI/ISO C89.
2.



## License and Copyrights

**The license for AutobahnC will be MIT.**

This is a liberal, non-copyleft license that allows use in both commercial, closed-source applications and open-source projects.

The MIT license - different from Apache 2.0 - is also compatible with GPL v2.

We also use MIT for AutobahnPython and AutobahnJS. AutobahnCpp uses the Boost license, mainly because be deeply depend on Boost anyway, and users then don't have to deal with yet another one. AutobahnAndroid (after the revamp that is upcoming) will also move to MIT.

**The copyright notice will read: `Copyright (c) Tavendo GmbH and contributors.`**

For various reasons, I think this is a sane, precise and fair one.

We (Tavendo) will thus share the copyright, and there is no way we would be able to take away anything from the community or contributors.

Listing each contributor in copyright notice is impractical (witness the discussion we had in AutobahnCpp). On the other hand, giving proper credits and visibility to contributors is important. We'll make sure that happens: in announcements ("X did awesome work") and/or CHANGELOG ("fix: ZZ - Thanks to X for this!"). Prominently placing us (Tavendo) in the copyright notice on the other hand is fair IMO, because we started all this.

This is our policy (for all Autobahns), we do make this fully transparent in the wild open, and I think we (as a company) do already have a track record of being a good open-source fellow;) Not to speak of the significant amounts of money we've invested sponsoring all these open-source efforts.

> Note: we'll soonish retire "Tavendo GmbH", and found "Crossbar.io GmbH". The copyright notice then will be changed to: `Copyright (c) Crossbar.io GmbH and contributors.` The new company will be transferred all legal rights from the old one. So we don't need to ask anyone for permission to do the change.


## Dev environment

### Hardware

The dev MCU/SoC/board we'll use in (early) development of AutobahnC is:

* ARM Cortex M4
* Freescale Kinetis KW2x
* [PHYTEC phyWAVE-KW2x](http://www.phytec.de/produkte/internet-of-things/phywave/)


http://www.compex.com.sg/wp-content/uploads/2015/12/WPQ864-v1.7a.pdf
http://www.compex.com.sg/product/wpq864/


The main reasons to use this specific product are:

* the MCU is a state-of-the-art ARM Cortex device
* RIOT *mainline* support for both the MCU/SoC and board (for *all* sensors/actuators)
* PHYTEC seem to be a vivid open-source supporter with close relations to RIOT
* PHYTEC has very good, openly available docs for their products

> I've met the RIOT guys at EmbeddedWorld in Nürnberg/Germany 2016, and they had a booth _sponsored_ by PHYTEC. No sales talking at all. All engineers/developers there. Nice, nice.

An alternative or equivalent would be

* ST Microelectronics STM32F40 (ARM Cortex M4)
* STM32F4discovery

And of course, there are a lot of other M4 SoCs and boards. We do want to be open of course for other vendors/products - so this isn't about pushing for one vendor. But in my experience, its worth settling on one specific device in particular during early development, simply to reduce the number of variables, and don't spend too much time fiddling with stuff instead of writing code.

> Disclosure: We (Tavendo) do NOT (2016/04) have any commercial relationship with Freescale or PHYTEC.

### Software

We'll use GNU Tools for ARM Embedded Processors toolchain, aka **gcc-arm-embedded**.

> We do not use proprietory 3rd party or ARM proprietory closed source tools. None. I don't care about that and would actively oppose anything in that direction. If we get patches to support properietory toolchain, so be it, and we'll merge *if it fits*. But we won't spend time ourself fiddling with these.


## Dev process

Code will be hosted on GitHub in the main repo [https://github.com/crossbario/autobahn-c](https://github.com/crossbario/autobahn-c).

Developers fork that repo, develop on private, short-lived branches and file PRs against the main repo. No direct merges to master on the main repo!

Before merging, at least one other developer should have a look / review the PR.

During early developement, we don't require any specifics regarding the dev branches.

> Whether we require squasing commits before merging and/or rebasing to master we need to decide too.

When AutobahnC has reached a minimal viable / functional state, we'll tighten the process:

1. no change without an issue
2. feature/fix branches refer to an issue
3. only on thing per issue, and hence feature/fix branch (granularity)
4. a proper changelog

Issue are tracked on GitHub. We'll use labels for light-weight organization of issues. Yes, GH issues isn't perfect and limited, but it's super easy, light-weight and integrated with other GH features.


## Dev communication

Discussions about concrete code proposal are encouraged to happen on PRs and/or related issues.

We get the nice GH integrations for free, as well as long-term persistency of all the discussions.

**The Autobahns have a mailing list and an IRC channel as well, but we might consider setting up Gitter (trivial) or Slack (we use that internally at Tavendo), because that has some real pros vs the former.**


## Coding Styleguide

Lets not reinvent a new one, but look for something nice and existing **but well-defined**.

Eg in the Python world, there is PEP8. Its there, hashed out, and many projects use it.

Is there something similar for C? Obviously, but needs discussion / decision.

> I've learned that the hard way (read, I did it wrong;). Personal taste is one thing. NOT having to hash out rules ourself, and then have endless discussions, and the doing it different from the rest of the community IS NOT producing value, but a waste of time.
