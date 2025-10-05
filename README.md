# YESMINER

This is a multi-threaded CPU miner for ***Yescrypt*** and ***Yespower*** algorithms with the aim to mainly support ARMv7 and ARMv8. This is a fork of Kanon's (sugarmaker) fork of solardiz's (Resistance) fork of Pooler's (Litecoin) fork of Jeff Garzik's (Bitcoin) reference cpuminer. It also uses ideas and inspirations from tpruvot's cpuminer-multi and JayDDee's cpuminer-opt.

License:  [GPLv2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html).  See COPYING for details.

Git tree:  https://github.com/sig11b/yesminer

## Changed or newly added features since the previous release:

Version 2.6.2 - TBD

- Colored and more informative output:
  * latency (by Overdrive5)
  * statistics
- Added Yespower variants:
  * Interchained (ITC) (and renamed historic yespowerITC)
  * JagaricoinR (historic)
- Fixed YespowerEQPAY (EQPAY)
- Allow expired SSL certificates and add option --cert-verify

See [NEWS](NEWS) for summaries of older changes.

## Supported algorithms:

- interchained - Interchained
- power2b - MircoBitcoin
- yescrypt - GlobalBoost-Y, Myriad, Unitus
- yescryptR16 - Fennec, GoldCash, BitWeb, Qoge, ELI
- yescryptR32 - DMS, WAVI
- yescryptR8 - BitZeny, Mateable
- yespower - BellCoin, Veco, SwampCoin, SprintPay
- yespowerADVC - AdventureCoin
- yespowerBlake256 - untested (Dogemone has incompatible net protocols)
- yespowerEQPAY - EquityPay
- yespowerLTNCG - CrionicCoin, LTNCG
- yespowerMGPC - MagpieCoin
- yespowerR16 - Yenten
- yespowerSUGAR - SugarChain
- yespowerTIDE - TideCoin
- yespowerURX - UraniumX
### Historic algorithms:
- cpupower - CPUchain (classic only)
- yescryptR24 - JagaricoinR
- yespowerARWN - ArowanaCoin
- yespowerIOTS - IOTS
- yespowerISO - IsotopeC
- yespowerITCOIN - Intercoin
- yespowerLITB - LightBit
- yespowerRES - Resistance

## Basic Unix build instructions:

### Prerequisites:

- openssl
- libcurl (the (open)ssl variant if you have a choice)

### When downloading a release source archive
```
./configure
make
```
This will use `CFLAGS="-Wall -O3 -fomit-frame-pointer -march=native"` or an
equivalent `-march` flag if possible.
To use custom `CFLAGS`, change the `configure` line to `./configure CFLAGS="-CUSTOM_FLAGS"`.
However, if you want to experiment with the flags, make sure to include `-march=native` or a
similar argument to get the best optimization.

### When cloning from github

In addition to the prerequisites listed above, you will also need some autotools like autoconf and automake.
```
autoreconf -i
./configure
make
```

Or you can simply use the shortcut
```
./build.sh
```
See above for the default `CFLAGS` and how to change them.

## Usage instructions:

Run `yesminer --help` to see options or
take a look at [the manual](Manual.md), which is
also included as a man page.

## Authors:

- Jeff Garzik
- ArtForz
- pooler
- Alexander Peslyak (yespower algorithm implementation)
- Kanon
- DLT Collaboration (sse2neon)
- Sig11 (sig11b@github)
