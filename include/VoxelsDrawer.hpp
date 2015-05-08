#pragma once

#include "Drawer.hpp"
class Voxels;


class VoxelsDrawer : public Drawer {
public:
	VoxelsDrawer(Voxels* voxels);
	~VoxelsDrawer();
	
	virtual void draw();

private:
	Voxels* m_voxels;
	unsigned int m_voxStamp;
	unsigned int m_voxDl;
};
