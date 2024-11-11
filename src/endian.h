#ifndef ENDIAN_H
#define ENDIAN_H

// https://github.com/mikepb/endian.h/issues/4

#if defined(HAVE_ENDIAN_H) || \
    defined(__linux__) || \
    defined(__GNU__) || \
    defined(__OpenBSD__) || \
    defined(__CYGWIN__) || \
    defined(__MSYS__) || \
    defined(__HAIKU__) || \
    defined(__illumos__) || \
    defined(__sun) || \
    defined(sun)

# include <endian.h>

#elif defined(HAVE_SYS_ENDIAN_H) || \
    defined(__FreeBSD__) || \
    defined(__NetBSD__) || \
    defined(__DragonFly__)

# include <sys/endian.h>

#elif defined(__APPLE__)

# include <libkern/OSByteOrder.h>

# define htobe16(x) OSSwapHostToBigInt16(x)
# define htole16(x) OSSwapHostToLittleInt16(x)
# define be16toh(x) OSSwapBigToHostInt16(x)
# define le16toh(x) OSSwapLittleToHostInt16(x)

# define htobe32(x) OSSwapHostToBigInt32(x)
# define htole32(x) OSSwapHostToLittleInt32(x)
# define be32toh(x) OSSwapBigToHostInt32(x)
# define le32toh(x) OSSwapLittleToHostInt32(x)

# define htobe64(x) OSSwapHostToBigInt64(x)
# define htole64(x) OSSwapHostToLittleInt64(x)
# define be64toh(x) OSSwapBigToHostInt64(x)
# define le64toh(x) OSSwapLittleToHostInt64(x)

#elif defined(_WIN32)

/* byte swap functions */
# if defined(_MSC_VER) && !defined(__clang__)
#   include <stdlib.h>
#   define B_SWAP_16(x) _byteswap_ushort(x)
#   define B_SWAP_32(x) _byteswap_ulong(x)
#   define B_SWAP_64(x) _byteswap_uint64(x)
# else
#   define B_SWAP_16(x) __builtin_bswap16(x)
#   define B_SWAP_32(x) __builtin_bswap32(x)
#   define B_SWAP_64(x) __builtin_bswap64(x)
# endif

/* defines BIG_ENDIAN, LITTLE_ENDIAN and BYTE_ORDER */
# if defined(__MINGW32__) || defined(HAVE_SYS_PARAM_H)
#   include <sys/param.h>
# endif

# ifndef BIG_ENDIAN
#   ifdef __BIG_ENDIAN
#     define BIG_ENDIAN __BIG_ENDIAN
#   elif defined(__ORDER_BIG_ENDIAN__)
#     define BIG_ENDIAN __ORDER_BIG_ENDIAN__
#   else
#     define BIG_ENDIAN 4321
#   endif
# endif
# ifndef LITTLE_ENDIAN
#   ifdef __LITTLE_ENDIAN
#     define LITTLE_ENDIAN __LITTLE_ENDIAN
#   elif defined(__ORDER_LITTLE_ENDIAN__)
#     define LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
#   else
#     define LITTLE_ENDIAN 1234
#   endif
# endif
# ifndef BYTE_ORDER
#   ifdef __BYTE_ORDER
#     define BYTE_ORDER __BYTE_ORDER
#   elif defined(__BYTE_ORDER__)
#     define BYTE_ORDER __BYTE_ORDER__
#   else
      /* assume LE on Windows if nothing was defined */
#     define BYTE_ORDER LITTLE_ENDIAN
#   endif
# endif

# if BYTE_ORDER == LITTLE_ENDIAN

#   define htobe16(x) B_SWAP_16(x)
#   define htole16(x) (x)
#   define be16toh(x) B_SWAP_16(x)
#   define le16toh(x) (x)

#   define htobe32(x) B_SWAP_32(x)
#   define htole32(x) (x)
#   define be32toh(x) B_SWAP_32(x)
#   define le32toh(x) (x)

#   define htobe64(x) B_SWAP_64(x)
#   define htole64(x) (x)
#   define be64toh(x) B_SWAP_64(x)
#   define le64toh(x) (x)

# elif BYTE_ORDER == BIG_ENDIAN

#   define htobe16(x) (x)
#   define htole16(x) B_SWAP_16(x)
#   define be16toh(x) (x)
#   define le16toh(x) B_SWAP_16(x)

#   define htobe32(x) (x)
#   define htole32(x) B_SWAP_32(x)
#   define be32toh(x) (x)
#   define le32toh(x) B_SWAP_32(x)

#   define htobe64(x) (x)
#   define htole64(x) B_SWAP_64(x)
#   define be64toh(x) (x)
#   define le64toh(x) B_SWAP_64(x)

# else

#   error byte order not supported

# endif

#endif

#endif /* ENDIAN_H */