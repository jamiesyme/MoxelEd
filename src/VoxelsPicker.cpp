#include "VoxelsPicker.hpp"
#include "Camera.hpp"
#include "Voxels.hpp"
#include <SFML/OpenGL.hpp>



VoxelsPicker::VoxelsPicker(Camera* cam, Voxels* voxels)
{
	m_cam = cam;
	m_voxels = voxels;
	m_voxStamp = 0;
	m_voxDl = glGenLists(1);
}



VoxelsPicker::~VoxelsPicker()
{
	glDeleteLists(1, m_voxDl);
}



Camera* VoxelsPicker::getCamera()
{
	return m_cam;
}



Voxels* VoxelsPicker::getVoxels()
{
	return m_voxels;
}



int VoxelsPicker::pick(int mouseX, int mouseY)
{
	_updateVoxelDl();
	
	int viewport[] = {0,0,0,0};
	glGetIntegerv(GL_VIEWPORT, viewport);
	glEnable(GL_SCISSOR_TEST);
	glScissor(mouseX, viewport[3] - 1 - mouseY, 1, 1);

	m_cam->draw();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glCallList(m_voxDl);
	
	unsigned char pixel[3];
	glReadPixels(mouseX, viewport[3] - 1 - mouseY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
	int index = pixel[0] * 256 * 256 + pixel[1] * 256 + pixel[2] - 1;

	glDisable(GL_SCISSOR_TEST);
	
	return index;
}



int VoxelsPicker::pickNormal(int mouseX, int mouseY, int index)
{
	_updateVoxelDl();
	
	int viewport[] = {0,0,0,0};
	glGetIntegerv(GL_VIEWPORT, viewport);
	glEnable(GL_SCISSOR_TEST);
	glScissor(mouseX, viewport[3] - 1 - mouseY, 1, 1);

	m_cam->draw();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	float x1 = (float)m_voxels->getVoxelX(index);
	float y1 = (float)m_voxels->getVoxelY(index);
	float z1 = (float)m_voxels->getVoxelZ(index);
	float x2 = x1 + 1;
	float y2 = y1 + 1;
	float z2 = z1 + 1;
	
	glBegin(GL_TRIANGLES);
	glColor3ub(0, 0, 1);
		glVertex3f(x1, y1, z1); glVertex3f(x2, y1, z1); glVertex3f(x2, y2, z1);
		glVertex3f(x2, y2, z1); glVertex3f(x1, y2, z1); glVertex3f(x1, y1, z1);
	glColor3ub(0, 0, 2);
		glVertex3f(x2, y1, z1); glVertex3f(x2, y1, z2); glVertex3f(x2, y2, z2);
		glVertex3f(x2, y2, z2); glVertex3f(x2, y2, z1); glVertex3f(x2, y1, z1);
	glColor3ub(0, 0, 3);
		glVertex3f(x2, y1, z2); glVertex3f(x1, y1, z2); glVertex3f(x1, y2, z2);
		glVertex3f(x1, y2, z2); glVertex3f(x2, y2, z2); glVertex3f(x2, y1, z2);
	glColor3ub(0, 0, 4);
		glVertex3f(x1, y1, z2); glVertex3f(x1, y1, z1); glVertex3f(x1, y2, z1);
		glVertex3f(x1, y2, z1); glVertex3f(x1, y2, z2); glVertex3f(x1, y1, z2);
	glColor3ub(0, 0, 5);
		glVertex3f(x1, y2, z1); glVertex3f(x2, y2, z1); glVertex3f(x2, y2, z2);
		glVertex3f(x2, y2, z2); glVertex3f(x1, y2, z2); glVertex3f(x1, y2, z1);
	glColor3ub(0, 0, 6);
		glVertex3f(x1, y1, z1); glVertex3f(x1, y1, z2); glVertex3f(x2, y1, z2);
		glVertex3f(x2, y1, z2); glVertex3f(x2, y1, z1); glVertex3f(x1, y1, z1);
	glEnd();
	
	unsigned char pixel[3];
	glReadPixels(mouseX, viewport[3] - 1 - mouseY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

	glDisable(GL_SCISSOR_TEST);
	
	return pixel[2];
}



void VoxelsPicker::_updateVoxelDl()
{
	if (m_voxels->getTimestamp() == m_voxStamp)
		return;
	glNewList(m_voxDl, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < m_voxels->getVoxelCount(); i++)
	{
		int id = i + 1;
		unsigned char b = id % 256;
		unsigned char g = std::min((int)((float)id / 256), 255);
		unsigned char r = std::min((int)((float)id / 256 / 256), 255);
		glColor3ub(r, g, b);
	
		float x = (float)m_voxels->getVoxelX(i);
		float y = (float)m_voxels->getVoxelY(i);
		float z = (float)m_voxels->getVoxelZ(i);
		glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f); glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f); glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f);
		glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f); glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f); glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f);
		glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f); glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f); glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);
		glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f); glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f); glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f);
		glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f); glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f); glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f);
		glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f); glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f); glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f);
		glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f); glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f); glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
		glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f); glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f); glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f);
		glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f); glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f); glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);
		glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f); glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f); glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
		glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f); glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f); glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f);
		glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f); glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f); glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f);
	}
	glEnd();
	glEndList();
	
	m_voxStamp = m_voxels->getTimestamp();
}
