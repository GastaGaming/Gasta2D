#include "TextureLoader.h"
//Supported formats: ICO, CUR, BMP, GIF, JPG, LBM, PCX, PNG, PNM, TIF, XCF, XPM, XV, WEBP'
//curl http://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.0-mingw.tar.gz > SDL2_image-devel-2.0.0-mingw.tar.gz
//tar -xzvf SDL2_image-devel-2.0.0-mingw.tar.gz
#include "Game.h"
SDL_Texture* TextureLoader::LoadTexture(const char* texture) 
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}

void TextureLoader::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	//SDL_RenderCopy(Game::renderer, tex, &src, &dest);
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);//EX ALLOWS US TO FLIP AND ANGLE THE TEXTURE
}
