# OpenDaVINCI - Experiment to study matching recordings from the real world with simulation data to extract matching feature sets

This example was realized with OpenDaVINCI and demonstrates how to use the
framework in combination with the simulation environment to extract matching
features from real world sensor data recordings. The following instructions
were tested with Ubuntu 14.04 LTS; further information for other platforms or
how to build OpenDaVINCI are available here: http://opendavinci.readthedocs.org/en/latest.

Further background about this project is provided here: http://arxiv.org/abs/1406.7768

This project demonstrates how to design simulation studies with OpenDaVINCI.

## How to build

A simulation can be designed as a stand-alone application or embedded
into a unit test environment. This example demonstrates how to create
a CLI simulation using OpenDaVINCI and odSimulation; in addition, the
simulation is also embedded into a CxxTest test suite to be automatically
executed using a ``make test`` command.

Install required libraries:

    $ sudo apt-get install build-essential cmake git libcv-dev libhighgui-dev freeglut3 freeglut3-dev libboost-dev libopencv-photo-dev libopencv-contrib-dev 

Install OpenDaVINCI according to the following instructions: http://opendavinci.readthedocs.org/en/latest/installation.pre-compiled.html#adding-opendavinci-to-your-ubuntu-linux-distribution

Install libautomotivedata:

    $ sudo apt-get install libautomotivedata

Create a build folder within the source tree of your local working copy:

    $ mkdir build

Change to the build folder:

    $ cd build

Create the build files:

    $ cmake ..

Build the sources:

    $ make

Run the binary:

    $ ./simulation-model-matching

![Screenshot](https://github.com/se-research-studies/simulation-model-matching/blob/master/Screenshot.png)
