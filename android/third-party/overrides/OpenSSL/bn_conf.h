/*
 * WARNING: do not edit!
 * Pre-generated for Android by Flipper build.
 */

#ifndef HEADER_BN_CONF_H
# define HEADER_BN_CONF_H

#if defined(__LP64__) || defined(_LP64)
# undef BN_LLONG
# define SIXTY_FOUR_BIT_LONG
# undef SIXTY_FOUR_BIT
# undef THIRTY_TWO_BIT
#else
# define BN_LLONG
# undef SIXTY_FOUR_BIT_LONG
# undef SIXTY_FOUR_BIT
# define THIRTY_TWO_BIT
#endif

#endif
