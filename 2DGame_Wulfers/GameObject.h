#include "Vec2.h"
#include <string>
#include <unordered_map>
#include <SDL.h>

#pragma once

using namespace std;

class Manager;
class PhysicsObject;
class PhysicsManager;

enum ComboType
{
	NONE = 0x00,
	DASH_RIGHT = 0x01,
	DASH_LEFT = 0x10,
	ORBIT = 0x100,
};

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
	void FollowTarget();
    //virtual bool Collide(GameObject* other);
    //virtual void HandleCollision(GameObject* other);

    b32 active;

protected:
	void PerformDash(Vec2 dir);

    virtual void UpdateAnimation();
    void OrbitTarget();

    PhysicsObject* phys_obj;
	
	b32 isControlled;
	b32 isOrbiting;

	ComboType comboType;

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

