#include "App.hpp"
#include "Drawer.hpp"
#include "Listener.hpp"
#include "Editor.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>



App::App()
{
	// Create the window
	sf::ContextSettings settings;
	settings.depthBits = 24;
	m_window = new sf::RenderWindow(sf::VideoMode(400, 300), "Moxel Editor", sf::Style::Default, settings);
	m_pressIndex = 0;
}



App::~App()
{
	m_window->close();
	delete m_window;
}



void App::run()
{
	// Set up opengl
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
	// Create the editor
	Editor ed(this);
	
	
	// Main loop
	bool isRunning = true;
	while (isRunning)
	{
		// Handle input
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				isRunning = false;
			if (event.type == sf::Event::KeyReleased &&
					event.key.code == sf::Keyboard::Escape)
				isRunning = false;
				
			// Pass input to listeners
			if (event.type == sf::Event::MouseMoved)
			{
				for (unsigned int i = 0; i < m_listeners.size(); i++) {
					if (m_listeners[i]->mouseMove(event.mouseMove.x, event.mouseMove.y))
						break;
				}
			} else
			if (event.type == sf::Event::MouseWheelMoved)
			{
				for (unsigned int i = 0; i < m_listeners.size(); i++) {
					if (m_listeners[i]->mouseWheelMove(event.mouseWheel.delta))
						break;
				}
			} else
			if (event.type == sf::Event::MouseButtonPressed)
			{
				m_pressIndex = (int)m_listeners.size() - 1;
				for (unsigned int i = 0; i < m_listeners.size(); i++) {
					if (m_listeners[i]->mousePress(event.mouseButton.button))
					{
						m_pressIndex = (int)i;
						break;
					}
				}
			} else
			if (event.type == sf::Event::MouseButtonReleased)
			{
				for (unsigned int i = 0; i <= m_pressIndex; i++) {
					m_listeners[i]->mouseRelease(event.mouseButton.button);
				}
			} else
			if (event.type == sf::Event::KeyPressed)
			{
				for (unsigned int i = 0; i < m_listeners.size(); i++) {
					if (m_listeners[i]->keyPress(event.key))
						break;
				}
			} else
			if (event.type == sf::Event::KeyReleased)
			{
				for (unsigned int i = 0; i < m_listeners.size(); i++) {
					m_listeners[i]->keyRelease(event.key);
				}
			} else
			if (event.type == sf::Event::TextEntered)
			{
				for (unsigned int i = 0; i < m_listeners.size(); i++) {
					if (m_listeners[i]->textEntered(event.text))
						break;
				}
			}
		}
		
		// Clear all the pixels
		glViewport(0, 0, getWindowWidth(), getWindowHeight());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw our drawers
		for (unsigned int i = 0; i < m_drawers.size(); i++)
		{
			m_drawers[i]->draw();
		}
		
		// Render it to the window
		m_window->display();
		
		
		// Add a little delay, to give the cpu some breathing room
		sf::sleep(sf::milliseconds(1));
	}
}



int App::getWindowWidth()
{
	return m_window->getSize().x;
}



int App::getWindowHeight()
{
	return m_window->getSize().y;
}



void App::addDrawer(Drawer* drawer, int priority)
{
	if (drawer == 0)
		return;
		
	// Position the drawer based on it's priority
	for (unsigned int i = 0; i < m_drawPri.size(); i++)
	{
		if (m_drawPri[i] <= priority)
			continue;
		m_drawPri.insert(m_drawPri.begin() + i, priority);
		m_drawers.insert(m_drawers.begin() + i, drawer);
		break;
	}
	
	// It belongs at the back
	m_drawPri.push_back(priority);
	m_drawers.push_back(drawer);
}



void App::addListener(Listener* listener, int priority)
{
	if (listener == 0)
		return;
		
	// Position the listener based on it's priority
	for (unsigned int i = 0; i < m_listPri.size(); i++)
	{
		if (m_listPri[i] <= priority)
			continue;
		m_listPri.insert(m_listPri.begin() + i, priority);
		m_listeners.insert(m_listeners.begin() + i, listener);
		break;
	}
	
	// It belongs at the back
	m_listPri.push_back(priority);
	m_listeners.push_back(listener);
}
