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
		monitor.endwin();
	}

	void center(int y, std::string str)
	{
		size_t x = (resolution.width - str.size()) / 2;
		for (size_t i = 0; i < str.size(); ++ i) {
			monitor(x+i,y) = str[i];
		}
	}

	blessings::Terminal term;
	blessings::Monitor monitor;
	blessings::Resolution resolution;
};

void center(int y, std::string str)
{

}

int main() {
	Display display;
	display.monitor.tile(".");
	display.monitor(4,4) = "@";
	display.center(5, "Hello");
	display.monitor.draw();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	return 0;
}
