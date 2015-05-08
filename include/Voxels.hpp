#pragma once

#include <vector>


class Voxels {
public:
	Voxels();
	~Voxels();
	
	void add(const int x, const int y, const int z);
	void remove(const int x, const int y, const int z);
	void removeAll();
	
	void startBatch();
	void endBatch();
	
	void undo();
	void redo();
	
	unsigned int getTimestamp() const;
	
	int getVoxelX(const int index) const;
	int getVoxelY(const int index) const;
	int getVoxelZ(const int index) const;
	int getVoxelCount() const;
	
	int findIndex(const int x, const int y, const int z) const;
	
private:
	struct Voxel { int x, y, z; };
	struct VoxelChange { int type; Voxel v; }; // type == 0: add. type == 1: remove.
	
	bool m_inBatch;
	std::vector<Voxel> m_voxels;
	std::vector<std::vector<VoxelChange>> m_changeHistory;
	unsigned int m_historyIndex;
	unsigned int m_timestamp;
	
	void _add(const Voxel& v);
	void _remove(const int i);
};
