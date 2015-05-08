#include "Button.hpp"



Button::Button()
{
	m_name = "button";
	m_isDown = false;
}



Button::~Button()
{
}



void Button::setName(const std::string& name)
{
	m_name = name;
}



std::string Button::getName() const
{
	return m_name;
}



void Button::isDown(const bool down)
{
	m_isDown = down;
}



bool Button::isDown() const
{
	return m_isDown;
}



void Button::press()
{
	isDown(true);
	_pressCallback();
}



void Button::release()
{
	isDown(false);
	_releaseCallback();
}



void Button::_pressCallback() {}
void Button::_releaseCallback() {}
