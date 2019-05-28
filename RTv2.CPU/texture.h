#ifndef TEXTURE_H
#define TEXTURE_H

//texel buffers
template<typename T,int X,int Y>
struct texture
{
private:

	T data[X][Y];

public:

	texture();

	T get_texel(int x, int y);

	void set_texel (int x, int y, T texel);

};

template<typename T,int X,int Y>
texture<T, X, Y>::texture()
{

}

template<typename T, int X, int Y>
T texture<T, X, Y>::get_texel(int x, int y)
{
	return data[x][y];
}

template<typename T, int X, int Y>
void texture<T, X, Y>::set_texel(int x, int y, T texel)
{
	data[x][y] = texel;
}
#endif