#include "Voxels.hpp"
#include <iostream>



Voxels::Voxels()
{
	m_inBatch = false;
	m_historyIndex = 0;
	m_timestamp = 0;
	m_changeHistory.push_back(std::vector<VoxelChange>());
}



Voxels::~Voxels()
{
}



void Voxels::add(const int x, const int y, const int z)
{
	int index = findIndex(x, y, z);
	if (index >= 0)
		return;
		
	Voxel v;
	v.x = x;
	v.y = y;
	v.z = z;
	_add(v);
}



void Voxels::remove(const int x, const int y, const int z)
{
	int index = findIndex(x, y, z);
	if (index < 0)
		return;
		
	_remove(index);
}



void Voxels::removeAll()
{
	for (int i = (int)m_voxels.size() - 1; i >= 0; i--)
		remove(m_voxels[i].x, m_voxels[i].y, m_voxels[i].z);
}



void Voxels::startBatch()
{
	m_inBatch = true;
	
	// Overwrite history if the historyIndex is not current
	if (m_historyIndex + 1 != m_changeHistory.size())
	{
		m_changeHistory.erase(m_changeHistory.begin() + m_historyIndex + 1, m_changeHistory.end());
		m_changeHistory[m_historyIndex].clear();
	}
}



void Voxels::endBatch()
{
	if (!m_inBatch)
		return;
	m_inBatch = false;
	m_historyIndex++;
	m_changeHistory.push_back(std::vector<VoxelChange>());
}



void Voxels::undo()
{
	// We can't undo anything if our historyIndex is already 0
	if (m_historyIndex <= 0)
		return;
		
	// If a batch wasn't closed, do that now
	if (m_inBatch)
		endBatch();
		
	// Reduce the historyIndex and undo changes that happened in the previous batch
	m_historyIndex -= 1;
	for (int i = (int)m_changeHistory[m_historyIndex].size() - 1; i >= 0; i--)
	{
		VoxelChange vc = m_changeHistory[m_historyIndex][i];
		if (vc.type == 1)
		{
			int index = findIndex(vc.v.x, vc.v.y, vc.v.z);
			if (index == -1)
				std::cout << "VOXELS UNDO REMOVE ERROR" << std::endl;
			else
				m_voxels.erase(m_voxels.begin() + index);
		} else
		if (vc.type == 2)
		{
			m_voxels.push_back(vc.v);
		}
	}
	m_timestamp++;
}



void Voxels::redo()
{
	// We can't redo anything if our historyIndex is current
	if (m_historyIndex + 1 == m_changeHistory.size())
		return;
		
	// If a batch wasn't closed, do that now
	if (m_inBatch)
		endBatch();
		
	// Redo the changes that were undone, and increment the timestamp
	for (unsigned int i = 0; i < m_changeHistory[m_historyIndex].size(); i++)
	{
		VoxelChange vc = m_changeHistory[m_historyIndex][i];
		if (vc.type == 1)
			m_voxels.push_back(vc.v);
		else
		if (vc.type == 2)
		{
			int index = findIndex(vc.v.x, vc.v.y, vc.v.z);
			m_voxels.erase(m_voxels.begin() + index);
		}
	}
	m_timestamp++;
	m_historyIndex += 1;
}



unsigned int Voxels::getTimestamp() const
{
	return m_timestamp;
}



int Voxels::getVoxelX(const int index) const
{
	if (index < 0 || index >= (int)m_voxels.size())
		return 0;
	return m_voxels[index].x;
}



int Voxels::getVoxelY(const int index) const
{
	if (index < 0 || index >= (int)m_voxels.size())
		return 0;
	return m_voxels[index].y;
}



int Voxels::getVoxelZ(const int index) const
{
	if (index < 0 || index >= (int)m_voxels.size())
		return 0;
	return m_voxels[index].z;
}



int Voxels::getVoxelCount() const
{
	return (int)m_voxels.size();
}



int Voxels::findIndex(const int x, const int y, const int z) const
{
	for (unsigned int i = 0; i < m_voxels.size(); i++)
	{
		if (x == m_voxels[i].x &&
				y == m_voxels[i].y &&
				z == m_voxels[i].z)
			return (int)i;
	}
	return -1;
}



void Voxels::_add(const Voxel& v)
{
	// Add the voxel
	if (findIndex(v.x, v.y, v.z) != -1)
	{
		std::cout << "VOXELS ADD ERROR" << std::endl;
		return;
	}
	m_voxels.push_back(v);
	m_timestamp++;
	
	// Overwrite history if the historyIndex is not current
	if (m_historyIndex + 1 < m_changeHistory.size())
	{
		m_changeHistory.erase(m_changeHistory.begin() + m_historyIndex + 1, m_changeHistory.end());
		m_changeHistory[m_historyIndex].clear();
	}
	
	// Add the history
	VoxelChange vc;
	vc.v = v;
	vc.type = 1;
	m_changeHistory[m_historyIndex].push_back(vc);
	
	// If this is a batch, we don't need to increment the history
	if (m_inBatch)
		return;
		
	// This is just a single change, so increase the history
	m_historyIndex++;
	m_changeHistory.push_back(std::vector<VoxelChange>());
}



void Voxels::_remove(const int i)
{
	// Remove the voxel
	Voxel v;
	v.x = getVoxelX(i);
	v.y = getVoxelY(i);
	v.z = getVoxelZ(i);
	m_voxels.erase(m_voxels.begin() + i);
	m_timestamp++;
	
	// Overwrite history if the historyIndex is not current
	if (m_historyIndex + 1 != m_changeHistory.size())
	{
		m_changeHistory.erase(m_changeHistory.begin() + m_historyIndex + 1, m_changeHistory.end());
		m_changeHistory[m_historyIndex].clear();
	}
	
	// Add the history
	VoxelChange vc;
	vc.v = v;
	vc.type = 2;
	m_changeHistory[m_historyIndex].push_back(vc);
	
	// If this is a batch, we don't need to increment the history
	if (m_inBatch)
		return;
		
	// This is just a single change, so increase the history
	m_historyIndex++;
	m_changeHistory.push_back(std::vector<VoxelChange>());
}
