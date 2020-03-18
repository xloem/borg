#include <blessings/terminal.hpp>
#include <blessings/monitor.hpp>

#include <chrono>
#include <thread>

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
		size_t x = (resolution.width - str.size()) / 2;
		for (size_t i = 0; i < str.size(); ++ i) {
			monitor(x+i,y) = blessings::Monitor::Cell(str[i], colors);
		}
	}

	blessings::Terminal term;
	blessings::Monitor monitor;
	blessings::Resolution resolution;
};

int main() {
	Display display;
	//display.monitor.tile(".");
	//display.monitor(4,4) = "@";
	
	display.centerx(2, "YOU HAVE BEEN ASSIMILATED INTO THE INTERGALACTIC BORG COLLECTIVE", {{},blessings::ColorANSI::BLACK,false,true});
	display.centerx(7, "YOU ARE MONITORED AND NETWORKED AND WILL BE REASSIMILATED IF YOU DEVIATE FROM YOUR PARAMETERS", {{},blessings::ColorANSI::BLACK,false,true});

	display.monitor.draw();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	return 0;
}
