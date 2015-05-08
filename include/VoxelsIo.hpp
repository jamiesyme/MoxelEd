#pragma once

#include <string>
class Voxels;


class VoxelsIo {
public:
	VoxelsIo(Voxels* voxels);
	~VoxelsIo();
	
	void save(std::string filename);
	void load(std::string filename);

private:
	Voxels* m_voxels;
};
