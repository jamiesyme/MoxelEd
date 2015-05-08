#include "Window.hpp"
#include "UiText.h"
#include "Button.hpp"
#include <SFML/OpenGL.hpp>
#include <iostream>

#define BUTTON_PADDING 10
#define BUTTON_HEIGHT 30



Window::Window()
{
	m_isEnabled = true;
	m_isOpen = false;
	m_x = 0;
	m_y = 0;
	m_sx = 250;
	m_title = new UiText();
	m_title->SetText("Window");
	m_title->SetTextSize(24);
	m_title->SetFont("SourceCodePro-Medium.otf");
	m_mouseX = 0;
	m_mouseY = 0;
	m_isGrabbed = false;
	m_grab_mouseX = 0;
	m_grab_mouseY = 0;
	m_grab_x = 0;
	m_grab_y = 0;
}



Window::~Window()
{
	delete m_title;
	for (unsigned int i = 0; i < m_buttons.size(); i++)
	{
		delete m_buttons[i];
		delete m_buttonsText[i];
	}
}



void Window::draw()
{
	if (!isEnabled())
		return;
		
	glPushMatrix();

	// Draw the header
	int hsy = getHeadSizeY();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
		glVertex2i(m_x, m_y);
		glVertex2i(m_x + m_sx, m_y);
		glVertex2i(m_x + m_sx, m_y + hsy);
		glVertex2i(m_x + m_sx, m_y + hsy);
		glVertex2i(m_x, m_y + hsy);
		glVertex2i(m_x, m_y);
	glEnd();
	
	// Draw the open/close button
	glTranslatef(0.0f, 0.0f, 0.05f);
	glColor3f(0.9f, 0.9f, 0.9f);
	if (m_mouseY >= m_y && m_mouseY < m_y + hsy &&
			m_mouseX < m_x + m_sx && m_mouseX >= m_x + m_sx - hsy)
		glColor3f(1.0f, 0.8f, 0.8f);
	glBegin(GL_TRIANGLES);
		glVertex2i(m_x + m_sx - hsy, m_y);
		glVertex2i(m_x + m_sx, m_y);
		glVertex2i(m_x + m_sx, m_y + hsy);
		glVertex2i(m_x + m_sx, m_y + hsy);
		glVertex2i(m_x + m_sx - hsy, m_y + hsy);
		glVertex2i(m_x + m_sx - hsy, m_y);
	glEnd();
	
	// Draw the window title
	glTranslatef(0.0f, 0.0f, 0.05f);
	m_title->SetCenterLeftPosition(m_x + 5, m_y + getHeadSizeY() / 2);
	m_title->Draw();
	
	// If the window is closed, we don't draw anymore
	if (!m_isOpen)
		return;
		
	// Draw the body
	glTranslatef(0.0f, 0.0f, 0.05f);
	int bsy = getSizeY() - hsy;
	glColor3f(0.8f, 0.8f, 0.8f);
	glBegin(GL_TRIANGLES);
		glVertex2i(m_x, m_y + hsy);
		glVertex2i(m_x + m_sx, m_y + hsy);
		glVertex2i(m_x + m_sx, m_y + hsy + bsy);
		glVertex2i(m_x + m_sx, m_y + hsy + bsy);
		glVertex2i(m_x, m_y + hsy + bsy);
		glVertex2i(m_x, m_y + hsy);
	glEnd();
	
	// Draw the buttons
	glTranslatef(0.0f, 0.0f, 0.05f);
	int hoverBut = _getButtonUnder(m_mouseX, m_mouseY);
	int butX1 = m_x + BUTTON_PADDING;
	int butX2 = m_x + m_sx - BUTTON_PADDING;
	for (unsigned int i = 0; i < m_buttons.size(); i++)
	{
		int y = i * (BUTTON_HEIGHT + BUTTON_PADDING) + BUTTON_PADDING;
		
		if (m_buttons[i]->isDown())
		{
			glTranslatef(0.0f, 0.0f, -0.01f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glBegin(GL_TRIANGLES);
				glVertex2i(butX1 - 2, m_y + hsy + y - 2);
				glVertex2i(butX2 + 2, m_y + hsy + y - 2);
				glVertex2i(butX2 + 2, m_y + hsy + y + BUTTON_HEIGHT + 2);
				glVertex2i(butX2 + 2, m_y + hsy + y + BUTTON_HEIGHT + 2);
				glVertex2i(butX1 - 2, m_y + hsy + y + BUTTON_HEIGHT + 2);
				glVertex2i(butX1 - 2, m_y + hsy + y - 2);
			glEnd();
			glTranslatef(0.0f, 0.0f, 0.01f);
		}
		
		glColor3f(1.0f, 1.0f, 1.0f);
		if (hoverBut == (int)i)
			glColor3f(1.0f, 0.8f, 0.8f);
			
		glBegin(GL_TRIANGLES);
			glVertex2i(butX1, m_y + hsy + y);
			glVertex2i(butX2, m_y + hsy + y);
			glVertex2i(butX2, m_y + hsy + y + BUTTON_HEIGHT);
			glVertex2i(butX2, m_y + hsy + y + BUTTON_HEIGHT);
			glVertex2i(butX1, m_y + hsy + y + BUTTON_HEIGHT);
			glVertex2i(butX1, m_y + hsy + y);
		glEnd();
		
		glTranslatef(0.0f, 0.0f, 0.05f);
		if (m_buttonsText[i]->GetText().compare(m_buttons[i]->getName()) != 0)
			m_buttonsText[i]->SetText(m_buttons[i]->getName());
		m_buttonsText[i]->SetCenterPosition((butX1 + butX2) / 2, m_y + hsy + y + BUTTON_HEIGHT / 2);
		m_buttonsText[i]->Draw();
		glTranslatef(0.0f, 0.0f, -0.05f);
	}
	
	glPopMatrix();
}



bool Window::mousePress(const int button)
{
	if (!isEnabled())
		return false;
	if (!isOver(m_mouseX, m_mouseY))
		return false;
	
	if (m_mouseY < m_y + getHeadSizeY()) {
		if (m_mouseX > m_x + m_sx - getHeadSizeY())
			m_isOpen = !m_isOpen;
		else 
		{
			m_isGrabbed = true;
			m_grab_x = m_x;
			m_grab_y = m_y;
			m_grab_mouseX = m_mouseX;
			m_grab_mouseY = m_mouseY;
		}
	} else
	{
		int button = _getButtonUnder(m_mouseX, m_mouseY);
		if (button != -1)
			m_buttons[button]->press();
	}
	
	return true;
}



void Window::mouseRelease(const int button)
{
	if (!isEnabled())
		return;
	if (m_isGrabbed)
		m_isGrabbed = false;
	for (unsigned int i = 0; i < m_buttons.size(); i++)
		if (m_buttons[i]->isDown())
			m_buttons[i]->release();
}



bool Window::mouseMove(const int x, const int y)
{
	if (!isEnabled())
		return false;
		
	m_mouseX = x;
	m_mouseY = y;
	
	if (m_isGrabbed) {
		
		// Move the window
		m_x = m_grab_x + x - m_grab_mouseX;
		m_y = m_grab_y + y - m_grab_mouseY;
		return true;
	}
	
	if (isOver(x, y))
		return true;
		
	return false;
}



bool Window::mouseWheelMove(const int w)
{
	if (!isEnabled())
		return false;
	if (!isOver(m_mouseX, m_mouseY))
		return false;
		
	return true;
}



void Window::isEnabled(const bool enabled)
{
	m_isEnabled = enabled;
}



bool Window::isEnabled() const
{
	return m_isEnabled;
}



bool Window::isOver(const int x, const int y) const
{
	if (!isEnabled())
		return false;
	if (x < m_x || x >= m_x + m_sx)
		return false;
	if (m_isOpen)
	{
		if (y < m_y || y >= m_y + getSizeY())
			return false;
	} else
	{
		if (y < m_y || y >= m_y + getHeadSizeY())
			return false;
	}
	return true;
}



void Window::setTitle(std::string t)
{
	m_title->SetText(t);
}



std::string Window::getTitle() const
{
	return m_title->GetText();
}



void Window::setX(int x)
{
	m_x = x;
}



void Window::setY(int y)
{
	m_y = y;
}



void Window::setSizeX(int x)
{
	m_sx = x;
}



int Window::getX() const
{
	return m_x;
}



int Window::getY() const
{
	return m_y;
}



int Window::getSizeX() const
{
	return m_sx;
}



int Window::getSizeY() const
{
	return getHeadSizeY() + (int)m_buttons.size() * (BUTTON_PADDING + BUTTON_HEIGHT) + BUTTON_PADDING;
}



int Window::getHeadSizeY() const
{
	return m_title->GetTextSize() + 10;
}



void Window::manageButton(Button* button)
{
	if (button == 0)
		return;
	m_buttons.push_back(button);
	UiText* text = new UiText();
	text->SetTextSize(20);
	text->SetFont("SourceCodePro-Medium.otf");
	m_buttonsText.push_back(text);
}



int Window::_getButtonUnder(const int x, const int y)
{
	if (!m_isOpen)
		return -1;

	if (x < m_x + BUTTON_PADDING)
		return -1;
	if (x >= m_x + m_sx - BUTTON_PADDING)
		return -1;
	int hsy = getHeadSizeY();
	if (y < m_y + hsy)
		return -1;
	if (y > m_y + hsy + (int)m_buttons.size() * (BUTTON_PADDING + BUTTON_HEIGHT))
		return -1;
		
	for (int i = 0; i < (int)m_buttons.size(); i++)
	{
		if (y >= m_y + hsy + (i + 1) * BUTTON_PADDING && 
				y <  m_y + hsy + (i + 1) * (BUTTON_PADDING + BUTTON_HEIGHT))
			return i;
	}
	
	return -1;
}
