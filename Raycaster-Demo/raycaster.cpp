//
//  raycaster.cpp
//  Raycaster-Demo
//
//  Created by Kamil Pawlowski on 11/03/2025.
//

#include <SDL3/SDL.h>
#include <cmath>
#include <algorithm>

const int map[] = {
    1,1,1,1,1,1,1,1,
    1,0,0,2,0,0,0,1,
    1,0,0,2,0,0,0,1,
    1,0,0,2,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,2,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,3,3,3,3,3,3,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1
};

constexpr int MAP_WIDTH = 8;
constexpr int MAP_HEIGHT = 11;
constexpr int MAP_GRID_SIZE = 64;

constexpr int PLAYER_SIZE = 8;
constexpr float PLAYER_SPEED_MOVEMENT = 4;
constexpr float PLAYER_SPEED_ROTATION = 4;
constexpr int PLAYER_FOV = 60;

constexpr int VIEWPORT_X = MAP_WIDTH * MAP_GRID_SIZE + 1; // next to the map viewport
constexpr int VIEWPORT_Y = 0;
constexpr int VIEWPORT_SCALE = 8; // 1 means pixel precision
constexpr int VIEWPORT_WIDTH = (1280 - VIEWPORT_X) / VIEWPORT_SCALE; // to keep viewport same size as map viewport
constexpr int VIEWPORT_HEIGHT = MAP_HEIGHT * MAP_GRID_SIZE; // to keep viewport same size as map viewport

namespace {
float playerX = 300;
float playerY = 320;
float playerAngle = 45;
}


constexpr int mapAt(const int x, const int y) {
    return map[MAP_WIDTH * y + x];
}

constexpr int mapAtPos(const float x, const float y) {
    return mapAt(x / MAP_GRID_SIZE, y / MAP_GRID_SIZE);
}

constexpr float degToRadians(const float deg) {
    return deg * (M_PI/180);
}

constexpr float calcDistance(const float x1, const float yl, const float x2, const float y2) {
    return sqrt(pow(x1 - x2, 2) + pow(yl - y2, 2));
}

constexpr float fishEyeFix(const float distance, const float angle, float rayAngle)
{
    return distance * cosf(rayAngle - angle);
}

void drawMapGrid(SDL_Renderer *renderer)
{
    for (int x=0; x<MAP_WIDTH; ++x)
        for (int y=0; y<MAP_HEIGHT; ++y)
        {
            const float gx = x * MAP_GRID_SIZE;
            const float gy = y * MAP_GRID_SIZE;
            const SDL_FRect gridBorder = {
                gx, gy,
                MAP_GRID_SIZE, MAP_GRID_SIZE
            };
            
            const SDL_FRect gridInterior = {
                gridBorder.x+1, gridBorder.y+1,
                gridBorder.w-2, gridBorder.h-2
            };
            
            SDL_SetRenderDrawColor(renderer, 180, 180, 180, SDL_ALPHA_OPAQUE);
            SDL_RenderRect(renderer, &gridBorder);
            if (mapAt(x,y)) {
                SDL_SetRenderDrawColor(renderer, 150, 50, 50, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &gridInterior);
            }
            
            const int playerGridX = floor(playerX / MAP_GRID_SIZE);
            const int playerGridY = floor(playerY / MAP_GRID_SIZE);
            if (x == playerGridX && y == playerGridY) {
                SDL_SetRenderDrawColor(renderer, 60, 60, 60, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &gridInterior);
            }
        }
}

void drawPlayer(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 50, 150, 50, SDL_ALPHA_OPAQUE);
    const SDL_FRect playerRect = {
        playerX - PLAYER_SIZE/2,
        playerY - PLAYER_SIZE/2,
        PLAYER_SIZE, PLAYER_SIZE
    };
    SDL_RenderFillRect(renderer, &playerRect);
    
    const float sin = sinf(degToRadians(playerAngle));
    const float cos = cosf(degToRadians(playerAngle));
    const float angleX = playerX + cos * 10;
    const float angleY = playerY + sin * 10;
    SDL_RenderLine(renderer, playerX, playerY, angleX, angleY);
}

void updatePlayer(const SDL_Keycode &key)
{
    const float undoPlayerX = playerX;
    const float undoPlayerY = playerY;
    const float sin = sinf(degToRadians(playerAngle));
    const float cos = cosf(degToRadians(playerAngle));
    if (key == SDLK_UP)
    {
        playerX += cos * PLAYER_SPEED_MOVEMENT;
        playerY += sin * PLAYER_SPEED_MOVEMENT;
    }
    else if (key == SDLK_DOWN)
    {
        playerX -= cos * PLAYER_SPEED_MOVEMENT;
        playerY -= sin * PLAYER_SPEED_MOVEMENT;
    }
    else if (key == SDLK_LEFT)
    {
        playerAngle -= PLAYER_SPEED_ROTATION;
    }
    else if (key == SDLK_RIGHT)
    {
        playerAngle += PLAYER_SPEED_ROTATION;
    }
    
    if (playerAngle < 0) playerAngle = 359;
    else if (playerAngle >= 360) playerAngle = 0;
    if (mapAtPos(playerX, playerY))
    {
        playerX = undoPlayerX;
        playerY = undoPlayerY;
    }
}

namespace {
struct Ray {
    float x;
    float y;
    float angle;
};
Ray rays [VIEWPORT_WIDTH];
}

void calculateRays()
{
    const float rayIncrement = degToRadians(PLAYER_FOV) / VIEWPORT_WIDTH;
    const int precision = 64;
    float currentRayAngle = degToRadians(playerAngle - PLAYER_FOV / 2);
    
    for (int i=0; i < VIEWPORT_WIDTH; ++i)
    {
        const float rayCos = cosf(currentRayAngle) / precision;
        const float raySin = sinf(currentRayAngle) / precision;
        float rayX = playerX;
        float rayY = playerY;
        int wall = 0;
        while (wall == 0) {
            rayX += rayCos;
            rayY += raySin;
            wall = mapAtPos(rayX, rayY);
        }
        rays[i] = {rayX, rayY, currentRayAngle};
        currentRayAngle += rayIncrement;
    }
}

void drawRays(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 60, 60, 200, SDL_ALPHA_OPAQUE);
    for(int i=0; i<VIEWPORT_WIDTH; ++i)
    {
        SDL_RenderLine(renderer, playerX, playerY, rays[i].x, rays[i].y);
    }
}

void drawRaycastView(SDL_Renderer *renderer)
{
    for(int i=0; i<VIEWPORT_WIDTH; ++i)
    {
        const auto ray = rays[i];
        const float distance =
        fishEyeFix(calcDistance(playerX, playerY, ray.x, ray.y),
                   degToRadians(playerAngle), ray.angle);
        
        const float wallHeight =
        std::min(
                 (MAP_GRID_SIZE * (VIEWPORT_WIDTH * VIEWPORT_SCALE)) / distance,
                 static_cast<float>(VIEWPORT_HEIGHT));
        
        const float startX = static_cast<float>(VIEWPORT_X + (VIEWPORT_SCALE*i));
        
        const SDL_FRect wallRect = {
            startX, VIEWPORT_Y + (VIEWPORT_HEIGHT - wallHeight) / 2,
            VIEWPORT_SCALE, wallHeight
        };
        const SDL_FRect ceilRect = {
            startX, 0,
            VIEWPORT_SCALE, VIEWPORT_HEIGHT/2 - wallRect.h/2
        };
        const SDL_FRect floorRect = {
            startX, wallRect.y + wallRect.h,
            VIEWPORT_SCALE, VIEWPORT_HEIGHT - (ceilRect.h + wallRect.h)
        };
        
        // ceil
        SDL_SetRenderDrawColor(renderer, 128, 128, 200, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &ceilRect);
        // wall
        switch(mapAtPos(ray.x,ray.y)) {
            case 1:
                SDL_SetRenderDrawColor(renderer, 200, 60, 60, SDL_ALPHA_OPAQUE);
                break;
            case 2:
                SDL_SetRenderDrawColor(renderer, 60, 160, 160, SDL_ALPHA_OPAQUE) ;
                break;
            case 3:
                SDL_SetRenderDrawColor(renderer, 60, 60, 160, SDL_ALPHA_OPAQUE);
                break;
        }
        SDL_RenderFillRect(renderer, &wallRect);
        // floor
        SDL_SetRenderDrawColor(renderer, 0, 90, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &floorRect);
    }
}
    
