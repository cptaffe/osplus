
#ifndef OS_TERMINAL_H_
#define OS_TERMINAL_H_

namespace os {
class Terminal {
public:
	virtual ~Terminal() {};
	virtual void Put(char c) = 0;
};
} // namespace os

#endif // OS_TERMINAL_H_
