#pragma once

#if defined(_MSC_VER)
// Provide GCC attribute / asm compatibility for MSVC IntelliSense parsing.
#ifndef ATTRIBUTE_PACKED
#define ATTRIBUTE_PACKED
#endif

#ifndef __attribute__
#define __attribute__(x)
#endif

#ifndef __asm__
#define __asm__(x)
#endif

#ifndef MK_INLINE
#define MK_INLINE static __inline
#endif

#endif
