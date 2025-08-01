#ifndef __MINER_H__
#define __MINER_H__

#include "cpuminer-config.h"

#include <stdbool.h>
#include <inttypes.h>
#include <sys/time.h>
#include <pthread.h>
#include <jansson.h>
#include <curl/curl.h>

#ifdef STDC_HEADERS
# include <stdlib.h>
# include <stddef.h>
#else
# ifdef HAVE_STDLIB_H
#  include <stdlib.h>
# endif
#endif
#ifdef HAVE_ALLOCA_H
# include <alloca.h>
#elif !defined alloca
# ifdef __GNUC__
#  define alloca __builtin_alloca
# elif defined _AIX
#  define alloca __alloca
# elif defined _MSC_VER
#  include <malloc.h>
#  define alloca _alloca
# elif !defined HAVE_ALLOCA
#  ifdef  __cplusplus
extern "C"
#  endif
void *alloca (size_t);
# endif
#endif

#ifdef HAVE_SYSLOG_H
#include <syslog.h>
#else
enum {
	LOG_ERR,
	LOG_WARNING,
	LOG_NOTICE,
	LOG_INFO,
	LOG_DEBUG,
};
#endif

#undef unlikely
#undef likely
#if defined(__GNUC__) && (__GNUC__ > 2) && defined(__OPTIMIZE__)
#define unlikely(expr) (__builtin_expect(!!(expr), 0))
#define likely(expr) (__builtin_expect(!!(expr), 1))
#else
#define unlikely(expr) (expr)
#define likely(expr) (expr)
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

#if ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
#define WANT_BUILTIN_BSWAP
#else
#define bswap_32(x) ((((x) << 24) & 0xff000000u) | (((x) << 8) & 0x00ff0000u) \
                   | (((x) >> 8) & 0x0000ff00u) | (((x) >> 24) & 0x000000ffu))
#endif

static inline uint32_t swab32(uint32_t v)
{
#ifdef WANT_BUILTIN_BSWAP
	return __builtin_bswap32(v);
#else
	return bswap_32(v);
#endif
}

#ifdef HAVE_SYS_ENDIAN_H
#include <sys/endian.h>
#endif

#if !HAVE_DECL_BE32DEC
static inline uint32_t be32dec(const void *pp)
{
	const uint8_t *p = (uint8_t const *)pp;
	return ((uint32_t)(p[3]) + ((uint32_t)(p[2]) << 8) +
	    ((uint32_t)(p[1]) << 16) + ((uint32_t)(p[0]) << 24));
}
#endif

#if !HAVE_DECL_LE32DEC
static inline uint32_t le32dec(const void *pp)
{
	const uint8_t *p = (uint8_t const *)pp;
	return ((uint32_t)(p[0]) + ((uint32_t)(p[1]) << 8) +
	    ((uint32_t)(p[2]) << 16) + ((uint32_t)(p[3]) << 24));
}
#endif

#if !HAVE_DECL_BE32ENC
static inline void be32enc(void *pp, uint32_t x)
{
	uint8_t *p = (uint8_t *)pp;
	p[3] = x & 0xff;
	p[2] = (x >> 8) & 0xff;
	p[1] = (x >> 16) & 0xff;
	p[0] = (x >> 24) & 0xff;
}
#endif

#if !HAVE_DECL_LE32ENC
static inline void le32enc(void *pp, uint32_t x)
{
	uint8_t *p = (uint8_t *)pp;
	p[0] = x & 0xff;
	p[1] = (x >> 8) & 0xff;
	p[2] = (x >> 16) & 0xff;
	p[3] = (x >> 24) & 0xff;
}
#endif

#if JANSSON_MAJOR_VERSION >= 2
#define JSON_LOADS(str, err_ptr) json_loads(str, 0, err_ptr)
#define JSON_LOAD_FILE(path, err_ptr) json_load_file(path, 0, err_ptr)
#else
#define JSON_LOADS(str, err_ptr) json_loads(str, err_ptr)
#define JSON_LOAD_FILE(path, err_ptr) json_load_file(path, err_ptr)
#endif

#define USER_AGENT PACKAGE_NAME "/" PACKAGE_VERSION

void sha256_init(uint32_t *state);
void sha256_transform(uint32_t *state, const uint32_t *block, int swap);
void sha256d(unsigned char *hash, const unsigned char *data, int len);

extern bool setup_variant();

extern int scanhash_yespower(int thr_id, uint32_t *pdata,
	const uint32_t *ptarget,
	uint32_t max_nonce, unsigned long *hashes_done);

struct thr_info {
	int		id;
	pthread_t	pth;
	struct thread_q	*q;
};

struct work_restart {
	volatile unsigned long	restart;
	char			padding[128 - sizeof(unsigned long)];
};

enum algos {
	ALGO_YESPOWER_CPU,
	ALGO_YESPOWER_POWER2B,
	ALGO_YESCRYPT,
	ALGO_YESCRYPT_R8,
//	ALGO_YESCRYPT_R8G,    // TODO: implement Koto
	ALGO_YESCRYPT_R16,
	ALGO_YESCRYPT_R32,
	ALGO_YESPOWER,
	ALGO_YESPOWER_ADVC,
	ALGO_YESPOWER_BLAKE256, // For Dogemone, probably already dead, uses Cryptonight stratum
	ALGO_YESPOWER_EQPAY,
	ALGO_YESPOWER_LTNCG,
	ALGO_YESPOWER_MGPC,
	ALGO_YESPOWER_R16,
	ALGO_YESPOWER_SUGAR,
	ALGO_YESPOWER_TIDE,
	ALGO_YESPOWER_URX,
	ALGO_NONE,              // ALGO_NONE separates the historic algos from the ones still in use
	ALGO_YESPOWER_ARWN,
	ALGO_YESPOWER_IOTS,
	ALGO_YESPOWER_ISO,
	ALGO_YESPOWER_ITC,
	ALGO_YESPOWER_LITB,
	ALGO_YESPOWER_RES,
};

static const char *algo_names[] = {
	[ALGO_YESCRYPT]		= "yescrypt         GlobalBost-Y, Myriad, Unitus",
	[ALGO_YESCRYPT_R8]	= "yescryptR8       BitZeny, Mateable",
	[ALGO_YESCRYPT_R16]	= "yescryptR16      Fennec, GoldCash, ELI",
	[ALGO_YESCRYPT_R32]	= "yescryptR32      DMS, WAVI",
	[ALGO_YESPOWER]		= "yespower         BellCoin, Veco, SwampCoin",
	[ALGO_YESPOWER_ADVC]	= "yespowerADVC     AdventureCoin",
	[ALGO_YESPOWER_CPU]	= "cpupower         CPUchain",
	[ALGO_YESPOWER_BLAKE256]= "yespowerBlake256 untested (Dogemone has incompatible net protocols)",
	[ALGO_YESPOWER_EQPAY]	= "yespowerEQPAY    EQPAY",
	[ALGO_YESPOWER_LTNCG]	= "yespowerLTNCG    CrionicCoin, LTNCG",
	[ALGO_YESPOWER_MGPC]	= "yespowerMGPC     MagpieCoin",
	[ALGO_YESPOWER_POWER2B]	= "power2b          MircoBitcoin",
	[ALGO_YESPOWER_R16]	= "yespowerR16      Yenten",
	[ALGO_YESPOWER_SUGAR]	= "yespowerSUGAR    SugarChain",
	[ALGO_YESPOWER_TIDE]	= "yespowerTIDE     TideCoin",
	[ALGO_YESPOWER_URX]	= "yespowerURX      UraniumX",
	[ALGO_NONE]		= "\0",
	[ALGO_YESPOWER_ARWN]	= "yespowerARWN     ArowanaCoin",
	[ALGO_YESPOWER_IOTS]	= "yespowerIOTS     IOTS",
	[ALGO_YESPOWER_ISO]	= "yespowerISO      IsotopeC",
	[ALGO_YESPOWER_ITC]	= "yespowerITC      Intercoin",
	[ALGO_YESPOWER_LITB]	= "yespowerLITB     LightBit",
	[ALGO_YESPOWER_RES]	= "yespowerRES      Resistance",
};

extern bool opt_debug;
extern bool opt_protocol;
extern bool opt_redirect;
extern int opt_timeout;
extern bool want_longpoll;
extern bool have_longpoll;
extern bool have_gbt;
extern bool allow_getwork;
extern bool want_stratum;
extern bool have_stratum;
extern enum algos opt_algo;
extern char *opt_cert;
extern char *opt_proxy;
extern long opt_proxy_type;
extern bool use_syslog;
extern pthread_mutex_t applog_lock;
extern struct thr_info *thr_info;
extern int longpoll_thr_id;
extern int stratum_thr_id;
extern struct work_restart *work_restart;

#define JSON_RPC_LONGPOLL	(1 << 0)
#define JSON_RPC_QUIET_404	(1 << 1)

// a very basic set of colors should be more than enough
#define CL_N    "\x1B[0m"
#define CL_RED  "\x1B[31m"
#define CL_GRN  "\x1B[32m"
#define CL_YLW  "\x1B[33m"
#define CL_BLU  "\x1B[34m"
#define CL_MAG  "\x1B[35m"
#define CL_CYN  "\x1B[36m"

extern void applog(int prio, const char *fmt, ...);
extern json_t *json_rpc_call(CURL *curl, const char *url, const char *userpass,
	const char *rpc_req, int *curl_err, int flags);
void memrev(unsigned char *p, size_t len);
extern void bin2hex(char *s, const unsigned char *p, size_t len);
extern char *abin2hex(const unsigned char *p, size_t len);
extern bool hex2bin(unsigned char *p, const char *hexstr, size_t len);
extern int varint_encode(unsigned char *p, uint64_t n);
extern size_t address_to_script(unsigned char *out, size_t outsz, const char *addr);
extern int timeval_subtract(struct timeval *result, struct timeval *x,
	struct timeval *y);
extern bool fulltest(const uint32_t *hash, const uint32_t *target);
extern void diff_to_target(uint32_t *target, double diff);

struct stratum_job {
	char *job_id;
	unsigned char prevhash[32];
	size_t coinbase_size;
	unsigned char *coinbase;
	unsigned char *xnonce2;
	int merkle_count;
	unsigned char **merkle;
	unsigned char version[4];
	unsigned char nbits[4];
	unsigned char ntime[4];
	bool clean;
	double diff;
};

struct stratum_ctx {
	char *url;

	CURL *curl;
	char *curl_url;
	char curl_err_str[CURL_ERROR_SIZE];
	curl_socket_t sock;
	size_t sockbuf_size;
	char *sockbuf;
	pthread_mutex_t sock_lock;

	double next_diff;

	char *session_id;
	size_t xnonce1_size;
	unsigned char *xnonce1;
	size_t xnonce2_size;
	struct stratum_job job;
	pthread_mutex_t work_lock;
};

bool stratum_socket_full(struct stratum_ctx *sctx, int timeout);
bool stratum_send_line(struct stratum_ctx *sctx, char *s);
char *stratum_recv_line(struct stratum_ctx *sctx);
bool stratum_connect(struct stratum_ctx *sctx, const char *url);
void stratum_disconnect(struct stratum_ctx *sctx);
bool stratum_subscribe(struct stratum_ctx *sctx);
bool stratum_authorize(struct stratum_ctx *sctx, const char *user, const char *pass);
bool stratum_handle_method(struct stratum_ctx *sctx, const char *s);

struct thread_q;

extern struct thread_q *tq_new(void);
extern void tq_free(struct thread_q *tq);
extern bool tq_push(struct thread_q *tq, void *data);
extern void *tq_pop(struct thread_q *tq, const struct timespec *abstime);
extern void tq_freeze(struct thread_q *tq);
extern void tq_thaw(struct thread_q *tq);

#endif /* __MINER_H__ */
