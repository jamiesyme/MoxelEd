#pragma once

#include <SFML/Window/Event.hpp>


class Listener {
public:
	Listener() {}
	virtual ~Listener() {}
	
	virtual bool mousePress(const int button) { return false; }
	virtual void mouseRelease(const int button) { return; }
	virtual bool mouseMove(const int x, const int y) { return false; }
	virtual bool mouseWheelMove(const int w) { return false; }
	virtual bool keyPress(sf::Event::KeyEvent k) { return false; }
	virtual void keyRelease(sf::Event::KeyEvent k) { return; }
	virtual bool textEntered(sf::Event::TextEvent t) { return false; }
};
