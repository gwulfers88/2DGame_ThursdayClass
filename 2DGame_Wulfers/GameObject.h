#include "Vec2.h"
#include <string>
#include <unordered_map>
#include <SDL.h>

#pragma once

using namespace std;

class Manager;
class PhysicsObject;
class PhysicsManager;

//GameObject class
class GameObject
{
    friend Manager;
    friend PhysicsObject;
    friend PhysicsManager;

public:
    GameObject(void);
    ~GameObject(void);

    virtual void Init(std::string txtfile, SDL_Rect* dest=nullptr);
    virtual b32 Update();

    virtual void Render();
#if _DEBUG
    void DebugRender();
#endif
    virtual void Move(i32 action);

    //virtual bool Collide(GameObject* other);
    //virtual void HandleCollision(GameObject* other);

    b32 active;

protected:
    virtual void UpdateAnimation();
    void OrbitTarget();

    PhysicsObject* phys_obj;
	
	b32 isControlled;

    SDL_Surface* surf;
    SDL_Texture* img;
    SDL_Rect     pos;

    //target
    GameObject* target;
    Vec2 offset;

    r32 speed;
    r32 mass;
    r32 angle;

    Vec2 position;
    Vec2 velocity;
    Vec2 accel;

    //animation stuff
    SDL_Rect     clip;
    i32          frame;
    
    string state;

    //timer
    u32     prev;
    r32     dt;
    r32     timer;
};

