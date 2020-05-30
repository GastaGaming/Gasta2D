#pragma once
#include "../ECS/Components.h"
#include <fstream>
#include <string>
//#include "Game.h"
Uint32 getpixel(SDL_Surface* surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16*)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32*)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}
class Map
{
public:
	Map() {};
	~Map() {};

	static void LoadMap(std::string path)
	{
		//char tile;
		//std::fstream mapImage;"img/map.tga"
		SDL_Surface* tempSurface = IMG_Load(path.c_str());
		//mapImage.open(path);
		for (int y = 0; y < tempSurface->h; y++)
		{
			for (int x = 0; x < tempSurface->w; x++)
			{
				//mapImage.get(tile);
				//Game::AddTile(atoi(&tile), x * 32, y * 32);
				//mapImage.ignore();
                Uint32 pixel = getpixel(tempSurface, x, y);
                SDL_Color rgb;
                SDL_GetRGB(pixel, tempSurface->format, &rgb.r, &rgb.g, &rgb.b);
                std::cout << "Pixel Y : " << y << " X :" << x << " RGB = " << rgb.r << "," << rgb.g << "," << rgb.b << std::endl;
                int t = 0;
                if (rgb.r == 255)
                {
                    t = 0;
                }
                if (rgb.g == 255)
                {
                    t = 1;
                }
                if (rgb.b == 255)
                {
                    t = 2;
                }
                Game::AddTile(t, x * 32, y * 32);
			}
		}
		//mapImage.close();
        SDL_FreeSurface(tempSurface);
	}
private:
};