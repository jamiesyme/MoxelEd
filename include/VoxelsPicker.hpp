#pragma once

class Camera;
class Voxels;


class VoxelsPicker {
public:
	VoxelsPicker(Camera* cam, Voxels* voxels);
	~VoxelsPicker();
	
	Camera* getCamera();
	Voxels* getVoxels();
	
	int pick(int mouseX, int mouseY);
	int pickNormal(int mouseX, int mouseY, int voxIndex);

private:
	Camera* m_cam;
	Voxels* m_voxels;
	unsigned int m_voxStamp;
	unsigned int m_voxDl;
	
	void _updateVoxelDl();
};
