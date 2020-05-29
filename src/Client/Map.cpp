//#include "Map.h"
//Map::Map()
//{
//	dirt = TextureLoader::LoadTexture("img/Dirt");
//	water = TextureLoader::LoadTexture("img/Water");
//	grass = TextureLoader::LoadTexture("img/Grass");
//
//	LoadMap(lvl1);
//	src.x = src.y = 0;
//	src.w = dest.w = 32;
//	src.h = dest.h = 32;
//
//	dest.x = dest.y = 0;
//
//}
//Map::~Map()
//{
//	SDL_DestroyTexture(grass);
//	SDL_DestroyTexture(water);
//	SDL_DestroyTexture(dirt);
//}
//
//void Map::LoadMap()//Pass texture
//{
//	for (int x = 0; x < countX; x++)
//	{
//		for (int y = 0; y < length; y++)
//		{
//			//Map tile here
//		}
//	}
//}
//void Map::DrawMap()
//{
//	int type = 0;
//	for (int x = 0; x < countX; x++)
//	{
//		for (int y = 0; y < length; y++)
//		{
//			type = map[][]
//				dest.x = column * 32;
//			dest.y = row * 32;
//			switch (type)
//			{
//			case 0:
//				TextureLoader::Draw(water, src, dest);
//				break;
//			case 1:
//				TextureLoader::Draw(grass, src, dest);
//				break;
//			case 2:
//				TextureLoader::Draw(dirt, src, dest);
//				break;
//			default:
//				break;
//			}
//		}
//	}
//
//}