#!/usr/bin/bash

set -x

killall abstrac_engine
killall ffmpeg
# rm -rf /tmp/ramdisk/*.raw

make build
nohup ./bin/abstrac_engine headless &> nohup_engine &
sleep 5 # get a decent head start in RAM buffer

set +x
#nohup ffmpeg -loglevel debug -stream_loop -1 -f image2 -re -framerate 25 -pattern_type glob -i '/tmp/ramdisk/*.png'  -preset ultrafast  -r 25 -c:v libx264 -pix_fmt yuv420p -f flv rtmp://arn04.contribute.live-video.net/app/$twtch
# ffmpeg -loglevel info -stream_loop -1 -f image2 -re -framerate 25  -pattern_type glob -i '/mnt/ramdisk/*.png'  -preset ultrafast   -c:v libx264 -pix_fmt yuv420p -s 1280x720 -f flv -force_key_frames 2 -b:v 1400k -minrate 1400k -maxrate 1400k -bufsize 2m rtmp://arn04.contribute.live-video.net/app/$twtch
#nohup ffmpeg -loglevel info -loop 1 -f image2 -re -framerate 25  -pattern_type glob -i '/tmp/ramdisk/*.png'  -preset ultrafast   -c:v libx264 -pix_fmt yuv420p -s 800x450 -f flv -force_key_frames 2 -b:v 400k -minrate 200k -maxrate 800k -bufsize 2m rtmp://arn04.contribute.live-video.net/app/$twtch &> nohup_ffmpeg &
ffmpeg -loglevel info -loop 1 -f image2 -re -framerate 25  -pattern_type glob -pix_fmt rgb32 -s 800x450 -i '/tmp/ramdisk/*.raw'  -preset ultrafast   -c:v libx264 -pix_fmt yuv420p -s 800x450 -f flv -force_key_frames 2 -b:v 400k -minrate 200k -maxrate 800k -bufsize 2m rtmp://arn04.contribute.live-video.net/app/$twtch &> nohup_ffmpeg &

# ffplay  -f image2  -framerate 25 -pattern_type glob -i '/tmp/ramdisk/*.png'
sleep 1
echo "=============================================="
echo "Now playing to https://www.twitch.tv/abstrac55"
echo "=============================================="

