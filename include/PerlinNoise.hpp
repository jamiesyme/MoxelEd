#pragma once


class PerlinNoise {
public:
	PerlinNoise(const int seed);
	~PerlinNoise();
	
	float gen(float x, float y, float z);

private:
	int* m_perm;
	int* m_p;
	
	float _fade(float t);
	float _lerp(float t, float a, float b);
	float _grad(int hash, float x, float y, float z);
};
