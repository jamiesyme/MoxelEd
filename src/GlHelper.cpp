#include "GlHelper.hpp"
#include <SFML/OpenGL.hpp>
#include <cmath>



GlHelper::GlHelper()
{
	m_width = 0;
	m_height = 0;
}



GlHelper::~GlHelper()
{
}



void GlHelper::setWindowSize(const int w, const int h)
{
	m_width = w;
	m_height = h;
}



void GlHelper::enableOrtho()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, m_width, m_height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



void GlHelper::enablePersp(const float fov)
{
	float asp = (float)m_width / (float)m_height;
	float t = 0.1f * std::tan(fov * 3.141592654 / 360.0f);
	float b = -t;
	float l = b * asp;
	float r = t * asp;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(l, r, b, t, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



void GlHelper::enableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}



void GlHelper::disableDepthTest()
{
	glDisable(GL_DEPTH_TEST);
}



void GlHelper::setEyes(const float posX, const float posY, const float posZ,
											 const float rotX, const float rotY, const float rotZ)
{
	glRotatef(-rotZ, 0.0f, 0.0f, 1.0f);
	glRotatef(-rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(-rotY, 0.0f, 1.0f, 0.0f);
	glTranslatef(-posX, -posY, -posZ);
}
