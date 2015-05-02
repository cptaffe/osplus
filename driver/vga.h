
#ifndef OS_DRIVER_VGA_H_
#define OS_DRIVER_VGA_H_

#include "../types.h"
#include "../writer.h"

namespace os {
namespace driver {

class VGAWriter : public os::Writer {
public:
	VGAWriter();
	static VGAWriter *Instance() { return &vga; }
	virtual void WriteByte(u8 c);
private:
	static VGAWriter vga;

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
} // namespace os

#endif // OS_DRIVER_VGA_H_
