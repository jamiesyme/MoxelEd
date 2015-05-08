#include "Camera.hpp"
#include "GlHelper.hpp"
#include "App.hpp"
#include <cmath>

#define DEG_TO_RAD 3.141592654f / 180.0f
#define RAD_TO_DEG 180.0f / 3.141592654f



Camera::Camera(App* app)
{
	m_app = app;
	m_isRotLocked = false;
	m_isPosLocked = false;
	m_radius = 3.0f;
	m_oriX = 0.0f;
	m_oriY = 0.0f;
	m_oriZ = 0.0f;
	m_rotX = 0.0f;
	m_rotY = 0.0f;
	m_oldMouseX = 0;
	m_oldMouseY = 0;
}



Camera::~Camera()
{
}



void Camera::draw()
{
	/*glm::mat4 projMat = glm::perspective(90.0f, 
																			 (float)m_app->getWindowWidth() / (float)m_app->getWindowHeight(),
																			 0.1f,
																			 100.0f);
	glm::mat4 viewMat = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	viewMat = glm::rotate(viewMat, -getRotationX(), glm::vec3(1.0f, 0.0f, 0.0f));
	viewMat = glm::rotate(viewMat, -getRotationY(), glm::vec3(0.0f, 1.0f, 0.0f));
	viewMat = glm::translate(viewMat, glm::vec3(-getCameraX(), -getCameraY(), -getCameraZ()));
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(&projMat[0][0]);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(&viewMat[0][0]);*/
	
	GlHelper gl;
	gl.enableDepthTest();
	gl.setWindowSize(m_app->getWindowWidth(), m_app->getWindowHeight());
	gl.enablePersp(60.0f);
	gl.setEyes(getCameraX(), getCameraY(), getCameraZ(),
						 getRotationX(), getRotationY(), 0.0f);
}



bool Camera::mousePress(const int button)
{
	if (button == 2)
		isRotationLocked(false);
	if (button == 1)
		isPositionLocked(false);
	
	return false;
}



void Camera::mouseRelease(const int button)
{
	if (button == 2)
		isRotationLocked(true);
	if (button == 1)
		isPositionLocked(true);
}



bool Camera::mouseMove(const int x, const int y)
{
	int difX = x - m_oldMouseX;
	int difY = y - m_oldMouseY;
	m_oldMouseX = x;
	m_oldMouseY = y;

	rotateX(-difY * 1.0f);
	rotateY(-difX * 1.0f);

	float speed = getRadius() / 100.0f;
	moveRight(-difX * speed);
	moveUp(-difY * speed);
	
	return false;
}



bool Camera::mouseWheelMove(const int w)
{
	if (w < 0)
		for (int i = 0; i < -w; i++)
			_zoomOut();
	if (w > 0)
		for (int i = 0; i < w; i++)
			_zoomIn();
	
	return true;
}



bool Camera::keyPress(sf::Event::KeyEvent k)
{
	if (k.control && k.code == sf::Keyboard::Add)
	{
		_zoomIn();
		return true;
	}
	if (k.control && k.code == sf::Keyboard::Subtract)
	{
		_zoomOut();
		return true;
	}
	if (k.code == sf::Keyboard::Space)
	{
		isRotationLocked(!isRotationLocked());
		return true;
	}
	return false;
}



bool Camera::isRotationLocked() const
{
	return m_isRotLocked;
}



bool Camera::isPositionLocked() const
{
	return m_isPosLocked;
}



void Camera::isRotationLocked(const bool locked)
{
	m_isRotLocked = locked;
}



void Camera::isPositionLocked(const bool locked)
{
	m_isPosLocked = locked;
}



void Camera::setRadius(const float r)
{
	if (r <= 0.0f)
		m_radius = 0.0f;
	else
		m_radius = r;
}



float Camera::getRadius() const
{
	return m_radius;
}



void Camera::setRotationX(const float x)
{
	if (m_isRotLocked)
		return;
		
	if (x < -89.0f)
		m_rotX = -89.0f * DEG_TO_RAD;
	else if (x > 89.0f)
		m_rotX = 89.0f * DEG_TO_RAD;
	else
		m_rotX = x * DEG_TO_RAD;
}



void Camera::setRotationY(const float y)
{
	if (m_isRotLocked)
		return;
		
	m_rotY = y * DEG_TO_RAD;
}



float Camera::getRotationX() const
{
	return m_rotX * RAD_TO_DEG;
}



float Camera::getRotationY() const
{
	return m_rotY * RAD_TO_DEG;
}



void Camera::setOriginX(const float x)
{
	if (m_isPosLocked)
		return;
	m_oriX = x;
}



void Camera::setOriginY(const float y)
{
	if (m_isPosLocked)
		return;
	m_oriY = y;
}



void Camera::setOriginZ(const float z)
{
	if (m_isPosLocked)
		return;
	m_oriZ = z;
}



float Camera::getOriginX() const
{
	return m_oriX;
}



float Camera::getOriginY() const
{
	return m_oriY;
}



float Camera::getOriginZ() const
{
	return m_oriZ;
}



float Camera::getCameraX() const
{
	float x = m_oriX;
	x += std::sin(m_rotY) * (std::cos(m_rotX) * m_radius);
	
	return x;
}



float Camera::getCameraY() const
{
	float y = m_oriY;
	y -= std::sin(m_rotX) * m_radius;
	
	return y;
}



float Camera::getCameraZ() const
{
	float z = m_oriZ;
	z += std::cos(m_rotY) * (std::cos(m_rotX) * m_radius);
	
	return z;
}



void Camera::moveRight(const float dist)
{
	if (m_isPosLocked)
		return;
	m_oriX += std::cos(m_rotY) * dist;
	m_oriZ -= std::sin(m_rotY) * dist;
}



void Camera::moveForward(const float dist)
{
	if (m_isPosLocked)
		return;
	m_oriX += std::sin(m_rotY) * std::cos(m_rotX) * dist;
	m_oriY -= std::sin(m_rotX) * dist;
	m_oriZ -= std::cos(m_rotY) * std::cos(m_rotX) * dist;
}



void Camera::moveUp(const float dist)
{
	if (m_isPosLocked)
		return;
	m_oriX -= std::sin(m_rotY) * std::sin(m_rotX) * dist;
	m_oriY -= std::cos(m_rotX) * dist;
	m_oriZ -= std::cos(m_rotY) * std::sin(m_rotX) * dist;
}



void Camera::rotateX(const float deg)
{
	setRotationX(getRotationX() + deg);
}



void Camera::rotateY(const float deg)
{
	setRotationY(getRotationY() + deg);
}



App* Camera::getApp()
{
	return m_app;
}



void Camera::_zoomIn()
{
	setRadius(getRadius() * 0.9f);
}



void Camera::_zoomOut()
{
	setRadius(getRadius() / 0.9f);
}
