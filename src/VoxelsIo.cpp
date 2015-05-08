#include "VoxelsIo.hpp"
#include "Voxels.hpp"
#include <fstream>
#include <sstream>



VoxelsIo::VoxelsIo(Voxels* voxels)
{
	m_voxels = voxels;
}



VoxelsIo::~VoxelsIo()
{
}



void VoxelsIo::save(std::string filename)
{
	// Open the file
	std::ofstream file;
	file.open("export.vox");
	if (!file.is_open())
		return;
	
	// Save all the voxels to the file
	for (int i = 0; i < m_voxels->getVoxelCount(); i++)
	{
		file << m_voxels->getVoxelX(i) << " ";
		file << m_voxels->getVoxelY(i) << " ";
		file << m_voxels->getVoxelZ(i) << " ";
	}
	
	// Remember to close the file
	file.close();
}



void VoxelsIo::load(std::string filename)
{
	// Open the file
	std::ifstream file;
	file.open("export.vox");
	if (!file.is_open())
		return;
	
	// Remove all the current voxels
	m_voxels->removeAll();
	
	// Load the voxels from the file
	std::string curNumStr = "";
	int x = 0;
	int y = 0;
	int z = 0;
	int coordCount = 0;
	while (file.good())
	{
		char c = file.get();
		if (c != ' ')
			curNumStr += c;
		else
		{
			// We hit a space, so we have collected a number now
			int num = 0;
			std::stringstream ss(curNumStr);
			ss >> num;
			curNumStr.clear();
			
			// Depending on the coord count, we know which number this is
			if (coordCount == 0)
				x = num;
			else if (coordCount == 1)
				y = num;
			else if (coordCount == 2) {
				z = num;
				
				// We have all the coordinates for this voxel
				m_voxels->add(x, y, z);
			}
			
			// Increase the coord count (and wrap)
			coordCount++;
			if (coordCount > 2)
				coordCount = 0;
		}
	}
	
	// Don't forget to close the file
	file.close();
}
