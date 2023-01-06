// MIT License -- Copyright (c) 2023 Adam Horvath

#include <iostream>
#include <string.h>

#include "ray.h"

int main(int argc, char** argv)
{
    std::cout << "Hi there, World!" << std::endl;
    bool headless = false;
    if(argc > 1 && strcmp(argv[1], "headless") == 0)
    {
        headless = true;
    }
    return rayWin5(defaultScreenWidth, defaultScreenHeight, 25.0, headless);
}
