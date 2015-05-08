#pragma once

#include <vector>
#include "Listener.hpp"
#include "Drawer.hpp"
class Window;
class App;


class WindowManager : public Listener, public Drawer {
public:
	WindowManager(App* app);
	~WindowManager();
	
	virtual void draw();
	
	virtual bool mousePress(const int button);
	virtual void mouseRelease(const int button);
	virtual bool mouseMove(const int x, const int y);
	virtual bool mouseWheelMove(const int w);
	
	Window* createWindow();
	void destroyWindow(Window* w);

private:
	App* m_app;
	int m_mouseX;
	int m_mouseY;
	std::vector<Window*> m_windows;
	int m_nextWindowY;
};
