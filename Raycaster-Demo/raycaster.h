//
//  raycaster.h
//  Raycaster-Demo
//
//  Created by Kamil Pawlowski on 11/03/2025.
//

#pragma once

#include <SDL3/SDL.h>
#include <cmath>

constexpr int map[] = {
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

constexpr float fishEyeFix(const float distance, const float angle, float rayAngle) {
    return distance * cosf(rayAngle - angle);
}

void updatePlayer(const SDL_Keycode &key);
void calculateRays();
void drawMapGrid(SDL_Renderer *renderer);
void drawPlayer(SDL_Renderer *renderer);
void drawRays(SDL_Renderer *renderer);
void drawRaycastView(SDL_Renderer *renderer);
