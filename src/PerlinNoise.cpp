#include "PerlinNoise.hpp"
#include <cstdlib>
#include <cmath>



PerlinNoise::PerlinNoise(const int seed)
{
	// Set the seed for the rand() function
	srand(seed);
	
	// Generate the permutation table [0, 255]
	m_perm = new int[256];
	for (int i = 0; i < 256; i++)
		m_perm[i] = i;
		
	// Mix up the permutation table
	for (int i = 0; i < 1024; i++)
	{
		int a = rand() % 256;
		int b = rand() % 256;
		int temp = m_perm[a];
		m_perm[a] = m_perm[b];
		m_perm[b] = temp;
	}
	
	// Set the 'p' table up (??)
	m_p = new int[512];
	for (int i = 0; i < 256; i++)
	{
		m_p[i] = m_perm[i];
		m_p[i + 256] = m_perm[i];
	}
}



PerlinNoise::~PerlinNoise()
{
	delete[] m_perm;
	delete[] m_p;
}



float PerlinNoise::gen(float x, float y, float z)
{
	int X = (int)std::floor(x) & 255;
	int Y = (int)std::floor(y) & 255;
	int Z = (int)std::floor(z) & 255;
	x -= std::floor(x);
	y -= std::floor(y);
	z -= std::floor(z);
	float u = _fade(x);
	float v = _fade(y);
	float w = _fade(z);
	int A  = m_p[X  ] + Y;
	int AA = m_p[A  ] + Z;
	int AB = m_p[A+1] + Z;
	int B  = m_p[X+1] + Y;
	int BA = m_p[B  ] + Z;
	int BB = m_p[B+1] + Z;
	return _lerp(w, _lerp(v, _lerp(u, _grad(m_p[AA  ], x  , y  , z   ),
																		 _grad(m_p[BA  ], x-1, y  , z   )),
									 					_lerp(u, _grad(m_p[AB  ], x  , y-1, z   ),
									 									 _grad(m_p[BB  ], x-1, y-1, z   ))),
									 _lerp(v, _lerp(u, _grad(m_p[AA+1], x  , y  , z-1 ),
																		 _grad(m_p[BA+1], x-1, y  , z-1 )),
									 					_lerp(u, _grad(m_p[AB+1], x  , y-1, z-1 ),
									 									 _grad(m_p[BB+1], x-1, y-1, z-1 ))));
}



float PerlinNoise::_fade(float t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}



float PerlinNoise::_lerp(float t, float a, float b)
{
	return a + t * (b - a);
}



float PerlinNoise::_grad(int hash, float x, float y, float z)
{
	int h = hash & 15;
	float u = h < 8 ? x : y;
	float v = h < 4 ? y : (h == 12 || h == 14 ? x : z);
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
