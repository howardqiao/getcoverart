# getcoverart
Get cover art from file or stream

Build:

sudo apt update

sudo apt install ligavcodec-dev libavformat-dev

gcc -o getcoverart getcoverart.c -lavformat -lavcodec

Usage:

getcoverat musicfile cover.jpg
