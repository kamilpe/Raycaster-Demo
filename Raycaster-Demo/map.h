//
//  map.h
//  Raycaster-Demo
//
//  Created by Kamil Pawlowski on 14/03/2025.
//

struct Color {
    unsigned char r, g, b;
};

struct Texture {
    int width;
    int height;
    int bitmap[];
};

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

const Texture wallTexture {
    8, 8,
    /*{
        1,0,1,0,1,0,1,0,
        1,0,1,0,1,0,1,0,
        1,0,1,0,1,0,1,0,
        1,0,1,0,1,0,1,0,
        1,0,1,0,1,0,1,0,
        1,0,1,0,1,0,1,0,
        1,0,1,0,1,0,1,0,
        1,0,1,0,1,0,1,0
    }*/
    /* {
        1,1,1,1,1,1,1,1,
        0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,
        0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,
        0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,
        0,0,0,0,0,0,0,0
    }*/
    {
        1,1,1,1,1,1,1,1,
        0,0,0,1,0,0,0,1,
        1,1,1,1,1,1,1,1,
        0,1,0,0,0,1,0,0,
        1,1,1,1,1,1,1,1,
        0,0,0,1,0,0,0,1,
        1,1,1,1,1,1,1,1,
        0,1,0,0,0,1,0,0
    }
};

const Color wallPalette[] = {
    {255,155,0},
    {240,95,99}
};
