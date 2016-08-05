#include <fstream>
#include <SDL_image.h>
#include <stdio.h>

#include "Manager.h"

#include <sstream>

namespace
{
	std::vector<std::string> split(std::string metadata)
	{
		std::istringstream in(metadata);
		std::vector<std::string> result;
		std::string token;

		while (in >> token)
		{			
			result.push_back(token);
		}

		return result;
	}
}

SDL_Window* 	Manager::window = nullptr;
SDL_Renderer*	Manager::renderer = nullptr;

Manager::Manager(void)
	: keys(KEYS::NONE)
	, background(nullptr)
	, screenWidth(SCREEN_WIDTH)
	, screenHeight(SCREEN_HEIGHT)
{
}

Manager::~Manager(void)
{
}

i32 Manager::Init()
{
	//start sdl
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
		return MANAGERERROR::SDL_INITFAIL;

	//start img
	i32 flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if ( IMG_Init( flags ) != flags )
		return MANAGERERROR::IMG_INITFAIL;

	window = SDL_CreateWindow("2D Graphics",  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if ( !window )
		return MANAGERERROR::WINDOW_INITFAIL;

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if (!renderer)
		return MANAGERERROR::RENDERER_FAIL;

	LoadLevel("level1.txt");

	return 0;
}

void Manager::ApplyMetadata(GameObject *object, std::string metadata)
{
	std::vector<std::string> data = split(metadata);

	for (size_t i = 0; i < data.size(); i += 4)
	{
		if (data[i] == "follow")
		{
			std::string target = data[i + 1];
			std::string distance = data[i + 2];
			std::string angle = data[i + 3];

			object->target = objs[target];
			
			object->offset.r = stof(distance);
			object->offset.th = stof(angle);
		}
	}
}

b32 Manager::LoadLevel(std::string levelfile)
{
	std::ifstream in;
	in.open(levelfile);

	if ( in.fail() )
		exit(MANAGERERROR::FILEOPEN_ERROR);

	std::string type, file, name;
	i32 x, y, w, h;
	r32 speed;

	while ( !in.eof() )
	{
		in >> type;
		if (in.fail())
			continue;

		if (type == "bg")
		{
			in >> file;
			background = LoadTexture(file);
			//objs.insert("bg", new GameObject);
			//objs["bg"]->Init(file);
		}
		else if (type == "Object" || type == "Player")
		{
			in >> name >> speed >> file >> x >> y >> w >> h;
			objs[name] = new GameObject;
			//objs.insert( name, new GameObject );
			objs[name]->Init( file );
			objs[name]->position.x = (r32)x;
			objs[name]->position.y = (r32)y;
			objs[name]->pos.w = w;
			objs[name]->pos.h = h;
			objs[name]->speed = speed;

			if (!player)
			{
				player = objs[name];
			}

			std::string meta;
			getline(in, meta);

			ApplyMetadata(objs[name], meta);
		}
		else if (type == "Nextlevel")
		{
			in >> nextlevel;
		}
	}

	in.close();
	return true;
}

b32 Manager::Update()
{
	if ( !KeyUpdate() )
		return false;
	
	if (keys & KEYS::UP)
	{
		printf("UP\n");
	}
	if (keys & KEYS::DOWN) 
	{
		printf("DOWN\n");
	}
	if (keys & KEYS::LEFT) 
	{
		printf("LEFT\n");
	}
	if (keys & KEYS::RIGHT) 
	{
		printf("RIGHT\n");
	}

	if (player)
	{
		//GameObject mouse;
		//mouse.position = Vector2(mouse_pos.x, mouse_pos.y);
		//player->target = &mouse;
		player->position.x = mouse_pos.x;
		player->position.y = mouse_pos.y;
	}

	SDL_RenderClear( renderer );
	SDL_RenderCopy( renderer, background, nullptr, nullptr);
	
	for (ObjectByName::value_type& objByName : objs)
	{
		GameObject* obj = objByName.second;
		obj->Move(keys);// i == 0 ? keys : 0);
		obj->Update();
	}
	
	for (ObjectByName::value_type& objByName : objs)
	{
		GameObject* obj = objByName.second;
		obj->Render();
#if _DEBUG
		obj->DebugRender();
#endif

	}
	
	SDL_RenderPresent( renderer );

	return true;
}

void Manager::Close()
{
	objs.clear();

	if(renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if(window)
		SDL_DestroyWindow( window );

	IMG_Quit();
	SDL_Quit();
}


SDL_Texture* Manager::LoadTexture(std::string filename, SDL_Rect* offset)
{
	if ( renderer == nullptr )
		exit( 403 );

	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;

	surface = IMG_Load( filename.c_str() );
	if ( surface == nullptr )
		exit( 404 );
	
	if ( offset != nullptr )
	{
		offset->w = surface->w;
		offset->h = surface->h;
	}
	
	texture = SDL_CreateTextureFromSurface( renderer, surface );

	SDL_FreeSurface( surface );
	return texture;
}

void Manager::RenderTexture(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* offset)
{
	SDL_RenderCopy( renderer, texture, clip, offset );
}

void Manager::RenderTextureEx(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* offset, r32 angle, SDL_Point* rotationPoint)
{
	SDL_RenderCopyEx(renderer, texture, clip, offset, angle, rotationPoint, SDL_FLIP_NONE);
}

b32 Manager::KeyUpdate()
{
	i32 x, y;
	SDL_GetMouseState(&x, &y);
	mouse_pos.x = (r32)x;
	mouse_pos.y = (r32)y;

	SDL_Event e;
	while ( SDL_PollEvent( &e ) )
	{
		switch( e.type )
		{
		case SDL_QUIT:
			return false;

		case SDL_KEYDOWN:
			if ( !KeyDown( e.key.keysym.sym ) )
				return false;
			break;

		case SDL_KEYUP:
			if ( !KeyUp( e.key.keysym.sym ) )
				return false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if ( e.button.button == SDL_BUTTON_LEFT )
				keys |= KEYS::MOUSE0;
			if ( e.button.button == SDL_BUTTON_RIGHT )
				keys |= KEYS::MOUSE1;
			break;

		case SDL_MOUSEBUTTONUP:
			if ( e.button.button == SDL_BUTTON_LEFT )
				keys &= (~KEYS::MOUSE0);
			if ( e.button.button == SDL_BUTTON_RIGHT )
				keys &= (~KEYS::MOUSE1);
			break;
		}
	}
	return true;
}

b32 Manager::KeyDown(SDL_Keycode key)
{
	switch( key )
	{
	case SDLK_ESCAPE:
		return false;
		break;

	case SDLK_UP:
	case 'w':
		keys |= KEYS::UP;
		break;
	
	case SDLK_DOWN:
	case 's':
		keys |= KEYS::DOWN;
		break;

	case SDLK_LEFT:
	case 'a':
		keys |= KEYS::LEFT;
		break;

	case SDLK_RIGHT:
	case 'd':
		keys |= KEYS::RIGHT;
		break;

	case SDLK_SPACE:
		keys |= KEYS::SPACE;
		break;
	}

	return true;
}

b32 Manager::KeyUp(SDL_Keycode key)
{
	switch( key )
	{
	case SDLK_ESCAPE:
		return false;
		break;

	case SDLK_UP:
	case 'w':
		keys &= ~KEYS::UP;
		break;
	
	case SDLK_DOWN:
	case 's':
		keys &= ~KEYS::DOWN;
		break;

	case SDLK_LEFT:
	case 'a':
		keys &= ~KEYS::LEFT;
		break;

	case SDLK_RIGHT:
	case 'd':
		keys &= ~KEYS::RIGHT;
		break;

	case SDLK_SPACE:
		keys &= ~KEYS::SPACE;
		break;

	}

	return true;
}