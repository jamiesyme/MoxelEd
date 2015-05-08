#pragma once


class GlHelper {
public:
	GlHelper();
	~GlHelper();

	void setWindowSize(const int width, const int height);
	
	void enableOrtho();
	void enablePersp(const float fov);
	
	void enableDepthTest();
	void disableDepthTest();
	
	void setEyes(const float posX, const float posY, const float posZ,
							 const float rotX, const float rotY, const float rotZ);

private:
	int m_width;
	int m_height;
};
