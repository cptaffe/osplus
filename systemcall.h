
#ifndef BOS_SYSTEMCALL_H_
#define BOS_SYSTEMCALL_H_

#include "types.h"

namespace basilisk {

class SystemCall {
public:
	static SystemCall& GetInstance() { return syscall_; }
	void Invoke(u32 *args);
private:
	static SystemCall syscall_;
};

} // namespace basilisk

#endif // BOS_SYSTEMCALL_H_
