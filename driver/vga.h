
#ifndef OS_DRIVER_VGA_H_
#define OS_DRIVER_VGA_H_

#include "../types.h"
#include "../writeable.h"
#include "../screen.h"

namespace basilisk {
namespace driver {

class VGAScreen : public basilisk::Screen {
public:
	static VGAScreen& GetInstance() { return vga; }
	virtual bool Write(const Buffer& buf);

	// Color augmentation functions (whole screen)
	virtual basilisk::Screen::Color GetColor() const;
	virtual void SetColor(const basilisk::Screen::Color& c);
	virtual void Paint();
	virtual void Clear();
private:
	VGAScreen();
	static VGAScreen vga;
	void Put(u8 c);
	void Newline();

	enum {
		kWidth = 80,
		kHeight = 25
	};

	basilisk::Screen::Color color;
	int i = 0, j = 0;
	u16 *buf = (u16 *) 0xb8000;
};

} // namespace driver
} // namespace basilisk

#endif // OS_DRIVER_VGA_H_
