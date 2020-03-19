#include <blessings/terminal.hpp>
#include <blessings/monitor.hpp>

#include <chrono>
#include <thread>
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

class Display
{
public:
	Display()
	{
		term.init();
		monitor.connect(&term);
		resolution = monitor.terminalResolution();
		monitor.setResolution(resolution);
		monitor.initscr();
	}
	~Display()
	{
		//monitor.endwin();
	}

	void centerx(int y, std::string str, blessings::PropertyANSI colors = {})
	{
		size_t x = 0;
		if (resolution.width > str.size()) {
			x = (resolution.width - str.size()) / 2;
		}
		for (size_t i = 0; i < str.size(); ++ i, ++ x) {
			while (x >= resolution.width) {
				x -= resolution.width;
				++ y;
			}
			monitor(x,y) = blessings::Monitor::Cell(str[i], colors);
		}
	}

	blessings::Terminal term;
	blessings::Monitor monitor;
	blessings::Resolution resolution;
};

void step()
{
}

int main() {
	Display display;
	//display.monitor.tile(".");
	//display.monitor(4,4) = "@";
	display.centerx(2, "YOU HAVE BEEN ASSIMILATED INTO THE INTERGALACTIC BORG COLLECTIVE", {{},blessings::ColorANSI::BLACK,false,true});
	display.centerx(7, "YOU ARE MONITORED AND NETWORKED AND WILL BE REASSIMILATED IF YOU DEVIATE FROM YOUR PARAMETERS", {{},blessings::ColorANSI::BLACK,false,true});

	//EM_ASM({console.log('about-to-draw');});

	display.monitor.draw();

#ifdef __EMSCRIPTEN__
	//emscripten_set_main_loop(step, 25, 1);
#else
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 25));
		step();
	}
#endif
	return 0;
}
