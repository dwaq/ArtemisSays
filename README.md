## Installation

**In WSL:**

Download tensorflow:

`git clone --depth 1 https://github.com/tensorflow/tensorflow.git`

`cd tensorflow`

Download Python dependencies:

`pip3 install pycrypto pyserial --user`

Compile code for hello_world (important, because it downloads and installs other tensorflow dependencies)

(might need to install unzip first: `sudo apt install unzip`)

`make -f tensorflow/lite/micro/tools/make/Makefile TARGET=sparkfun_edge hello_world_bin`

Compile the actual code that we want to run:

`make -f tensorflow/lite/micro/tools/make/Makefile TARGET=sparkfun_edge micro_speech_bin`

Flash it to the board:

`./tensorflow/lite/micro/tools/make/downloads/AmbiqSuite-Rel2.2.0/boards_sfe/common/tools_sfe/ambiq/ambiq_bin2board.py --bin tensorflow/lite/micro/tools/make/gen/sparkfun_edge_cortex-m4/bin/micro_speech.bin`