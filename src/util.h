// MIT License -- Copyright (c) 2023 Adam Horvath

#pragma once

#include "ray.h"

Color rndHLS(float minH, float maxH, float minL, float maxL, float minS, float maxS, int a = 255);


// internal
Color hsl2rgb(float h, float s, float l, int a = 255);
float hue2rgb(float p, float q, float t);