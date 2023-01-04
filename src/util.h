// MIT License -- Copyright (c) 2023 Adam Horvath

#pragma once

#include "ray.h"

float interpol(float time, float startTime, float endTime, float f1, float f2);
Vector3 interpol(float time, float startTime, float endTime, Vector3 v1, Vector3 v2);

Color rndHLS(float minH, float maxH, float minL, float maxL, float minS, float maxS, int a = 255);


// internal
Color hsl2rgb(float h, float s, float l, int a = 255);
float hue2rgb(float p, float q, float t);