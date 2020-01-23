Artemis ATP TensorFlow Micro Speech
===================================

This repository is a copy of [sparkfun/Tensorflow_AIOT2019](https://github.com/sparkfun/Tensorflow_AIOT2019) repository adapted for the [SparkFun Artemis ATP Development](https://www.sparkfun.com/products/15442)

<p align="center" valign="middle">
   <img src="https://cdn.sparkfun.com/assets/custom_pages/3/3/4/dark-logo-red-flame.png"  width=200>  
   <img src="https://www.gstatic.com/devrel-devsite/prod/v0ee3aab4746d30f0d189bec7de9a20f1b6a1e49e000167a7abfdd73e499fffdc/tensorflow/images/lockup.svg"  width=300>   
</p>

This repository contains the Micro Speech example that demonstrates the use of [TensorFlow Lite](https://www.tensorflow.org/lite/) based machine learning executing on the [SparkFun Artemis ATP Development](https://www.sparkfun.com/products/15442). The example is designed for use within the Arduino development environment.

The example contained in this repository, micro_speech, uses the on-board microphone to detect a spoken keyword.

<img src="https://cdn.sparkfun.com//assets/parts/1/4/0/1/7/15442-SparkFun_RedBoard_Artemis_ATP-04a.jpg"  align="right" width=300> 

## Contents

* [Required Hardware ](#required-hardware)
* [Software Setup](#software-setup)
* [Running an Example](#running-an-example)

Required Hardware
-----------------

To run the examples, the following hardware is required:
* [SparkFun Artemis ATP Development](https://www.sparkfun.com/products/15442)
* [Reversible USB-A to USB-C cable](https://www.sparkfun.com/products/15425) or a cable to connect the Development Board to the development computer.

<p align="center" valign="middle">
   <img src="https://cdn.sparkfun.com//assets/parts/1/4/0/1/7/15442-SparkFun_RedBoard_Artemis_ATP-04a.jpg"  width=80>  
   <img src="https://cdn.sparkfun.com//assets/parts/4/5/5/8/10215-01.jpg"  width=80>  
</p>

Software Setup
--------------
The example in this repository is for use and execution within the Arduino development environment. This section details the steps required to setup Arduino for the examples.

### Install Arduino

<img src="https://www.arduino.cc/en/pub/skins/arduinoWide/img/ArduinoAPP-01.svg"  align="left" width=40>

Arduino is avilable for a variety of platforms. To ensure compatiblity with the demos in this repository, the latest version should be installed.

The Arduino application is available for a variety of platforms and is available online from Arduino. Download the application from the Arduino website using this [link](https://www.arduino.cc/en/Main/Software).

### Install the TensorFlowLite Library

The examples utilize the TensorFlowLite Arduino libary, which is installed using the Arduino Library Manager. 

To install this library, use the following steps:
<img src="resource/TFL_Install.png"  align="right" width=350>
* In Arduino, select the "Manage Libraries..." menu item. ***Tools > Manage Libraries...***
* In the Library Manager interface, search for tensorflow
* Select the library **Arduino_TensorFlowLite** by **TensorFlow Authors**
* Select the *non-precompiled* version of the libary
* Select the **Install** button to install the library

### Install the SparkFun Boards Package

Load the SparkFun Boards package into the Arduino Board Manger.

To install package, use the following steps:

* In Arduino, open the Preferences menu item. ***File > Preferences***, (macOS) ***Arduino > Preferences***
* Add the following path to the ***Additional Boards Manager URLs:*** path in preferences.

  ```https://raw.githubusercontent.com/sparkfun/Arduino_Boards/master/IDE_Board_Manager/package_sparkfun_index.json```

* Select the ***OK*** button to save the preferences.

<img src="resource/BoardPacakgeURL.png" >

#### Install the SparkFun Artemis Boards Package 

Once the location of the SparkFun boards package is set in the preferences, the board definition package for the SparkFun Apollo3 boards must be installed. 

To install package, use the following steps:
<img src="resource/BoardManager.png"  align="right" width=350>
* In Arduino, open the Preferences menu item. ***Tools > Board "..." > Manage Boards...***
* Search for *SparkFun*
* Select the **SparkFun Apollo3 Boards" package 
* Close the dialog
* Select the SparkFun Edge Board. ***Tools > Boards "..." > SparkFun RedBoard Artemis ATP***
* Set the Bootloader to the ***SparkFun Variable Loader***. ***Tools > Bootloader "..." > SparkFun Variable Loader..."

Running an Example
------------------

### Configure the Hardware
* Plug USB cable into computer
* Plug in Artemis ATP board to adpater


### Configure the Software
* Install and setup Arduino as described [above](#software-setup).
* Download (or clone) this repo to favorite location
* Open Arduino
* Open an example from this repo through Arduino by clicking on the ```.ino``` file in the example directory
  * ```micro_speech```
* Select the ```SparkFun RedBoard Artemis ATP``` board (Tools->Board under 'SparkFun Apollo3')
* Select the proper port to connect with the baord (Tools->Port)
  * Windows - COM Port
  * Linux - /dev/ttyUSB*, where * is a number. NOTE: Permissions on this device needs to include user read and write (chmod 666)
  * macOS - /dev/cu.usbserial* 
* Change the **Bootloader** from *Ambiq Secure Bootloader (Default)* to *SparkFun Variable Loader (Enable w/ Artemis Bootloader)* (Tools->Bootloader)
  * (Your boards have received the upgraded bootloader already)
* Change the ```SVL Baud Rate``` from *921600* to *230400*

### Upload
* Compile with the ```Verify``` button (checkmark symbol)
* Upload with the ```Upload``` button (arrow symbol)
  * If uploading fails try lowering the bootloader baud rate
* Note: You will see some warnings from the compiler, these can be ignored.
* Note: The bootloader attempts to upload for 3 times. If all three attempts fail, try adjusting the baud rate. 

### Serial Monitor
* Open the Serial Monitor by clicking on the magnifying glass icon (top right) or (Tools->Serial Monitor)

## Training a Speech Model
The micro speech example has a model that is trained to recognize "Yes" and "No". An example of how to train a new model based on Google collected sample phrases is included in the tensorflow micro_speech example repository. The method listed utilizes Google Colaboratory to run the training session - an Jypter notebooks based system that presents a Python based notebook and abstracts the management of compute resources.

The notebook to run the training for this example is contained in the tensorflow github repository at this [location.](https://github.com/tensorflow/tensorflow/blob/59c06b9016700dbf1ab0cefc062d247345cdd0f0/tensorflow/lite/micro/examples/micro_speech/train_speech_model.ipynb)
