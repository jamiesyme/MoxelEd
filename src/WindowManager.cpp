#include "WindowManager.hpp"
#include "Window.hpp"
#include "GlHelper.hpp"
#include "App.hpp"
#include <iostream>



WindowManager::WindowManager(App* app)
{
	m_app = app;
	m_mouseX = 0;
	m_mouseY = 0;
	m_nextWindowY = 0;
}



WindowManager::~WindowManager()
{
	while (m_windows.size() != 0)
		destroyWindow(m_windows[0]);
}



void WindowManager::draw()
{
	GlHelper gl;
	gl.disableDepthTest();
	gl.setWindowSize(m_app->getWindowWidth(), m_app->getWindowHeight());
	gl.enableOrtho();
	for (int i = (int)m_windows.size() - 1; i >= 0; i--)
		m_windows[i]->draw();
}



bool WindowManager::mousePress(const int button)
{
	int selectIndex = -1;
	bool quitEarly = false;
	for (unsigned int i = 0; i < m_windows.size(); i++)
	{
		if (selectIndex == -1 && m_windows[i]->isOver(m_mouseX, m_mouseY))
			selectIndex = (int)i;
		if (m_windows[i]->mousePress(button))
		{
			quitEarly = true;
			break;
		}
	}
	
	if (selectIndex != -1)
	{
		Window* newFront = m_windows[selectIndex];
		for (int i = selectIndex; i > 0; i--)
			m_windows[i] = m_windows[i - 1];
		m_windows[0] = newFront;
	}
	
	return quitEarly;
}



void WindowManager::mouseRelease(const int button)
{
	for (unsigned int i = 0; i < m_windows.size(); i++)
		m_windows[i]->mouseRelease(button);
	return;
}



bool WindowManager::mouseMove(const int x, const int y)
{
	m_mouseX = x;
	m_mouseY = y;
	for (unsigned int i = 0; i < m_windows.size(); i++)
		if (m_windows[i]->mouseMove(x, y))
			return true;
	return false;
}



bool WindowManager::mouseWheelMove(const int w)
{
	for (unsigned int i = 0; i < m_windows.size(); i++)
		if (m_windows[i]->mouseWheelMove(w))
			return true;
	return false;
}



Window* WindowManager::createWindow()
{
	Window* w = new Window();
	w->setY(m_nextWindowY);
	m_nextWindowY += w->getHeadSizeY() + 1;
	m_windows.push_back(w);
	return w;
}



void WindowManager::destroyWindow(Window* w)
{
	for (unsigned int i = 0; i < m_windows.size(); i++)
	{
		if (w == m_windows[i])
		{
			delete w;
			m_windows.erase(m_windows.begin() + i);
			return;
		}
	}
}
