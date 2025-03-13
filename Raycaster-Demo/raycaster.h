//
//  raycaster.h
//  Raycaster-Demo
//
//  Created by Kamil Pawlowski on 11/03/2025.
//

#pragma once

#include <SDL3/SDL.h>

void updatePlayer(const SDL_Keycode &key);
void calculateRays();
void drawMapGrid(SDL_Renderer *renderer);
void drawPlayer(SDL_Renderer *renderer);
void drawRays(SDL_Renderer *renderer);
void drawRaycastView(SDL_Renderer *renderer);
