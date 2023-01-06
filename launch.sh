#!/usr/bin/bash

set -x

killall abstrac_engine
killall ffmpeg

make build
nohup ./bin/abstrac_engine headless &> nohup_engine &

set +x
# stream_loop 0 is broken in this version
nohup ffmpeg -stream_loop 99999 -re -framerate 25 -pattern_type glob -i '/mnt/ramdisk/*.png'  -preset ultrafast  -r 25 -c:v libx264 -pix_fmt yuv420p -f flv rtmp://arn04.contribute.live-video.net/app/$twtch &> nohup_ffmpeg &

sleep 1
echo "=============================================="
echo "Now playing to https://www.twitch.tv/abstrac55"
echo "=============================================="

