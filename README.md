## How to build

Install required libraries:

    $ sudo apt-get install build-essential cmake git libcv-dev libhighgui-dev freeglut3 freeglut3-dev libboost-dev libopencv-photo-dev libopencv-contrib-dev libjsoncpp-dev sqlite3 libsqlite3-dev

Install OpenDaVINCI according to the following instructions: http://opendavinci.readthedocs.org/en/latest/installation.pre-compiled.html#adding-opendavinci-to-your-ubuntu-linux-distribution

Install the OpenDaVINCI simulation environment:

    $ sudo apt-get install odsimulation-odsimtools

Create a build folder within the source tree of your local working copy:

    $ mkdir build

Change to the build folder:

    $ cd build

Create the build files:

    $ cmake ..

Build the sources:

    $ make

To run the tests you need to install and build Google Test:

    $ sudo apt-get install libgtest-dev
    $ cd /usr/src/gtest
    $ sudo cmake CMakeLists.txt
    $ sudo make
    $ sudo cp *.a /usr/lib

