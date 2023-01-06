// MIT License -- Copyright (c) 2023 Adam Horvath

#include "util.h"
#include <random>

float interpol(float time, float startTime, float endTime, float f1, float f2)
{
    time = std::max(std::min(time, endTime), startTime); // clamp time between start & end

    float r = (time - startTime) / (endTime - startTime);
    return f1 * (1.0 - r) + f2 * r;
}


Vector3 interpol(float time, float startTime, float endTime, Vector3 v1, Vector3 v2)
{
    return Vector3 {
        interpol(time, startTime, endTime, v1.x, v2.x),
        interpol(time, startTime, endTime, v1.y, v2.y),
        interpol(time, startTime, endTime, v1.z, v2.z),
    };
}


Color rndHLS(float minH, float maxH, float minL, float maxL, float minS, float maxS, int a) {
    std::random_device r;
    std::default_random_engine eng(r());
    std::uniform_real_distribution<> disH(minH, maxH);
    std::uniform_real_distribution<> disL(minL, maxL);
    std::uniform_real_distribution<> disS(minS, maxS);

    float h = disH(eng);
    float l = disL(eng);
    float s = disS(eng);

    return hsl2rgb(h, l, s, a);
}

////////////////////////////////////////////////////////////////////////
// Adapted from: https://gist.github.com/ciembor/1494530
/*
 * Converts an HUE to r, g or b.
 * returns float in the set [0, 1].
 */
float hue2rgb(float p, float q, float t) {

  if (t < 0)
    t += 1;
  if (t > 1)
    t -= 1;
  if (t < 1./6)
    return p + (q - p) * 6 * t;
  if (t < 1./2)
    return q;
  if (t < 2./3)
    return p + (q - p) * (2./3 - t) * 6;

  return p;

}

////////////////////////////////////////////////////////////////////////

/*
 * Converts an HSL color value to RGB. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
 * Assumes h, s, and l are contained in the set [0, 1] and
 * returns RGB in the set [0, 255].
 */
Color hsl2rgb(float h, float l,  float s, int a) {

    Color col;

    if(0 == s) {
        col.r = col.g = col.b = l; // achromatic
    }
    else {
        float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        float p = 2 * l - q;
        col.r = hue2rgb(p, q, h + 1./3) * 255;
        col.g = hue2rgb(p, q, h) * 255;
        col.b = hue2rgb(p, q, h - 1./3) * 255;
    }
    col.a = a;

    return col;

}