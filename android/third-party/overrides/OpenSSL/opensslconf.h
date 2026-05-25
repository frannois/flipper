/*
 * WARNING: do not edit!
 * Pre-generated for Android by Flipper build (no-asm configuration).
 * Based on OpenSSL 1.1.1w Configure output for android targets.
 */

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef OPENSSL_ALGORITHM_DEFINES
# error OPENSSL_ALGORITHM_DEFINES no longer supported
#endif

/*
 * OpenSSL was configured with the following options:
 */

#ifndef OPENSSL_SYS_LINUX
# define OPENSSL_SYS_LINUX 1
#endif

#ifndef OPENSSL_NO_ASM
# define OPENSSL_NO_ASM
#endif
#ifndef OPENSSL_NO_DYNAMIC_ENGINE
# define OPENSSL_NO_DYNAMIC_ENGINE
#endif
#ifndef OPENSSL_NO_DEVCRYPTOENG
# define OPENSSL_NO_DEVCRYPTOENG
#endif
#ifndef OPENSSL_NO_HW
# define OPENSSL_NO_HW
#endif
#ifndef OPENSSL_NO_MD2
# define OPENSSL_NO_MD2
#endif
#ifndef OPENSSL_NO_RC5
# define OPENSSL_NO_RC5
#endif
#ifndef OPENSSL_NO_EC_NISTP_64_GCC_128
# define OPENSSL_NO_EC_NISTP_64_GCC_128
#endif

#ifndef OPENSSL_THREADS
# define OPENSSL_THREADS
#endif

/* Entropy source for random number generation on Android/Linux */
#ifndef OPENSSL_RAND_SEED_DEVRANDOM
# define OPENSSL_RAND_SEED_DEVRANDOM
#endif

#ifndef OPENSSL_NO_STATIC_ENGINE
# define OPENSSL_NO_STATIC_ENGINE
#endif

#ifndef OPENSSL_FILE
# ifdef OPENSSL_NO_FILENAMES
#  define OPENSSL_FILE ""
#  define OPENSSL_LINE 0
# else
#  define OPENSSL_FILE __FILE__
#  define OPENSSL_LINE __LINE__
# endif
#endif

/*
 * Architecture-specific configuration.
 * Detect 32-bit vs 64-bit at compile time using preprocessor.
 */
#if defined(__LP64__) || defined(_LP64)
# define SIXTY_FOUR_BIT_LONG
#else
# define BN_LLONG
# define THIRTY_TWO_BIT
#endif

#define RC4_INT unsigned int

#define OPENSSL_UNISTD <unistd.h>

#define OPENSSLDIR "/etc/ssl"
#define ENGINESDIR "/dev/null"

/*
 * Deprecation macros. Since we want all APIs available, all deprecated
 * functions are still declared.
 */
# define DEPRECATEDIN_1_2_0(f)   f;
# define DEPRECATEDIN_1_1_0(f)   f;
# define DEPRECATEDIN_1_0_0(f)   f;
# define DEPRECATEDIN_0_9_8(f)   f;

#ifdef  __cplusplus
}
#endif

#include <openssl/opensslv.h>
