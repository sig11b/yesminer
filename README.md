# YESMINER

This is a multi-threaded CPU miner for ***Yescrypt*** and ***Yespower*** algorithms with the aim to mainly support ARMv7 and ARMv8. This is a fork Kanon's fork of solardiz's (Resistance) fork of pooler's (Litecoin) fork of Jeff Garzik's (Bitcoin) reference cpuminer.

License:  [GPLv2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html).  See COPYING for details.

Git tree:  https://github.com/sig11b/yesminer

### Supported algorithms:
```
  cpupower         CPUchain
  power2b          MircoBitcoin
  yescrypt         GlobalBost-Y, Myrias, Unitus
  yescryptR8       Mateable, BitZeny
  yescryptR16      Fennec, GoldCash, ELI
  yescryptR32      DMS, WAVI
  yespower         BellCoin, Veco, SwampCoin
  yespowerADVC     Adventure Coin
  yespowerEQPAY    EQPAY
  yespowerLTNCG    CrionicCoin, LTNCG
  yespowerMGPC     MagpieCoin
  yespowerR16      Yenten
  yespowerSUGAR    SugarChain
  yespowerTIDE     TideCOin
  yespowerURX      UraniumX
Historic algorithms:
  yespowerARWN     ArowanaCoin
  yespowerIOTS     IOTS
  yespowerISO      IsotopeC
  yespowerITC      Intercoin
  yespowerLITB     LightBit
```

### Basic Unix build instructions:
```
./autogen.sh
./configure CFLAGS="-Wall -O2 -fomit-frame-pointer" CXXFLAGS="$CFLAGS -std=gnu++11"
make
```
Or using the shortcut
```
./build.sh
```
See also the [README of the upstream project](README-upstream.md) on which this fork is based on.

### Usage instructions:
Run `yesminer --help` to see options.

### Author
- Jeff Garzik
- Pooler
- Alexander Peslyak
- Kanon
- sig11


