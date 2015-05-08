#include "HistoryTool.hpp"
#include "Voxels.hpp"



HistoryTool::HistoryTool(Voxels* voxels)
{
	m_voxels = voxels;
}



HistoryTool::~HistoryTool()
{
}



bool HistoryTool::keyPress(sf::Event::KeyEvent k)
{
	if (k.control && k.code == sf::Keyboard::Z)
	{
		m_voxels->undo();
		//if (m_voxels->getVoxelCount() == 0)
		//	m_voxels->add(0, 0, 0);
			
		return true;
	} else
	if (k.control && k.code == sf::Keyboard::Y)
	{
		m_voxels->redo();
		//if (m_voxels->getVoxelCount() == 0)
		//	m_voxels->add(0, 0, 0);
			
		return true;
	}
	
	return false;
}
