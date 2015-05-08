#include "Editor.hpp"
#include "App.hpp"
#include "Camera.hpp"
#include "Voxels.hpp"
#include "VoxelsIo.hpp"
#include "VoxelsExporter.hpp"
#include "VoxelsDrawer.hpp"
#include "VoxelsPicker.hpp"
#include "PencilTool.hpp"
#include "EraserTool.hpp"
#include "SelectorTool.hpp"
#include "HistoryTool.hpp"
#include "WindowManager.hpp"
#include "Window.hpp"
#include "Button.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>



class Button_Pencil : public Button {
public:
	Button_Pencil(Editor* ed) { 
		setName("Pencil"); 
		m_ed = ed; 
	}
	
private:
	Editor* m_ed;
	void _pressCallback() { m_ed->useTool_pencil(); }
};

class Button_Eraser : public Button {
public:
	Button_Eraser(Editor* ed) { 
		setName("Eraser"); 
		m_ed = ed; 
	}
	
private:
	Editor* m_ed;
	void _pressCallback() { m_ed->useTool_eraser(); }
};

class Button_Selector : public Button {
public:
	Button_Selector(Editor* ed) {
		setName("Selector");
		m_ed = ed;
	}
	
private:
	Editor* m_ed;
	void _pressCallback() { m_ed->useTool_selector(); }
};

class Button_SaveVox : public Button {
public:
	Button_SaveVox(Voxels* v) {
		setName("Save as .vox");
		m_v = v;
	}	
	
private:
	Voxels* m_v;
	void _pressCallback() 
	{ 
		VoxelsIo io(m_v);
		io.save("export.vox");
	}
};

class Button_OpenVox : public Button {
public:
	Button_OpenVox(Voxels* v) {
		setName("Open a .vox");
		m_v = v;
	}	
	
private:
	Voxels* m_v;
	void _pressCallback() 
	{ 
		VoxelsIo io(m_v);
		io.load("export.vox");
	}
};

class Button_ExportPly : public Button {
public:
	Button_ExportPly(Voxels* v) {
		setName("Export as .ply");
		m_v = v;
	}	
	
private:
	Voxels* m_v;
	void _pressCallback() 
	{ 
		VoxelsExporter ex(m_v);
		ex.exportPly("export.ply");
	}
};



Editor::Editor(App* app)
{
	m_app = app;
	m_cam = new Camera(m_app);
	m_cam->setOriginX(2.0f);
	m_cam->setOriginY(2.0f);
	m_cam->setOriginZ(2.0f);
	m_cam->setRotationY(225.0f);
	m_cam->setRotationX(-20.0f);
	m_cam->setRadius(10.0f);
	m_cam->isRotationLocked(true);
	m_cam->isPositionLocked(true);
	
	m_voxels = new Voxels();
	for (int x = 0; x < 1; x++)
		for (int y = 0; y < 1; y++)
			for (int z = 0; z < 1; z++)
				m_voxels->add(x, y, z);
	m_voxelDraw = new VoxelsDrawer(m_voxels);
	m_voxelPick = new VoxelsPicker(m_cam, m_voxels);
				
	m_wm = new WindowManager(m_app);
	Window* toolsWindow = m_wm->createWindow();
	toolsWindow->setTitle("Tools");
	toolsWindow->manageButton(new Button_Pencil(this));
	toolsWindow->manageButton(new Button_Eraser(this));
	toolsWindow->manageButton(new Button_Selector(this));
	Window* fileWindow = m_wm->createWindow();
	fileWindow->setTitle("File");
	fileWindow->manageButton(new Button_SaveVox(m_voxels));
	fileWindow->manageButton(new Button_OpenVox(m_voxels));
	fileWindow->manageButton(new Button_ExportPly(m_voxels));
	
	m_pencil = new PencilTool(m_voxelPick);
	m_eraser = new EraserTool(m_voxelPick);
	m_selector = new SelectorTool(m_voxelPick, m_wm);
	m_history = new HistoryTool(m_voxels);
	
	m_app->addListener(m_wm, 10);
	m_app->addListener(m_cam, 15);
	m_app->addListener(m_history, 19);
	m_app->addListener(m_pencil, 20);
	m_app->addListener(m_eraser, 20);
	m_app->addListener(m_selector, 20);
	m_app->addDrawer(m_cam, 1);
	m_app->addDrawer(m_voxelDraw, 10);
	m_app->addDrawer(m_pencil, 15);
	m_app->addDrawer(m_eraser, 15);
	m_app->addDrawer(m_selector, 20);
	m_app->addDrawer(m_wm, 100);
	
	useTool_pencil();
}



Editor::~Editor()
{
	delete m_pencil;
	delete m_eraser;
	delete m_selector;
	delete m_history;
	delete m_cam;
	delete m_voxels;
	delete m_voxelDraw;
	delete m_voxelPick;
	delete m_wm;
}



void Editor::useTool_pencil() 
{ 
	m_pencil->isEnabled(true);
	m_eraser->isEnabled(false);
	m_selector->isEnabled(false);
}



void Editor::useTool_eraser() 
{ 
	m_pencil->isEnabled(false);
	m_eraser->isEnabled(true);
	m_selector->isEnabled(false);
}



void Editor::useTool_selector() 
{ 
	m_pencil->isEnabled(false);
	m_eraser->isEnabled(false);
	m_selector->isEnabled(true);
}
