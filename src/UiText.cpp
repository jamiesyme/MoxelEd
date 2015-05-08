#include "UiText.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>



UiText::UiText()
{
	m_isDirty = true;
	m_anchor = BOT_LEFT;
	m_posX = 0;
	m_posY = 0;
	m_sizeX = 0;
	m_sizeY = 0;
	m_textColorR = 0;
	m_textColorG = 0;
	m_textColorB = 0;
	m_textColorA = 255;
	m_textSize = 16;
	m_text = "Default Text";
	m_fontFilename = "";
	m_texture = new sf::Texture();
}



UiText::~UiText()
{
	delete m_texture;
	//SDL_DestroyTexture(m_texture);
}



void UiText::Draw()
{
	if (m_texture == 0)
		return;
	if (m_isDirty)
		_reloadText();
	glEnable(GL_TEXTURE_2D);
	sf::Texture::bind(m_texture);
	glColor4ub(GetTextColorR(), GetTextColorG(), GetTextColorB(), GetTextColorA());
	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(GetPositionX1(), GetPositionY1()); 
		glTexCoord2f(1.0f, 1.0f); glVertex2i(GetPositionX2(), GetPositionY1()); 
		glTexCoord2f(1.0f, 0.0f); glVertex2i(GetPositionX2(), GetPositionY2()); 
		glTexCoord2f(1.0f, 0.0f); glVertex2i(GetPositionX2(), GetPositionY2()); 
		glTexCoord2f(0.0f, 0.0f); glVertex2i(GetPositionX1(), GetPositionY2()); 
		glTexCoord2f(0.0f, 1.0f); glVertex2i(GetPositionX1(), GetPositionY1()); 
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//SDL_Rect src = { 0, 0, GetSizeX(), GetSizeY() };
	//SDL_Rect dst = { GetPositionX1(), GetPositionY1(), GetSizeX(), GetSizeY() };
	//SDL_SetTextureColorMod(m_texture, GetTextColorR(), GetTextColorG(), GetTextColorB());
	//SDL_SetTextureAlphaMod(m_texture, GetTextColorA());
	//SDL_RenderCopy(Window::GetRenderer(), m_texture, &src, &dst);
}



void UiText::SetCenterPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
	m_anchor = CENTER;
}



void UiText::SetCenterLeftPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
	m_anchor = CENTER_LEFT;
}



void UiText::SetCenterRightPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
	m_anchor = CENTER_RIGHT;
}



void UiText::SetTopLeftPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
	m_anchor = TOP_LEFT;
}



void UiText::SetTopRightPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
	m_anchor = TOP_RIGHT;
}



void UiText::SetBottomLeftPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
	m_anchor = BOT_LEFT;
}



void UiText::SetBottomRightPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
	m_anchor = BOT_RIGHT;
}



void UiText::SetFont(std::string fontFilename)
{
	m_fontFilename = fontFilename;
	m_isDirty = true;
}



void UiText::SetText(std::string text)
{
	m_text = text;
	m_isDirty = true;
}



void UiText::SetTextSize(int point)
{
	m_textSize = point;
	m_isDirty = true;
}



void UiText::SetTextColor(int r, int g, int b, int a)
{
	m_textColorR = r;
	m_textColorG = g;
	m_textColorB = b;
	m_textColorA = a;
}



void UiText::SetTextColorR(int r)
{
	m_textColorR = r;
}



void UiText::SetTextColorG(int g)
{
	m_textColorG = g;
}



void UiText::SetTextColorB(int b)
{
	m_textColorB = b;
}



void UiText::SetTextColorA(int a)
{
	m_textColorA = a;
}



int UiText::GetPositionX1() const
{
	if (m_anchor == BOT_LEFT || m_anchor == TOP_LEFT || m_anchor == CENTER_LEFT)
		return m_posX;
	if (m_anchor == BOT_RIGHT || m_anchor == TOP_RIGHT || m_anchor == CENTER_RIGHT)
		return m_posX - GetSizeX() + 1;
	return m_posX - GetSizeX() / 2;
}



int UiText::GetPositionX2() const
{
	if (m_anchor == BOT_LEFT || m_anchor == TOP_LEFT || m_anchor == CENTER_LEFT)
		return m_posX + GetSizeX() - 1;
	if (m_anchor == BOT_RIGHT || m_anchor == TOP_RIGHT || m_anchor == CENTER_RIGHT)
		return m_posX;
	return m_posX + GetSizeX() / 2;
}



int UiText::GetPositionY1() const
{
	if (m_anchor == BOT_LEFT || m_anchor == BOT_RIGHT)
		return m_posY;
	if (m_anchor == TOP_LEFT || m_anchor == TOP_RIGHT)
		return m_posY - GetSizeY() + 1;
	return m_posY - GetSizeY() / 2;
}



int UiText::GetPositionY2() const
{
	if (m_anchor == BOT_LEFT || m_anchor == BOT_RIGHT)
		return m_posY + GetSizeY() - 1;
	if (m_anchor == TOP_LEFT || m_anchor == TOP_RIGHT)
		return m_posY;
	return m_posY + GetSizeY() / 2;
}



int UiText::GetSizeX() const
{
	return m_sizeX;
}



int UiText::GetSizeY() const
{
	return m_sizeY;
}



int UiText::GetTextColorR() const
{
	return m_textColorR;
}



int UiText::GetTextColorG() const
{
	return m_textColorG;
}



int UiText::GetTextColorB() const
{
	return m_textColorB;
}



int UiText::GetTextColorA() const
{
	return m_textColorA;
}


int UiText::GetTextSize() const
{
	return m_textSize;
}



std::string UiText::GetText() const
{
	return m_text;
}



std::string UiText::GetFont() const
{
	return m_fontFilename;
}



void UiText::_reloadText()
{
	if (m_fontFilename.size() == 0)
		return;
	
	// Load the font
	sf::Font font;
	if (!font.loadFromFile(m_fontFilename)) {
		std::cout << "Font '" << m_fontFilename.c_str() << "' failed to load!" << std::endl;
		return; 
	}
	
	// Create the text
	sf::Text text;
	text.setString(m_text);
	text.setCharacterSize(m_textSize);
	text.setColor(sf::Color::White);
	text.setFont(font);
	text.setOrigin(text.getLocalBounds().left, text.getLocalBounds().top);
	
	// Save the size
	m_sizeX = (int)text.getLocalBounds().width;
	m_sizeY = (int)text.getLocalBounds().height;
	
	// Create the SFML image
	sf::RenderTexture rTexture;
	rTexture.create(m_sizeX, m_sizeY);
	rTexture.clear(sf::Color::Transparent);
	rTexture.draw(text);
	*m_texture = rTexture.getTexture();
	
	// We are clean now
	m_isDirty = false;
	
	/*TTF_Font* font = TTF_OpenFont(m_fontFilename.c_str(), m_textSize);
	if (font == 0) {
		std::cout << "Font '" << m_fontFilename.c_str() << "' failed to load!" << std::endl;
		std::cout << "\t: " << TTF_GetError() << std::endl;
		return;
	}
		
	SDL_Color col = { 255, 255, 255, 255 };
	//col.r = GetTextColorR();
	//col.g = GetTextColorG();
	//col.b = GetTextColorB();
	//col.a = GetTextColorA();
	SDL_Surface* surf = TTF_RenderUTF8_Blended(font, m_text.c_str(), col);
	
	if (surf != 0) 
	{
		SDL_DestroyTexture(m_texture);
		m_texture = SDL_CreateTextureFromSurface(Window::GetRenderer(), surf);
		SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
		
		m_sizeX = surf->w;
		m_sizeY = surf->h;
		
		SDL_FreeSurface(surf);	
	}
	
	TTF_CloseFont(font);*/
}
