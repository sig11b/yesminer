# YESMINER(1)

## NAME

yesminer - CPU miner for Yescrypt and Yespower cryptocurrencies 

## SYNOPSIS

**yesminer** [_OPTION_]... 

## DESCRIPTION

**yesminer** is a multi-threaded CPU miner for Yescrypt and Yespower cryptocurrencies. It supports the getwork and getblocktemplate (BIP 22) methods, as well as the Stratum mining protocol. 

In its normal mode of operation, **yesminer** connects to a mining server (specified with the **-o** option), receives work from it and starts hashing. As soon as a solution is found, it is submitted to the same mining server, which can accept or reject it. When using getwork or getblocktemplate, **yesminer** can take advantage of long polling, if the server supports it; in any case, fresh work is fetched as needed. When using the Stratum protocol this is not possible, and the server is responsible for sending fresh work at least every minute; if it fails to do so, **yesminer** may drop the connection and try reconnecting again. 

By default, **yesminer** writes all its messages to standard error. On systems that have a syslog, the **--syslog** option can be used to write to it instead. 

On start, the nice value of all miner threads is set to 19. On Linux, the scheduling policy is also changed to SCHED\_IDLE, or to SCHED\_BATCH if that fails. On multiprocessor systems, **yesminer** automatically sets the CPU affinity of miner threads if the number of threads is a multiple of the number of processors. 

## OPTIONS

* **-a**, **--algo**=_ALGORITHM_ 

 Set the hashing algorithm to use. ALGORITHM is case insensitive. Possible values (using arbitrary capitalizations as examples) are: 
```

cpupower         CPUchain
power2b          MircoBitcoin
yescrypt         GlobalBost-Y, Myriad, Unitus
yescryptR16      Fennec, GoldCash, ELI
yescryptR32      DMS, WAVI
yescryptR8       BitZeny, Mateable
yespower         BellCoin, Veco, SwampCoin
yespowerADVC     AdventureCoin
yespowerBlake256 untested (Dogemone has incompatible net protocols)
yespowerEQPAY    EQPAY
yespowerLTNCG    CrionicCoin, LTNCG
yespowerMGPC     MagpieCoin
yespowerR16      Yenten
yespowerSUGAR    SugarChain
yespowerTIDE     TideCoin
yespowerURX      UraniumX

Historic algorithms:

yespowerARWN     ArowanaCoin
yespowerIOTS     IOTS
yespowerISO      IsotopeC
yespowerITC      Intercoin
yespowerLITB     LightBit
yespowerRES      Resistance

```

* **--benchmark** 

 Run in offline benchmark mode. 
* **-B**, **--background** 

 Run in the background as a daemon. 
* **--cert**=_FILE_ 

 Set an SSL certificate to use with the mining server. Only supported when using the HTTPS protocol. 
* **--coinbase-addr**=_ADDRESS_ 

 Set a payout address for solo mining. This is only used in getblocktemplate mode, and only if the server does not provide a coinbase transaction. It can be either a base-58 address, or a bech32 address (BIP 173). 
* **--coinbase-sig**=_TEXT_ 

 Set a string to be included in the coinbase (if allowed by the server). This is only used in getblocktemplate mode. 
* **-c**, **--config**=_FILE_ 

 Load options from a configuration file. _FILE_ must contain a JSON object mapping long options to their arguments (as strings), or to **true** if no argument is required. Sample configuration file: 
```
	{
		"algo": "yespowerR16",
		"url": "stratum+tcp://pool.example.com:3333",
		"userpass": "foo:bar",
		"retry-pause": "10",
		"quiet": true
	}
```

* **-D**, **--debug** 

 Enable debug output. 
* **-h**, **--help** 

 Print a help message and exit. 
* **--no-gbt** 

 Do not use the getblocktemplate RPC method. 
* **--no-getwork** 

 Do not use the getwork RPC method. 
* **--no-longpoll** 

 Do not use long polling. 
* **--no-redirect** 

 Ignore requests from the server to switch to a different URL. 
* **--no-stratum** 

 Do not switch to Stratum, even if the server advertises support for it. 
* **-o**, **--url**=[_SCHEME_://][_USERNAME_[:_PASSWORD_]@]_HOST_:_PORT_[/_PATH_] 

 Set the URL of the mining server to connect to. Supported schemes are **http**, **https**, **stratum+tcp** and **stratum+tcps**. If no scheme is specified, http is assumed. Specifying a _PATH_ is only supported for HTTP and HTTPS. Specifying credentials has the same effect as using the **-O** option. By default, on HTTP and HTTPS, the miner tries to use the getblocktemplate RPC method, and falls back to using getwork if getblocktemplate is unavailable. This behavior can be modified by using the **--no-gbt** and **--no-getwork** options. 
* **-O**, **--userpass**=_USERNAME_:_PASSWORD_ 

 Set the credentials to use for connecting to the mining server. Any value previously set with **-u** or **-p** is discarded. 
* **-p**, **--pass**=_PASSWORD_ 

 Set the password to use for connecting to the mining server. Any password previously set with **-O** is discarded. 
* **-P**, **--protocol-dump** 

 Enable output of all protocol-level activities. 
* **-q**, **--quiet** 

 Disable per-thread hashmeter output. 
* **-r**, **--retries**=_N_ 

 Set the maximum number of times to retry if a network call fails. If not specified, the miner will retry indefinitely. 
* **-R**, **--retry-pause**=_SECONDS_ 

 Set how long to wait between retries. Default is 30 seconds. 
* **-s**, **--scantime**=_SECONDS_ 

 Set an upper bound on the time the miner can go without fetching fresh work. This setting has no effect in Stratum mode or when long polling is activated. Default is 5 seconds. 
* **-S**, **--syslog** 

 Log to the syslog facility instead of standard error. 
* **-t**, **--threads**=_N_ 

 Set the number of miner threads. If not specified, the miner will try to detect the number of available processors and use that. 
* **-T**, **--timeout**=_SECONDS_ 

 Set a timeout for long polling. 
* **-u**, **--user**=_USERNAME_ 

 Set the username to use for connecting to the mining server. Any username previously set with **-O** is discarded. 
* **-V**, **--version** 

 Display version information and quit. 
* **-x**, **--proxy**=[_SCHEME_://][_USERNAME_:_PASSWORD_@]_HOST_:_PORT_ 

 Connect to the mining server through a proxy. Supported schemes are: **http**, **socks4**, **socks5**. Since libcurl 7.18.0, the following are also supported: **socks4a**, **socks5h** (SOCKS5 with remote name resolving). If no scheme is specified, the proxy is treated as an HTTP proxy. 

## EXAMPLES

To connect to a SugarChain mining pool that provides a Stratum server at example.com on port 3333, authenticating as worker "foo" with password "bar": 

```

yesminer -a yespowerSugar -u foo -p bar -o stratum+tcp://example.com:3333

```

To mine to a local testnet instance of a yespower currency running on port 4422, authenticating with username "rpcusr" and password "rpcpass": 

```

yesminer -a yespower -O rpcusr:rpcpass -o http://127.0.0.1:4422 --coinbase-addr=abcdefghijklmnopqrstuvwxyz123456789

```

To connect to a P2Pool node of a yescryptR16 currency running on my.server on port 9327, mining in the background and having output sent to the syslog facility, omitting the per-thread hashmeter output: 

```

yesminer -a yescryptr16 -BSq -o http://my.server:9327

```

## ENVIRONMENT

The following environment variables can be specified in lower case or upper case; the lower-case version has precedence. **http\_proxy** is an exception as it is only available in lower case. 

* **http\_proxy** [_SCHEME_://]_HOST_:_PORT_ 

 Sets the proxy server to use for HTTP. 
* **HTTPS\_PROXY** [_SCHEME_://]_HOST_:_PORT_ 

 Sets the proxy server to use for HTTPS. 
* **ALL\_PROXY** [_SCHEME_://]_HOST_:_PORT_ 

 Sets the proxy server to use if no protocol-specific proxy is set. 

Using an environment variable to set the proxy has the same effect as using the **-x** option. 

## AUTHOR

This variant is maintained by sig11b@github. Most of the code in the current version of yesminer is based on sugarmaker by Kanon, which, in turn, is based on cpuminer by Pooler. Most major contributors are: Jeff Garzik, ArtForz, pooler, Alexander Peslyak (yespower algorithm implementation), Kanon, DLT Collaboration (sse2neon), sig11b@github 