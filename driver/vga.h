
#ifndef OS_DRIVER_VGA_H_
#define OS_DRIVER_VGA_H_

#include "../types.h"
#include "../terminal.h"

namespace os {
namespace driver {

class VGA : public os::Terminal {
public:
	virtual void Put(char c);
	static VGA *Instance() { return &vga; }
private:
	void Newline();
	void Clear();

	static VGA vga;
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
