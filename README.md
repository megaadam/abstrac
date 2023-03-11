# abstrac
Streaming Abstract Pixel Art


## What is This Then ?
**Q:** The world's most overengineered *Starfield* screen-saver??<br>
**A:** I am not sure... there might be even worse.

<p float="center">
<img src="./media/starfield1.png"      width="48%" title="The Classic Starfield Animation"/>
<img src="./media/sliding-doors1.png"  width="48%" title="&quot;Sliding Doors&quot; Animation"/>
</p>

## Live Stream
Why not catch <b>[the live stream](https://www.twitch.tv/abstrac55)</b> ?

**Schedule:** Monday to Saturday 09:00 - 01:00 CET


## Goals
What I am trying to achieve here, is to create nifty random algorithmic patterns... but not quite only that.
I want to create an infrastructure where I create new abstract animations, and:
* **stream live animations** to Twitch (and in the future: Vimeo, YouTube, etc)
* easily review animations on my desktop, from debugger
* quickly tweak animation parameters
* easily deploy the "animation streaming services" to any server, including cloud (e.g. `make deploy`)
* configure schedules and layers:
    * Multiple layers,
    * eg. overlay an animation with a blurred version of itself
* another aspect of configuration is to record a slightly longer loop, and stream that, to save CPU power, and the planet
* future animations might be: falling autumn leaves, fun with typography etc etc...


## System Architecture
### The Services
To make the live stream happen, I am using two systemd services.
* `abstrac-engine.service` (the _rendering service_)
* `abstrac-ffmpeg.service` (the _streaming service_)

`abstrac-engine.service` is the C++ executable that renders the animations to be
streamed. For rendering I use **`raylib`**,  which is a nice C++ wrapper around
GLFW, which is an OpenGL wrapper. At some future point in time, it may happen
that I will use OpenGL directly. But with my near zero OpenGL experience,
**`raylib`** gave me a tremendous kickstart.

`abstrac-ffmpeg.service` is just running a single `ffmpeg`-command that streams the rendered images to Twitch.


### Service Interoperation
There is no intricate communication protocol here! The interface between the two
services, is simply a circular RAM disk buffer.

The rendering service is writing images to a RAM disk
(numbered `*.00000 - *01999`). It is looping through the numbers.
The streaming service is then looping through the same images. The rich `ffmpeg`
command line interface provides a straightforward way of streaming a loop of
images on a wildcard filepath. The file format is uncompressed raw 32-bit RGBA.
(Initially I used png, but after a while I noticed that the **`raylib`** png conversion was disproportionately CPU-intensive!)

Currently, there is no safeguard to prevent read/write race
conditions. But the services seem to cope quite well anyway.

The service files, including the full `ffmpeg` command, and stream scheduling,
are [all in this repo](https://github.com/megaadam/abstrac/tree/main/service).


## Streaming Format
* Flash Video container format over the RTMP streaming protocol
* 800x450 pixels (16x9), 25 fps, 400 kb/s, (`ffmpeg ultrafast`)
* Currently, I have not ventured into streaming any audio with the animations

## Credits & Dependencies

**The awesome `raylib`** <br>
License: zlib/libpng <br>
Copyright (c) 2014-2023 Ramon Santamaria (@raysan5)
https://github.com/raysan5/raylib
Version: 4.2.0

**The great `ffmpeg` toolset** <br>
License: GNU LGPL <br>
Copyright (c) 2000-2023 the FFmpeg developers <br>
http://ffmpeg.org <br>
Version: 5.1.2 <br>
(Currently, I am only using the complete executable. Later I might need link directly to the ffmpeg libraries)