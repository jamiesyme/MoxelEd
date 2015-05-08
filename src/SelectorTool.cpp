#include "SelectorTool.hpp"
#include "VoxelsPicker.hpp"
#include "Voxels.hpp"
#include "App.hpp"
#include "WindowManager.hpp"
#include "Window.hpp"
#include "Button.hpp"
#include <SFML/OpenGL.hpp>



class Button_Fill : public Button {
public:
	Button_Fill(SelectorTool* t) { 
		setName("Fill"); 
		m_tool = t;
	}
	
private:
	SelectorTool* m_tool;
	void _pressCallback() { m_tool->fillSelection(); }
};

class Button_Erase : public Button {
public:
	Button_Erase(SelectorTool* t) { 
		setName("Erase"); 
		m_tool = t;
	}
	
private:
	SelectorTool* m_tool;
	void _pressCallback() { m_tool->eraseSelection(); }
};

class Button_SelectOutside : public Button {
public:
	Button_SelectOutside(SelectorTool* t) { 
		setName("Select Outside"); 
		m_tool = t;
	}
	
private:
	SelectorTool* m_tool;
	void _pressCallback() { m_tool->selectOutside(); }
};

class Button_SelectInside : public Button {
public:
	Button_SelectInside(SelectorTool* t) { 
		setName("Select Inside"); 
		m_tool = t;
	}
	
private:
	SelectorTool* m_tool;
	void _pressCallback() { m_tool->selectInside(); }
};



SelectorTool::SelectorTool(VoxelsPicker* picker, WindowManager* wm)
{
	// Create the window for the "fill" and "erase" tools
	m_window = wm->createWindow();
	m_window->setX(250);
	m_window->setTitle("Selector Actions");
	m_window->manageButton(new Button_Fill(this));
	m_window->manageButton(new Button_Erase(this));
	m_window->manageButton(new Button_SelectInside(this));
	m_window->manageButton(new Button_SelectOutside(this));

	// We are enabled by default
	m_isEnabled = true;
	
	// We pick the outside by default
	m_isSelectingInside = false;
	
	// Save the picker
	m_picker = picker;
	
	// Create our display lists
	m_cubeBlueDl = glGenLists(1);
	glNewList(m_cubeBlueDl, GL_COMPILE);
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
	
	m_cubeGreenDl = glGenLists(1);
	glNewList(m_cubeGreenDl, GL_COMPILE);
		glBegin(GL_LINES);
			glColor3f(0.2f, 8.0f, 0.2f);
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
	
	m_cubeOrangeDl = glGenLists(1);
	glNewList(m_cubeOrangeDl, GL_COMPILE);
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
	
	// Set up the current voxel
	m_isCurrentVoxValid = false;
	m_currentVox[0] = 0;
	m_currentVox[1] = 0;
	m_currentVox[2] = 0;
	
	// Set some other defaults
	m_isSelectingMulti = false;
	m_isSelectingExtra = false;
	m_mouseX = 0;
	m_mouseY = 0;
}



SelectorTool::~SelectorTool()
{
	glDeleteLists(m_cubeBlueDl, 1);
	glDeleteLists(m_cubeOrangeDl, 1);
}



void SelectorTool::draw()
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
		glCallList(m_cubeOrangeDl);
		
		glTranslatef(-x, -y, -z);
	}
	
	// Draw the previews 
	{
		std::vector<int> previewVoxels;
		_getPreviewVoxels(previewVoxels);
		for (unsigned int i = 0; i < previewVoxels.size(); i += 3)
		{
			float x = (float)previewVoxels[i + 0];
			float y = (float)previewVoxels[i + 1];
			float z = (float)previewVoxels[i + 2];
			glTranslatef(x, y, z);
		
			glLineWidth(4.0f);
			glCallList(m_cubeGreenDl);
		
			glTranslatef(-x, -y, -z);
		}
	}
	
	// Draw the current voxel
	if (m_isCurrentVoxValid)
	{
		float x = (float)m_currentVox[0];
		float y = (float)m_currentVox[1];
		float z = (float)m_currentVox[2];
		glTranslatef(x, y, z);
		
		glLineWidth(5.0f);
		glCallList(m_cubeBlueDl);
		
		glTranslatef(-x, -y, -z);
	}
}



void SelectorTool::mouseRelease(const int button)
{
	if (!isEnabled())
		return;
		
	if (button != 0)
		return;

	if ((!m_isSelectingMulti && !m_isSelectingExtra) || !m_isCurrentVoxValid)
	{
		m_voxelsSelected.clear();
	}
	
	if (m_isSelectingMulti && m_isCurrentVoxValid)
	{
		std::vector<int> previewVoxels;
		_getPreviewVoxels(previewVoxels);
		for (unsigned int i = 0; i < previewVoxels.size(); i += 3)
		{
			if (!_isVoxelSelected(previewVoxels[i + 0], previewVoxels[i + 1], previewVoxels[i + 2]))
			{
				m_voxelsSelected.push_back(previewVoxels[i + 0]);
				m_voxelsSelected.push_back(previewVoxels[i + 1]);
				m_voxelsSelected.push_back(previewVoxels[i + 2]);
			}
		}
		
		// Remove the current voxel from the selection 
		// (it will get added right afterwards, but at the end of the list)
		for (unsigned int i = 0; i < m_voxelsSelected.size(); i += 3)
		{
			if (m_voxelsSelected[i + 0] == m_currentVox[0] &&
					m_voxelsSelected[i + 1] == m_currentVox[1] &&
					m_voxelsSelected[i + 2] == m_currentVox[2])
			{
				m_voxelsSelected.erase(m_voxelsSelected.begin() + i, m_voxelsSelected.begin() + i + 3);
			}
		}
	}
	
	if (m_isCurrentVoxValid && !_isVoxelSelected(m_currentVox[0], m_currentVox[1], m_currentVox[2]))
	{
		m_voxelsSelected.push_back(m_currentVox[0]);
		m_voxelsSelected.push_back(m_currentVox[1]);
		m_voxelsSelected.push_back(m_currentVox[2]);
	}
	
	_updateCurrent();
}



bool SelectorTool::mouseMove(const int x, const int y)
{
	if (!isEnabled())
		return false;

	m_mouseX = x;
	m_mouseY = y;
	_updateCurrent();
	
	return false;
}



bool SelectorTool::keyPress(sf::Event::KeyEvent e)
{
	if (e.code == sf::Keyboard::LShift)
		m_isSelectingMulti = true;
	else
	if (e.code == sf::Keyboard::LControl)
		m_isSelectingExtra = true;
}



void SelectorTool::keyRelease(sf::Event::KeyEvent e)
{
	if (e.code == sf::Keyboard::LShift)
		m_isSelectingMulti = false;
	else
	if (e.code == sf::Keyboard::LControl)
		m_isSelectingExtra = false;
}



void SelectorTool::isEnabled(const bool enabled)
{
	m_isEnabled = enabled;
	m_window->isEnabled(enabled);
}



bool SelectorTool::isEnabled() const
{
	return m_isEnabled;
}



void SelectorTool::fillSelection()
{
	if (m_voxelsSelected.size() != 0)
	{
		Voxels* voxels = m_picker->getVoxels();
		voxels->startBatch();
		for (unsigned int i = 0; i < m_voxelsSelected.size(); i += 3)
		{
			voxels->add(m_voxelsSelected[i + 0],
									m_voxelsSelected[i + 1],
									m_voxelsSelected[i + 2]);
		}
		voxels->endBatch();
	}
}



void SelectorTool::eraseSelection()
{
	if (m_voxelsSelected.size() != 0)
	{
		Voxels* voxels = m_picker->getVoxels();
		voxels->startBatch();
		for (unsigned int i = 0; i < m_voxelsSelected.size(); i += 3)
		{
			voxels->remove(m_voxelsSelected[i + 0],
										 m_voxelsSelected[i + 1],
										 m_voxelsSelected[i + 2]);
		}
		voxels->endBatch();
		if (voxels->getVoxelCount() == 0)
			voxels->add(0, 0, 0);
	}
}



void SelectorTool::selectOutside()
{
	m_isSelectingInside = false;
	_updateCurrent();
}



void SelectorTool::selectInside()
{
	m_isSelectingInside = true;
	_updateCurrent();
}



void SelectorTool::_updateCurrent()
{
	int index = m_picker->pick(m_mouseX, m_mouseY);
	if (index < 0)
	{
		m_isCurrentVoxValid = false;
		return;
	} else
		m_isCurrentVoxValid = true;
	
	
	int x = m_picker->getVoxels()->getVoxelX(index);
	int y = m_picker->getVoxels()->getVoxelY(index);
	int z = m_picker->getVoxels()->getVoxelZ(index);
	if (!m_isSelectingInside)
	{
		int normal = m_picker->pickNormal(m_mouseX, m_mouseY, index);
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
	}
	
	m_currentVox[0] = x;
	m_currentVox[1] = y;
	m_currentVox[2] = z;
}



void SelectorTool::_getPreviewVoxels(std::vector<int>& voxels)
{
	if (m_voxelsSelected.size() == 0 || !m_isSelectingMulti || !m_isCurrentVoxValid)
		return;
		
	int startX = m_voxelsSelected[m_voxelsSelected.size() - 3];
	int startY = m_voxelsSelected[m_voxelsSelected.size() - 2];
	int startZ = m_voxelsSelected[m_voxelsSelected.size() - 1];
	int x1, x2, y1, y2, z1, z2;
	if (startX >= m_currentVox[0]) { x1 = m_currentVox[0]; x2 = startX; }
	else													 { x2 = m_currentVox[0]; x1 = startX; }
	if (startY >= m_currentVox[1]) { y1 = m_currentVox[1]; y2 = startY; }
	else													 { y2 = m_currentVox[1]; y1 = startY; }
	if (startZ >= m_currentVox[2]) { z1 = m_currentVox[2]; z2 = startZ; }
	else													 { z2 = m_currentVox[2]; z1 = startZ; }
	
	for (int x = x1; x <= x2; x++)
		for (int y = y1; y <= y2; y++)
			for (int z = z1; z <= z2; z++) {
				voxels.push_back(x);
				voxels.push_back(y);
				voxels.push_back(z);
			}
}



bool SelectorTool::_isVoxelSelected(int x, int y, int z)
{
	for (unsigned int i = 0; i < m_voxelsSelected.size(); i += 3)
	{
		if (m_voxelsSelected[i + 0] == x &&
				m_voxelsSelected[i + 1] == y &&
				m_voxelsSelected[i + 2] == z)
			return true;
	}
	return false;
}
