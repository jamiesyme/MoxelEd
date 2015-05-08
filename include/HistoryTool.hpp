#pragma once

#include "Listener.hpp"
class Voxels;


class HistoryTool : public Listener {
public:
	HistoryTool(Voxels* voxels);
	~HistoryTool();
	
	bool keyPress(sf::Event::KeyEvent k);

private:
	Voxels* m_voxels;
};
