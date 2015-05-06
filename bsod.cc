
#include "bsod.h"
#include "driver/vga.h"
#include "io.h"

namespace basilisk {

// Here follows a message mirroring that of the
// Windows XP BSOD screen.
Buffer message = "\nA problem has been detected and BasiliskOS has been shut down to prevent damage to your computer.\n\n"
"The problem seems to be caused by the following file FUCKOFF.SYS\n\n"
"STOP_BEING_A_TOTAL_BITCH\n\n"
"If this is the first time you've seen this Stop error screen,\n"
"restart your computer. If this screen appears again, follow\n"
"these steps:\n\n"
"Check to make sure any new hardware or software is properly installed.\n"
"If this is a new installation, ask your hardware or software manufacturer\n"
"for any BasiliskOS updates you might need.\n\n"
"If problems continue, disable or remove any newly installed hardware\n"
"or software. Disable BIOS memory options such as caching or shadowing.\n"
"If you need to use Safe Mode to remove or disable components, restart\n"
"your computer, press F8 to select Advanced Startup Options, and then\n"
"select Safe Mode.\n\n"
"Technical information:\n\n"
"This was all a lie, there is no safe mode.";

BlueScreenOfDeath BlueScreenOfDeath::bsod_;

BlueScreenOfDeath::BlueScreenOfDeath() {}

BlueScreenOfDeath& BlueScreenOfDeath::Instance() {
	return bsod_;
}

void BlueScreenOfDeath::Invoke() {
	driver::VGAScreen& screen = driver::VGAScreen::Instance();
	screen.SetBackground(driver::VGAScreen::kBlue);
	screen.SetForeground(driver::VGAScreen::kWhite);
	screen.Clear();
	screen.Paint();
	IO::Instance().Put(message);
}

} // namespace basilisk
