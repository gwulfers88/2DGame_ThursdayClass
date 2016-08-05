#if EMACS
#include "..\deps\include\SDL\SDL.h"
#else
#include <SDL.h>
#endif

#include <unordered_map>
#include "GameObject.h"

#pragma once

namespace MANAGERERROR
{
    enum { SDL_INITFAIL=-10, IMG_INITFAIL, TTF_INITFAIL, WINDOW_INITFAIL, RENDERER_FAIL, FILEOPEN_ERROR };
}

class Manager
{
public:
    Manager(void);
    ~Manager(void);

    i32 Init();

    b32 LoadLevel(std::string levelfile);

    b32 Update();
    void Close();

    static SDL_Texture* LoadTexture(std::string filename, SDL_Rect* offset = nullptr);
    static void         RenderTextureEx(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* offset, r32 angle, SDL_Point* rotationPoint);
    static void         RenderTexture(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* offset);
    
    static SDL_Window*      window;
    static SDL_Renderer*    renderer;

private:
    void ApplyMetadata(GameObject *object, std::string data);
    
    b32 KeyUpdate();
    b32 KeyDown(SDL_Keycode key);
    b32 KeyUp(SDL_Keycode key);

    PhysicsManager* phys_man;

    u32 screenWidth;
    u32 screenHeight;

    i32      keys;
    Vec2 mouse_pos;
    
    std::string nextlevel;
    typedef std::unordered_map<std::string, GameObject*> ObjectByName;
    ObjectByName objs;

    GameObject* player;

    SDL_Texture* background;
};

