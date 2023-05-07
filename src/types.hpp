#ifndef CSP_TYPES_HPP_INCLUDED_
#define CSP_TYPES_HPP_INCLUDED_ 1
#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <SDL_rect.h>

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;

using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;

using f32 = float;
using f64 = double;

using String = std::string;

template<typename Type>
using Vector = std::vector<Type>;

struct Rect {
	u16 x, y, w, h;

	Rect& operator = (const Rect& rhs);
	bool operator == (const Rect& rhs) const;
	bool operator != (const Rect& rhs) const;

	explicit operator SDL_Rect() const;
};

struct Pixel {
#if TARGET_IS_BIGENDIAN == 0
	u8 r, g, b, a;
#else
	u8 a, b, g, r;
#endif

	Pixel& operator = (const Pixel& rhs);
	bool operator == (const Pixel& rhs) const;
	bool operator != (const Pixel& rhs) const;
	explicit operator u8*();
};

#endif // CSP_TYPES_HPP_INCLUDED_
