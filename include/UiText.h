#pragma once

#include <string>
namespace sf { class Texture; }


class UiText {
	enum Anchor {
		TOP_LEFT = 1,
		TOP_RIGHT,
		BOT_LEFT,
		BOT_RIGHT,
		CENTER,
		CENTER_LEFT,
		CENTER_RIGHT
	};	
	
public:
	UiText();
	~UiText();
	
	void Draw();
	
	void SetCenterPosition(int x, int y);
	void SetCenterLeftPosition(int x, int y);
	void SetCenterRightPosition(int x, int y);
	void SetTopLeftPosition(int x, int y);
	void SetTopRightPosition(int x, int y);
	void SetBottomLeftPosition(int x, int y);
	void SetBottomRightPosition(int x, int y);
	
	void SetFont(std::string fontFilename);
	void SetText(std::string text);
	void SetTextSize(int point);
	void SetTextColor(int r, int g, int b, int a);
	void SetTextColorR(int r);
	void SetTextColorG(int g);
	void SetTextColorB(int b);
	void SetTextColorA(int a);
	
	int GetPositionX1() const;
	int GetPositionX2() const;
	int GetPositionY1() const;
	int GetPositionY2() const;
	int GetSizeX() const;
	int GetSizeY() const;
	
	int GetTextColorR() const;
	int GetTextColorG() const;
	int GetTextColorB() const;
	int GetTextColorA() const;
	int GetTextSize() const;
	std::string GetText() const;
	std::string GetFont() const;

private:
	bool m_isDirty;
	int m_anchor; // 1 = bl, 2 = br, 3 = tl, 4 = tr, 5 = c
	int m_posX;
	int m_posY;
	int m_sizeX;
	int m_sizeY;
	int m_textColorR;
	int m_textColorG;
	int m_textColorB;
	int m_textColorA;
	int m_textSize;
	std::string m_text;
	std::string m_fontFilename;
	sf::Texture* m_texture;
	
	void _reloadText();
};
