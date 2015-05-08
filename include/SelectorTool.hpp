#pragma once

#include <vector>
#include "Drawer.hpp"
#include "Listener.hpp"
class VoxelsPicker;
class WindowManager;
class Window;


class SelectorTool : public Drawer, public Listener {
public:
	SelectorTool(VoxelsPicker* picker, WindowManager* wm);
	~SelectorTool();
	
	virtual void draw();
	
	virtual void mouseRelease(const int button);
	virtual bool mouseMove(const int x, const int y);
	virtual bool keyPress(sf::Event::KeyEvent e);
	virtual void keyRelease(sf::Event::KeyEvent e);
	
	void isEnabled(const bool enabled);
	bool isEnabled() const;	
	
	void fillSelection();
	void eraseSelection();
	
	void selectOutside();
	void selectInside();
	
private:
	Window* m_window;
	bool m_isSelectingInside;
	bool m_isEnabled;
	VoxelsPicker* m_picker;
	unsigned int m_cubeBlueDl;
	unsigned int m_cubeOrangeDl;
	unsigned int m_cubeGreenDl;
	std::vector<int> m_voxelsSelected;
	bool m_isCurrentVoxValid;
	int m_currentVox[3];
	bool m_isSelectingMulti;
	bool m_isSelectingExtra;
	int m_mouseX;
	int m_mouseY;
	
	void _updateCurrent();
	void _getPreviewVoxels(std::vector<int>& voxels);
	bool _isVoxelSelected(int x, int y, int z);
};
