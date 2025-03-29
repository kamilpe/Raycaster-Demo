//
//  raycaster.h
//  Raycaster-Demo
//
//  Created by Kamil Pawlowski on 11/03/2025.
//

#pragma once

#include <SDL3/SDL.h>
#include <cmath>

constexpr int MAP_WIDTH = 8;
constexpr int MAP_HEIGHT = 11;
constexpr int MAP_GRID_SIZE = 64;

constexpr int PLAYER_SIZE = 8;
constexpr int PLAYER_FOV = 60;
constexpr float PLAYER_SPEED_MOVEMENT = 4;
constexpr float PLAYER_SPEED_ROTATION = 4;

constexpr int VIEWPORT_X = MAP_WIDTH * MAP_GRID_SIZE + 1; // next to the map viewport
constexpr int VIEWPORT_Y = 0;
constexpr int VIEWPORT_SCALE = 4; // 1 means pixel precision
constexpr int VIEWPORT_WIDTH = (1280 - VIEWPORT_X) / VIEWPORT_SCALE; // to keep viewport same size as map viewport
constexpr int VIEWPORT_HEIGHT = MAP_HEIGHT * MAP_GRID_SIZE; // to keep viewport same size as map viewport

void updatePlayer(const SDL_Keycode &key);
void calculateRays();
void drawMapGrid(SDL_Renderer *renderer);
void drawPlayer(SDL_Renderer *renderer);
void drawRays(SDL_Renderer *renderer);
void drawRaycastView(SDL_Renderer *renderer);
