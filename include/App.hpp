#pragma once

#include <vector>
namespace sf { class Window; }
class Drawer;
class Listener;


class App
{
public:
	App();
	~App();
	
	void run();
	
	int getWindowWidth();
	int getWindowHeight();
	
	void addDrawer(Drawer* drawer, int priority);
	void addListener(Listener* listener, int priority);

private:
	sf::Window* m_window;
	std::vector<Drawer*> m_drawers;
	std::vector<Listener*> m_listeners;
	std::vector<int> m_drawPri;
	std::vector<int> m_listPri;
	int m_pressIndex;
};
