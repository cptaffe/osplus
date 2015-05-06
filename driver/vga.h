
#ifndef OS_DRIVER_VGA_H_
#define OS_DRIVER_VGA_H_

#include "../types.h"
#include "../writeable.h"

namespace basilisk {
namespace driver {

class VGAWriter : public basilisk::Writeable {
public:
	VGAWriter();
	static VGAWriter& Instance() { return vga; }
	virtual bool Write(Buffer& buf);
private:
	static VGAWriter vga;
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
