
#ifndef BOS_SCREEN_H_
#define BOS_SCREEN_H_

#include "types.h"
#include "writeable.h"

namespace basilisk {

class Screen : public Writeable {
public:
	virtual ~Screen() {}

	class Color {
	public:
		// color enumeration
		enum {
			kBlack = 0,
			kBlue,
			kGreen,
			kCyan,
			kRed,
			kMagenta,
			kBrown,
			kLightGrey,
			kDarkGrey,
			kLightBlue,
			kLightGreen,
			kLightCyan,
			kLightRed,
			kLightMagenta,
			kLightBrown,
			kWhite
		};
		Color(u8 foreground, u8 background) :
			color(foreground | background << 4) {}
		u8 color;
	};

	virtual Color GetColor() const = 0;
	virtual void SetColor(const Color &c) = 0;
	virtual void Paint() = 0;
	virtual void Clear() = 0;
};

} // namespace basilisk

#endif // BOS_SCREEN_H_
