# OpenDaVINCI - Experiment to study matching recordings from the real world with simulation data to extract matching feature sets

This example was realized with OpenDaVINCI and demonstrates how to use the
framework in combination with the simulation environment to extract matching
features from real world sensor data recordings. The following instructions
were tested with Ubuntu 14.04 LTS; further information for other platforms or
how to build OpenDaVINCI are available here: http://opendavinci.readthedocs.org/en/latest.

Further background about this project is provided here: http://arxiv.org/abs/1406.7768

This project demonstrates how to design simulation studies with OpenDaVINCI.

A simulation can be designed as a stand-alone application or embedded
into a unit test environment. This example demonstrates how to create
a CLI simulation using OpenDaVINCI and odSimulation; in addition, the
simulation is also embedded into a CxxTest test suite to be automatically
executed using a ``make test`` command.

To build this example, create a build folder, run make within that folder referring
to the sources, and call make.
