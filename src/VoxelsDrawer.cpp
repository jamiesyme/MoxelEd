#include "VoxelsDrawer.hpp"
#include "Voxels.hpp"
#include <SFML/OpenGL.hpp>



VoxelsDrawer::VoxelsDrawer(Voxels* voxels)
{
	m_voxels = voxels;
	m_voxStamp = 0;
	m_voxDl = glGenLists(1);
}



VoxelsDrawer::~VoxelsDrawer()
{
	glDeleteLists(m_voxDl, 1);
}



void VoxelsDrawer::draw()
{
	if (m_voxStamp != m_voxels->getTimestamp())
	{
		glNewList(m_voxDl, GL_COMPILE);
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < m_voxels->getVoxelCount(); i++)
		{
			float x = (float)m_voxels->getVoxelX(i);
			float y = (float)m_voxels->getVoxelY(i);
			float z = (float)m_voxels->getVoxelZ(i);
				glColor3f(0.9f, 0.9f, 0.9f);
			glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f); glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f); glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f);
			glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f); glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f); glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f);
				glColor3f(0.8f, 0.8f, 0.8f);
			glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f); glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f); glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);
			glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f); glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f); glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f);
				glColor3f(0.9f, 0.9f, 0.9f);
			glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f); glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f); glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f);
			glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f); glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f); glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f);
				glColor3f(0.8f, 0.8f, 0.8f);
			glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f); glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f); glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
			glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f); glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f); glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f);
				glColor3f(0.7f, 0.7f, 0.7f);
			glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f); glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f); glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);
			glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f); glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f); glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
			glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f); glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f); glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f);
			glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f); glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f); glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f);
		}
		glEnd();
		glColor3f(0.2f, 0.2f, 0.2f);
		glBegin(GL_LINES);
		for (int i = 0; i < m_voxels->getVoxelCount(); i++)
		{
			float x = (float)m_voxels->getVoxelX(i);
			float y = (float)m_voxels->getVoxelY(i);
			float z = (float)m_voxels->getVoxelZ(i);
			float e = 0.025f;
			glVertex3f(x + 0.0f - e, y + 1.0f + e, z + 0.0f - e); glVertex3f(x + 1.0f + e, y + 1.0f + e, z + 0.0f - e);
			glVertex3f(x + 0.0f - e, y + 1.0f + e, z + 0.0f - e); glVertex3f(x + 0.0f - e, y + 0.0f - e, z + 0.0f - e);
			glVertex3f(x + 0.0f - e, y + 1.0f + e, z + 0.0f - e); glVertex3f(x + 0.0f - e, y + 1.0f + e, z + 1.0f + e);
			glVertex3f(x + 1.0f + e, y + 1.0f + e, z + 1.0f + e); glVertex3f(x + 0.0f - e, y + 1.0f + e, z + 1.0f + e);
			glVertex3f(x + 1.0f + e, y + 1.0f + e, z + 1.0f + e); glVertex3f(x + 1.0f + e, y + 0.0f - e, z + 1.0f + e);
			glVertex3f(x + 1.0f + e, y + 1.0f + e, z + 1.0f + e); glVertex3f(x + 1.0f + e, y + 1.0f + e, z + 0.0f - e);
			glVertex3f(x + 1.0f + e, y + 0.0f - e, z + 0.0f - e); glVertex3f(x + 0.0f - e, y + 0.0f - e, z + 0.0f - e);
			glVertex3f(x + 1.0f + e, y + 0.0f - e, z + 0.0f - e); glVertex3f(x + 1.0f + e, y + 1.0f + e, z + 0.0f - e);
			glVertex3f(x + 1.0f + e, y + 0.0f - e, z + 0.0f - e);	glVertex3f(x + 1.0f + e, y + 0.0f - e, z + 1.0f + e);
			glVertex3f(x + 0.0f - e, y + 0.0f - e, z + 1.0f + e); glVertex3f(x + 1.0f + e, y + 0.0f - e, z + 1.0f + e);
			glVertex3f(x + 0.0f - e, y + 0.0f - e, z + 1.0f + e); glVertex3f(x + 0.0f - e, y + 1.0f + e, z + 1.0f + e);
			glVertex3f(x + 0.0f - e, y + 0.0f - e, z + 1.0f + e); glVertex3f(x + 0.0f - e, y + 0.0f - e, z + 0.0f - e);
		}
		glEnd();
		glEndList();
		
		m_voxStamp = m_voxels->getTimestamp();
	}
	
	glLineWidth(2.0f);
	glCallList(m_voxDl);
}
