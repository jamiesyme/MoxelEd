#pragma once

#include <vector>
#include "Drawer.hpp"
#include "Listener.hpp"
class VoxelsPicker;


class EraserTool : public Drawer, public Listener {
public:
	EraserTool(VoxelsPicker* picker);
	~EraserTool();
	
	virtual void draw();
	
	virtual bool mousePress(const int button);
	virtual void mouseRelease(const int button);
	virtual bool mouseMove(const int x, const int y);
	
	void isEnabled(const bool enabled);
	bool isEnabled() const;

private:
	bool m_isEnabled;
	VoxelsPicker* m_picker;
	unsigned int m_cubePreviewDl;
	unsigned int m_cubeSelectDl;
	std::vector<int> m_voxelsSelected;
	bool m_isCurrentVoxValid;
	int m_currentVox[3];
	bool m_isSelecting;
	int m_mouseX;
	int m_mouseY;
	
	void _updateCurrent();
};
