#include "PencilTool.hpp"
#include "VoxelsPicker.hpp"
#include "Voxels.hpp"
#include "App.hpp"
#include <SFML/OpenGL.hpp>



PencilTool::PencilTool(VoxelsPicker* picker)
{
	m_isEnabled = true;
	m_picker = picker;
	
	m_cubePreviewDl = glGenLists(1);
	glNewList(m_cubePreviewDl, GL_COMPILE);
		glBegin(GL_LINES);
			glColor3f(0.3f, 0.3f, 1.0f);
			float e = 0.05f;
			glVertex3f(0.0f - e, 1.0f + e, 0.0f - e); glVertex3f(1.0f + e, 1.0f + e, 0.0f - e);
			glVertex3f(0.0f - e, 1.0f + e, 0.0f - e); glVertex3f(0.0f - e, 0.0f - e, 0.0f - e);
			glVertex3f(0.0f - e, 1.0f + e, 0.0f - e); glVertex3f(0.0f - e, 1.0f + e, 1.0f + e);
			glVertex3f(1.0f + e, 1.0f + e, 1.0f + e); glVertex3f(0.0f - e, 1.0f + e, 1.0f + e);
			glVertex3f(1.0f + e, 1.0f + e, 1.0f + e); glVertex3f(1.0f + e, 0.0f - e, 1.0f + e);
			glVertex3f(1.0f + e, 1.0f + e, 1.0f + e); glVertex3f(1.0f + e, 1.0f + e, 0.0f - e);
			glVertex3f(1.0f + e, 0.0f - e, 0.0f - e); glVertex3f(0.0f - e, 0.0f - e, 0.0f - e);
			glVertex3f(1.0f + e, 0.0f - e, 0.0f - e); glVertex3f(1.0f + e, 1.0f + e, 0.0f - e);
			glVertex3f(1.0f + e, 0.0f - e, 0.0f - e);	glVertex3f(1.0f + e, 0.0f - e, 1.0f + e);
			glVertex3f(0.0f - e, 0.0f - e, 1.0f + e); glVertex3f(1.0f + e, 0.0f - e, 1.0f + e);
			glVertex3f(0.0f - e, 0.0f - e, 1.0f + e); glVertex3f(0.0f - e, 1.0f + e, 1.0f + e);
			glVertex3f(0.0f - e, 0.0f - e, 1.0f + e); glVertex3f(0.0f - e, 0.0f - e, 0.0f - e);
		glEnd();
	glEndList();
	
	m_cubeSelectDl = glGenLists(1);
	glNewList(m_cubeSelectDl, GL_COMPILE);
		glBegin(GL_LINES);
			glColor3f(1.0f, 0.6f, 0.0f);
			e = 0.05f;
			glVertex3f(0.0f - e, 1.0f + e, 0.0f - e); glVertex3f(1.0f + e, 1.0f + e, 0.0f - e);
			glVertex3f(0.0f - e, 1.0f + e, 0.0f - e); glVertex3f(0.0f - e, 0.0f - e, 0.0f - e);
			glVertex3f(0.0f - e, 1.0f + e, 0.0f - e); glVertex3f(0.0f - e, 1.0f + e, 1.0f + e);
			glVertex3f(1.0f + e, 1.0f + e, 1.0f + e); glVertex3f(0.0f - e, 1.0f + e, 1.0f + e);
			glVertex3f(1.0f + e, 1.0f + e, 1.0f + e); glVertex3f(1.0f + e, 0.0f - e, 1.0f + e);
			glVertex3f(1.0f + e, 1.0f + e, 1.0f + e); glVertex3f(1.0f + e, 1.0f + e, 0.0f - e);
			glVertex3f(1.0f + e, 0.0f - e, 0.0f - e); glVertex3f(0.0f - e, 0.0f - e, 0.0f - e);
			glVertex3f(1.0f + e, 0.0f - e, 0.0f - e); glVertex3f(1.0f + e, 1.0f + e, 0.0f - e);
			glVertex3f(1.0f + e, 0.0f - e, 0.0f - e);	glVertex3f(1.0f + e, 0.0f - e, 1.0f + e);
			glVertex3f(0.0f - e, 0.0f - e, 1.0f + e); glVertex3f(1.0f + e, 0.0f - e, 1.0f + e);
			glVertex3f(0.0f - e, 0.0f - e, 1.0f + e); glVertex3f(0.0f - e, 1.0f + e, 1.0f + e);
			glVertex3f(0.0f - e, 0.0f - e, 1.0f + e); glVertex3f(0.0f - e, 0.0f - e, 0.0f - e);
		glEnd();
	glEndList();
	
	m_isCurrentVoxValid = false;
	m_currentVox[0] = 0;
	m_currentVox[1] = 0;
	m_currentVox[2] = 0;
	
	m_isSelecting = false;
	
	m_mouseX = 0;
	m_mouseY = 0;
}



PencilTool::~PencilTool()
{
	glDeleteLists(m_cubePreviewDl, 1);
	glDeleteLists(m_cubeSelectDl, 1);
}



void PencilTool::draw()
{
	if (!isEnabled())
		return;

	// Draw the selected
	for (unsigned int i = 0; i < m_voxelsSelected.size(); i += 3)
	{
		float x = (float)m_voxelsSelected[i + 0];
		float y = (float)m_voxelsSelected[i + 1];
		float z = (float)m_voxelsSelected[i + 2];
		glTranslatef(x, y, z);
		
		glLineWidth(4.0f);
		glCallList(m_cubeSelectDl);
		
		glTranslatef(-x, -y, -z);
	}
	
	// Draw the current voxel
	if (m_isCurrentVoxValid)
	{
		float x = (float)m_currentVox[0];
		float y = (float)m_currentVox[1];
		float z = (float)m_currentVox[2];
		glTranslatef(x, y, z);
		
		glLineWidth(5.0f);
		glCallList(m_cubePreviewDl);
		
		glTranslatef(-x, -y, -z);
	}
}



bool PencilTool::mousePress(const int button)
{
	if (!isEnabled())
		return false;

	if (button != 0)
		return false;
		
	m_isSelecting = true;
	if (m_isCurrentVoxValid)
	{
		m_voxelsSelected.push_back(m_currentVox[0]);
		m_voxelsSelected.push_back(m_currentVox[1]);
		m_voxelsSelected.push_back(m_currentVox[2]);
	}
		
	return false;
}



void PencilTool::mouseRelease(const int button)
{
	if (!isEnabled())
		return;
		
	if (button != 0)
		return;

	m_isSelecting = false;
	
	if (m_voxelsSelected.size() != 0)
	{
		Voxels* voxels = m_picker->getVoxels();
		voxels->startBatch();
		for (unsigned int i = 0; i < m_voxelsSelected.size(); i += 3)
			voxels->add(m_voxelsSelected[i + 0], m_voxelsSelected[i + 1], m_voxelsSelected[i + 2]);
		voxels->endBatch();
		m_voxelsSelected.clear();
	}
	
	_updateCurrent();
}



bool PencilTool::mouseMove(const int x, const int y)
{
	if (!isEnabled())
		return false;

	m_mouseX = x;
	m_mouseY = y;
	_updateCurrent();
	
	if (m_isSelecting && m_isCurrentVoxValid)
	{
		bool alreadySelected = false;
		for (unsigned int i = 0; i < m_voxelsSelected.size(); i += 3)
		{
			if (m_voxelsSelected[i + 0] == m_currentVox[0] &&
					m_voxelsSelected[i + 1] == m_currentVox[1] &&
					m_voxelsSelected[i + 2] == m_currentVox[2])
			{
				alreadySelected = true;
				break;
			}
		}
		
		if (!alreadySelected)
		{
			m_voxelsSelected.push_back(m_currentVox[0]);
			m_voxelsSelected.push_back(m_currentVox[1]);
			m_voxelsSelected.push_back(m_currentVox[2]);
		}
	}
	
	return false;
}



void PencilTool::isEnabled(const bool enabled)
{
	m_isEnabled = enabled;
}



bool PencilTool::isEnabled() const
{
	return m_isEnabled;
}



void PencilTool::_updateCurrent()
{
	int index = m_picker->pick(m_mouseX, m_mouseY);
	if (index < 0)
	{
		m_isCurrentVoxValid = false;
		return;
	} else
		m_isCurrentVoxValid = true;
	
	int normal = m_picker->pickNormal(m_mouseX, m_mouseY, index);
	int x = m_picker->getVoxels()->getVoxelX(index);
	int y = m_picker->getVoxels()->getVoxelY(index);
	int z = m_picker->getVoxels()->getVoxelZ(index);
	if (normal == 1)
		z -= 1;
	else if (normal == 2)
		x += 1;
	else if (normal == 3)
		z += 1;
	else if (normal == 4)
		x -= 1;
	else if (normal == 5)
		y += 1;
	else if (normal == 6)
		y -= 1;
	
	m_currentVox[0] = x;
	m_currentVox[1] = y;
	m_currentVox[2] = z;
}
