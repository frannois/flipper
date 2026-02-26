# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.
#
# CMake build for OpenSSL 1.1.1w (static libraries)
# Built with OPENSSL_NO_ASM for CMake compatibility.

cmake_minimum_required(VERSION 3.6.0)
project(openssl C)

set(OPENSSL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/openssl-1.1.1w)

# Include directories
# Order matters: source-local includes are searched first
include_directories(
    ${OPENSSL_DIR}
    ${OPENSSL_DIR}/include
    ${OPENSSL_DIR}/crypto/include
    ${OPENSSL_DIR}/crypto/modes
    ${OPENSSL_DIR}/crypto/ec/curve448
)

# curve448 arch include (OpenSSL 1.1.1w only ships arch_32)
include_directories(${OPENSSL_DIR}/crypto/ec/curve448/arch_32)

# Compile definitions
add_definitions(
    -DOPENSSL_NO_ASM
    -DOPENSSL_NO_DYNAMIC_ENGINE
    -DOPENSSL_NO_DEVCRYPTOENG
    -DOPENSSL_NO_HW
    -DOPENSSL_NO_STATIC_ENGINE
    -DOPENSSL_NO_CRYPTO_MDEBUG_BACKTRACE
    -DOPENSSLDIR="/etc/ssl"
    -DENGINESDIR="/dev/null"
    -DOPENSSL_THREADS
    -D_REENTRANT
    -DNDEBUG
)

add_compile_options(
    -Wno-unused-parameter
    -Wno-missing-field-initializers
    -Wno-sign-compare
)

# ---------------------------------------------------------------------------
# libcrypto
# ---------------------------------------------------------------------------

file(GLOB_RECURSE CRYPTO_SRC "${OPENSSL_DIR}/crypto/*.c")

# Exclude platform-specific files
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/LPdir_.*\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/rand_vms\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/rand_win\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/dso_vms\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/dso_win32\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/dso_beos\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/threads_win\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/threads_none\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/eng_devcrypto\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/aes_x86core\\.c$")

# Exclude non-target CPU capability detection
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/s390xcap\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/ppccap\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/sparcv9cap\\.c$")

# armcap.c is ARM-specific; exclude on non-ARM targets
if(NOT CMAKE_ANDROID_ARCH_ABI MATCHES "^arm")
    list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/armcap\\.c$")
endif()

# Exclude files for disabled features (OPENSSL_NO_RC5, OPENSSL_NO_MD2)
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/rc5/.*\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/md2/.*\\.c$")

# Exclude platform-specific optimized implementations
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/poly1305_ieee754\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/poly1305_base2_44\\.c$")

# Exclude EGD (Entropy Gathering Daemon) - not available on Android
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/rand_egd\\.c$")

# Exclude SCTP support (netinet/sctp.h not available on Android)
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/bss_dgram\\.c$")

# Exclude x86_64 specific assembly/code
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/rsaz_exp\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/x86_64-gcc\\.c$")

# Exclude EBCDIC (IBM mainframe) support
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/ebcdic\\.c$")

# Exclude assembly-optimized files (not compatible with OPENSSL_NO_ASM)
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/ecp_nistz256_table\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/ecp_nistz256\\.c$")

# Exclude 64-bit GCC 128-bit int optimized NIST P-curve implementations
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/ecp_nistp224\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/ecp_nistp256\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/ecp_nistp521\\.c$")
list(FILTER CRYPTO_SRC EXCLUDE REGEX ".*/ecp_nistputil\\.c$")

# Include arch_32 curve448 field implementation (only arch available in 1.1.1w)

add_library(crypto STATIC ${CRYPTO_SRC})

target_include_directories(crypto PUBLIC
    ${OPENSSL_DIR}/include
    ${OPENSSL_DIR}/crypto/include
)

# ---------------------------------------------------------------------------
# libssl
# ---------------------------------------------------------------------------

file(GLOB SSL_SRC
    "${OPENSSL_DIR}/ssl/*.c"
    "${OPENSSL_DIR}/ssl/record/*.c"
    "${OPENSSL_DIR}/ssl/statem/*.c"
)

add_library(ssl STATIC ${SSL_SRC})

target_include_directories(ssl PUBLIC
    ${OPENSSL_DIR}/include
)

target_link_libraries(ssl crypto)
