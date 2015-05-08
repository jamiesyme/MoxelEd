#pragma once

#include <string>
class Voxels;


class VoxelsExporter {
public:
	VoxelsExporter(Voxels* voxels);
	~VoxelsExporter();
	
	void exportPly(std::string name);

private:
	struct VoxRect { int x1, x2, y1, y2, z1, z2; };

	Voxels* m_voxels;
};
