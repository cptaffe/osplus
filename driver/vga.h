
#ifndef OS_DRIVER_VGA_H_
#define OS_DRIVER_VGA_H_

#include "../types.h"
#include "../writeable.h"

namespace basilisk {
namespace driver {

class VGAScreen : public basilisk::Writeable {
public:
	static VGAScreen& Instance() { return vga; }
	virtual bool Write(const Buffer& buf);

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

	// Color augmentation functions (whole screen)
	u8 Background();
	u8 Foreground();
	void SetBackground(u8 color);
	void SetForeground(u8 color);

	// clear text to ' '
	void Clear();
	// clear color to current color setting.
	void Paint();
private:
	VGAScreen();
	static VGAScreen vga;
	void Put(u8 c);
	void Newline();

	enum {
		kWidth = 80,
		kHeight = 25
	};

	u16 color = 7;
	int i = 0, j = 0;
	u16 *buf = (u16 *) 0xb8000;
};

} // namespace driver
} // namespace basilisk

#endif // OS_DRIVER_VGA_H_
