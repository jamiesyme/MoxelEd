#pragma once

class App;
class Camera;
class Voxels;
class VoxelsDrawer;
class VoxelsPicker;
class PencilTool;
class EraserTool;
class SelectorTool;
class HistoryTool;
class WindowManager;


class Editor {
public:
	Editor(App* app);
	~Editor();
	
	void useTool_pencil();
	void useTool_eraser();
	void useTool_selector();

private:
	App* m_app;
	Camera* m_cam;
	Voxels* m_voxels;
	VoxelsDrawer* m_voxelDraw;
	VoxelsPicker* m_voxelPick;
	WindowManager* m_wm;
	PencilTool* m_pencil;
	EraserTool* m_eraser;
	SelectorTool* m_selector;
	HistoryTool* m_history;
};
