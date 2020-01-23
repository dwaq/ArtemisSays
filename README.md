## Installation
In WSL:
Download tensorflow:
`git clone --depth 1 https://github.com/tensorflow/tensorflow.git`
`cd tensorflow`
Download Python dependencies:
`pip3 install pycrypto pyserial --user`
Compile code for hello_world (important, because it installs other tensorflow dependencies)
`make -f tensorflow/lite/micro/tools/make/Makefile TARGET=sparkfun_edge hello_world_bin`