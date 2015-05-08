#pragma once

#include <string>


class Button {
public:
	Button();
	virtual ~Button();
	
	void setName(const std::string& name);
	std::string getName() const;
	
	void isDown(const bool down);
	bool isDown() const;
	
	void press();
	void release();

protected:
	virtual void _pressCallback();
	virtual void _releaseCallback();

private:
	std::string m_name;
	bool m_isDown;
};
