# gst_test
gst testing
# meson and ninja install
- apt-get install python3 python3-pip python3-setuptools python3-wheel ninja-build -y
- pip3 install meson
- apt-get install flex
- apt-get install bison
- apt-get install libglib2.0-dev
- gst-launch-1.0 -v ximagesrc use-damage=0 ! video/x-raw,framerate=30/1 ! videoconvert ! x264enc bitrate=5000 speed-preset=superfast ! mpegtsmux ! srtsink uri=srt://your_srt_server_ip:your_srt_port
- gst-launch-1.0 -v \
    webrtcbin name=sendrecv bundle-policy=max-bundle \
    ximagesrc use-damage=0 ! video/x-raw,framerate=30/1 ! videoconvert ! queue ! vp8enc deadline=1 ! rtpvp8pay ! application/x-rtp,media=video,encoding-name=VP8,payload=96 ! sendrecv.
