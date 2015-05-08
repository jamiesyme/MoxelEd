#include "VoxelsExporter.hpp"
#include "Voxels.hpp"
#include "PerlinNoise.hpp"
#include <fstream>
#include <vector>



VoxelsExporter::VoxelsExporter(Voxels* voxels)
{
	m_voxels = voxels;
}



VoxelsExporter::~VoxelsExporter()
{
}



void VoxelsExporter::exportPly(std::string name)
{
	// Open the file
	std::ofstream file;
	file.open("export.ply");
	if (!file.is_open())
		return;
		
		
	// Calculate the voxel info
	std::vector<int> visibleVoxels;
	for (int i = 0; i < m_voxels->getVoxelCount(); i++)
	{
		int x = m_voxels->getVoxelX(i);
		int y = m_voxels->getVoxelY(i);
		int z = m_voxels->getVoxelZ(i);
		if (m_voxels->findIndex(x - 1, y, z) != -1 &&
				m_voxels->findIndex(x + 1, y, z) != -1 &&
				m_voxels->findIndex(x, y - 1, z) != -1 &&
				m_voxels->findIndex(x, y + 1, z) != -1 &&
				m_voxels->findIndex(x, y, z - 1) != -1 &&
				m_voxels->findIndex(x, y, z + 1) != -1)
			continue;
		visibleVoxels.push_back(x);
		visibleVoxels.push_back(y);
		visibleVoxels.push_back(z);
	}
	
	
	// Create the perlin noise
	PerlinNoise p(13);
	float ep = 3.314f;
	
	// Write the header info
	file << "ply\n";
	file << "format ascii 1.0\n";
	file << "element vertex " << visibleVoxels.size() / 3 * 8 << "\n";
	file << "property float x\n";
	file << "property float y\n";
	file << "property float z\n";
	file << "property float red\n";
	file << "property float green\n";
	file << "property float blue\n";
	file << "element face " << visibleVoxels.size() / 3 * 12 << "\n";
	file << "property list uchar int vertex_index\n";
	file << "end_header\n";
	for (unsigned int i = 0; i < visibleVoxels.size(); i += 3)
	{
		int x = visibleVoxels[i + 0];
		int y = visibleVoxels[i + 1];
		int z = visibleVoxels[i + 2];
		
		float px1 = (float)(x  ) / ep;
		float px2 = (float)(x+1) / ep;
		float py1 = (float)(y  ) / ep;
		float py2 = (float)(y+1) / ep;
		float pz1 = (float)(z  ) / ep;
		float pz2 = (float)(z+1) / ep;
		
		float n1 = p.gen(px1, py1, pz1) * 0.5f + 0.5f;
		float n2 = p.gen(px2, py1, pz1) * 0.5f + 0.5f;
		float n3 = p.gen(px2, py1, pz2) * 0.5f + 0.5f;
		float n4 = p.gen(px1, py1, pz2) * 0.5f + 0.5f;
		float n5 = p.gen(px1, py2, pz1) * 0.5f + 0.5f;
		float n6 = p.gen(px2, py2, pz1) * 0.5f + 0.5f;
		float n7 = p.gen(px2, py2, pz2) * 0.5f + 0.5f;
		float n8 = p.gen(px1, py2, pz2) * 0.5f + 0.5f;
		
		file << x + 0 << " " << y + 0 << " " << z + 0 << " ";
		file << n1    << " " << n1    << " " << n1    << "\n";
		file << x + 1 << " " << y + 0 << " " << z + 0 << " ";
		file << n2    << " " << n2    << " " << n2    << "\n";
		file << x + 1 << " " << y + 0 << " " << z + 1 << " ";
		file << n3    << " " << n3    << " " << n3    << "\n";
		file << x + 0 << " " << y + 0 << " " << z + 1 << " ";
		file << n4    << " " << n4    << " " << n4    << "\n";
		file << x + 0 << " " << y + 1 << " " << z + 0 << " ";
		file << n5    << " " << n5    << " " << n5    << "\n";
		file << x + 1 << " " << y + 1 << " " << z + 0 << " ";
		file << n6    << " " << n6    << " " << n6    << "\n";
		file << x + 1 << " " << y + 1 << " " << z + 1 << " ";
		file << n7    << " " << n7    << " " << n7    << "\n";
		file << x + 0 << " " << y + 1 << " " << z + 1 << " ";
		file << n8    << " " << n8    << " " << n8    << "\n";
	}
	for (unsigned int i = 0; i < visibleVoxels.size(); i += 3)
	{
		int vi = i / 3 * 8;
		file << "3 " << vi + 0 << " " << vi + 1 << " " << vi + 5 << "\n";
		file << "3 " << vi + 5 << " " << vi + 4 << " " << vi + 0 << "\n";
		file << "3 " << vi + 1 << " " << vi + 2 << " " << vi + 6 << "\n";
		file << "3 " << vi + 6 << " " << vi + 5 << " " << vi + 1 << "\n";
		file << "3 " << vi + 2 << " " << vi + 3 << " " << vi + 7 << "\n";
		file << "3 " << vi + 7 << " " << vi + 6 << " " << vi + 2 << "\n";
		file << "3 " << vi + 3 << " " << vi + 0 << " " << vi + 4 << "\n";
		file << "3 " << vi + 4 << " " << vi + 7 << " " << vi + 3 << "\n";
		file << "3 " << vi + 0 << " " << vi + 3 << " " << vi + 2 << "\n";
		file << "3 " << vi + 2 << " " << vi + 1 << " " << vi + 0 << "\n";
		file << "3 " << vi + 4 << " " << vi + 5 << " " << vi + 6 << "\n";
		file << "3 " << vi + 6 << " " << vi + 7 << " " << vi + 4 << "\n";
	}
	
	// Close the file
	file.close();
}
