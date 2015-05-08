#pragma once

#include "Drawer.hpp"
#include "Listener.hpp"
class App;


class Camera : public Drawer, public Listener {
public:
	Camera(App* app);
	~Camera();
	
	virtual void draw();
	
	virtual bool mousePress(const int button);
	virtual void mouseRelease(const int button);
	virtual bool mouseMove(const int x, const int y);
	virtual bool mouseWheelMove(const int w);
	virtual bool keyPress(sf::Event::KeyEvent k);
	
	bool isRotationLocked() const;
	bool isPositionLocked() const;
	void isRotationLocked(const bool locked);
	void isPositionLocked(const bool locked);
	
	void setRadius(const float r);
	float getRadius() const;
	
	void setRotationX(const float x);
	void setRotationY(const float y);
	float getRotationX() const;
	float getRotationY() const;
	
	void setOriginX(const float x);
	void setOriginY(const float y);
	void setOriginZ(const float z);
	float getOriginX() const;
	float getOriginY() const;
	float getOriginZ() const;
	
	float getCameraX() const;
	float getCameraY() const;
	float getCameraZ() const;
	
	void moveRight(const float dist);
	void moveForward(const float dist);
	void moveUp(const float dist);
	void rotateX(const float deg);
	void rotateY(const float deg);
	
	App* getApp();

private:
	App* m_app;
	bool m_isRotLocked;
	bool m_isPosLocked;
	float m_radius;
	float m_oriX;
	float m_oriY;
	float m_oriZ;
	float m_rotX;
	float m_rotY;
	int m_oldMouseX;
	int m_oldMouseY;
	
	void _zoomIn();
	void _zoomOut();
};
