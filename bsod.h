
#ifndef BOS_BSOD_H_
#define BOS_BSOD_H_

#include "kernel.h"
#include "screen.h"

namespace basilisk {

// Blue Screen of Death (BSOD) Singleton.
// This is one of the most important features of this OS.
// Seriously you guys, seriously
class BlueScreenOfDeath {
public:
	static BlueScreenOfDeath& Instance();
	// Invokes the fury of the blue screen.
	void Invoke(Screen &screen = Kernel::GetInstance().GetScreen(), const char *str = message);
private:
	BlueScreenOfDeath();
	static BlueScreenOfDeath bsod_;

	static const char *message;
};

} // namespace basilisk

#endif // BOS_BSOD_H_
