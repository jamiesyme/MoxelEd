#pragma once

#include <string>
#include <vector>
#include "Listener.hpp"
#include "Drawer.hpp"
class UiText;
class Button;


class Window : public Listener, public Drawer {
public:
	Window();
	~Window();
	
	virtual void draw();
	
	virtual bool mousePress(const int button);
	virtual void mouseRelease(const int button);
	virtual bool mouseMove(const int x, const int y);
	virtual bool mouseWheelMove(const int w);
	
	void isEnabled(const bool enable);
	bool isEnabled() const;
	
	bool isOver(const int x, const int y) const;
	
	void setTitle(std::string t);
	std::string getTitle() const;
	
	void setX(int x);
	void setY(int y);
	void setSizeX(int x);
	int getX() const;
	int getY() const;
	int getSizeX() const;
	int getSizeY() const;
	int getHeadSizeY() const;
	
	void manageButton(Button* button);

private:
	bool m_isEnabled;
	bool m_isOpen;
	int m_x;
	int m_y;
	int m_sx;
	UiText* m_title;
	int m_mouseX;
	int m_mouseY;
	bool m_isGrabbed;
	int m_grab_mouseX;
	int m_grab_mouseY;
	int m_grab_x;
	int m_grab_y;
	std::vector<Button*> m_buttons;
	std::vector<UiText*> m_buttonsText;
	
	int _getButtonUnder(const int x, const int y);
};
