
#ifndef OS_DRIVER_VGA_H_
#define OS_DRIVER_VGA_H_

#include "../types.h"
#include "../writer.h"

namespace os {
namespace driver {

class VGAWriter : public os::Writer {
public:
	static VGAWriter *Instance() { return &vga; }
	virtual void WriteByte(u8 c);
private:
	static VGAWriter vga;

	void Newline();
	void Clear();

	enum {
		kWidth = 80,
		kHeight = 25
	};

	// get around constructor issues
	bool initialized = false;

	u16 color = 7;
	int i = 0, j = 0;
	u16 *buf = (u16 *) 0xb8000;
};

} // namespace driver
} // namespace os

#endif // OS_DRIVER_VGA_H_
