#include <fstream>
#include <iostream>

#if EMACS
#include "..\deps\include\SDL\SDL_image.h"
#else
#include <SDL_image.h>
#endif

#include "GameObject.h"
#include "Manager.h"

GameObject::GameObject(void)
    : target(0)
    , active(true)
    , surf(nullptr)
    , img(nullptr)
    , angle(0)
    , pos({0,0,0,0})
    , position(0,0)
    , velocity(0, 0)
    , accel(0, 50)
    , clip({ 0,0,0,0 })
    , frame(0)
    , prev(0)
    , timer(0)
{
}

GameObject::~GameObject(void)
{
}

void GameObject::Init(string txtfile, SDL_Rect* dest)
{
    img = Manager::LoadTexture(txtfile, &pos);
    prev = SDL_GetTicks();
    timer = 0;
}

/*
 p' = 1/2(a)(t^2) + vt + p
 v' = 10t + v
 a' = 10
*/
//true if eats up a key, false otherwise
b32 GameObject::Update()
{
    u32 now = SDL_GetTicks();
    dt = (r32)(now - prev) / 1000.0f;
    timer += dt;
    prev = now;

    if (!active)
        return false;

    angle += 100 * dt;

    Vec2 dirToTarget = {0, 0};

    OrbitTarget();
    UpdateAnimation();
    
    return false;
}

void GameObject::OrbitTarget()
{
    // Deg to Rad = angle * PI / 180.
    // x = cos(angle) * r
    // y = sin(angle) * r
    // offset = r, angle
    // angle = 45
    // a = offset.angle + angle * pi / 180
    // pos.x = r * cos(a) + target.pos.x
    // pos.y = r * sin(a) + target.pos.y

    if (!target)
        return;

    float angle = 180 * SDL_GetTicks() / 1000.0f;
    float rotateAngle = (offset.th + angle) * (r32)M_PI / 180.0f;

    //HOMEWORK: Find targets pivot based on rotation.
    Vec2 pivot = target->position + (Vec2(10, 10) * 0.5f);

    Vec2 center;
    center.x = offset.r * cos(rotateAngle) + pivot.x;
    center.y = offset.r * sin(rotateAngle) + pivot.y;

    position = center - (Vec2((r32)pos.w, (r32)pos.h) * 0.5f);
}

void GameObject::Render()
{
    //moving position from top left corner to the center of Rect.
    pos.x = (i32)position.x - (i32)(pos.w * 0.5f);
    pos.y = (i32)position.y - (i32)(pos.h * 0.5f);

    SDL_SetRenderDrawColor(Manager::renderer, 0, 0, 0, 255);
    if (active)
        Manager::RenderTextureEx( img, nullptr, &pos, angle, 0);
}

#if _DEBUG
void GameObject::DebugRender()
{
    if (target)
    {
        SDL_SetRenderDrawColor(Manager::renderer, 255, 100, 255, 255);
        SDL_RenderDrawLine(Manager::renderer, (i32)position.x, (i32)position.y, (i32)target->position.x, (i32)target->position.y);
    }
}
#endif

void GameObject::Move(i32 direction)
{
    //Enter movement logic here
    if (direction & KEYS::UP) {}
    if (direction & KEYS::DOWN) {}
    if (direction & KEYS::LEFT) {}
    if (direction & KEYS::RIGHT) {}
}

void GameObject::UpdateAnimation()
{
    // Input animation logic (clip animation) here
    if (timer > 1.0 / FPS) // 66ms ~ 1/15 sec
    {
        frame++;
        timer = 0;
    }
}

//dirToTarget = target->position - position;

////rotPoint->x = (int)dirToTarget.x + (int)(target->pos.w * 0.5f);
////rotPoint->y = (int)dirToTarget.y + (int)(target->pos.h * 0.5f);

//Normalize(&dirToTarget);

//if (MagnitudeSqr(target->position - position) > Square(80))
//{
//  accel = dirToTarget * speed;
//  accel = accel + (-1.5f * velocity);

//  Vec2 newPos = position;
//  newPos = (0.5f * accel) * Square(dt) + velocity * dt + position;
//  velocity = accel * dt + velocity;

//  position = newPos;
//}

/*printf("Accel { %.02f, %.02f } - Vel { %.02f, %.02f}\n", accel.x, accel.y,
velocity.x, velocity.y);*/
