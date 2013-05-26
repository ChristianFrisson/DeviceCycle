DeviceCycle
===========

by Christian Frisson: http://tcts.fpms.ac.be/~frisson
numediart Institute in Digital Art Technologies: http://www.numediart.org
University of Mons (UMONS): http://www.umons.ac.be

Description
-----------

DeviceCycle is a toolbox for PureData/flext aiming at facilitating the rapid prototyping of gestural interfaces using off-the-shelf devices, so as not to reinvent the (jog) wheel. It currently supports the following devices:

* Apple multitouch trackpad (on Macbooks or with a Magic Trackpad) (under OSX 10.6+ only)
* 3Dconnexion Space Navigator 3D mouse
* Contour Design Shuttle Xpress and Pro2 jog wheels
* Novint Falcon force-feedback 3D mouse

For more information, check:
* the DeviceCycle paper from the NIME 2010 conference proceedings: http://www.nime.org/proceedings/2010/nime2010_473.pdf
* the DeviceCycle page on the numediart website: http://www.numediart.org/tools/devicecycle

Changelog
---------

* v.0.1b (26/05/2013): now available on https://github.com/ChristianFrisson/DeviceCycle
* v.0.1 (18/06/2010): first release, tested on OSX Leopard only 

To do
-----

* CMake integration (flext/PureData detection, automated installation)
* Free-form interfaces support: Kinect/Xtion gesture recognition with https://github.com/ChristianFrisson/FUBIOSC

Requirements
------------

* pd-extended from version 0.41.4 onwards (source and binary): http://www.puredata.info
* flext * C++ development layer for Pure Data and Max/MSP: http://puredata.info/Members/thomas/flext/
* (optional, if you have a Novint Falcon) np_nifalcon flext object: http://sourceforge.net/projects/libnifalcon
* (optional, if you have a Novint Falcon) Edgar Berdahl's HSP toolbox: https://ccrma.stanford.edu/~eberdahl/Projects/HSP/index.html

Installation
------------

* Retrieve and install the pd-extended binary. Retrieve the pd-vanilla source of the same version and copy it on a "src" sub directory of the pd-extended binary installation at http://www.puredata.info
* Retrieve and compile flext at http://puredata.info/Members/thomas/flext/. Using OSX, you can alternatively copy the compiled flext libraries from the flext/ sub directory of this DeviceCycle toolbox to /usr/local/lib.
* (Optional, if you have a Novint Falcon) Retrieve and install the [np_nifalcon] flext object at http://sourceforge.net/projects/libnifalcon. Using OSX, it is already provided in the extra/ sub directory of this DeviceCycle toolbox.
* Copy the contents of extra/ of this DeviceCycle toolbox to the required folder of your pd-extended installation.
* (OSX-only) If you want to (re-)compile the included flext fingerpinger object, retrieve and compile flext, and copy the contents of src/ to a sub directory of your flext installation, for instance under test/.

Platform Specifics Issues
-------------------------

* OS X: For your convenience, the flext library and compiled objects of [fingerpinger], [hidio] (source present on pd-extended but not compiled), and [np_nifalcon] are provided at http://www.numediart.org/tools/devicecycle.
* Linux: Not yet tested.
* Windows: Not yet tested.

Licensing
---------

Unless otherwise noted, all content (abstractions, objects source code, help patches) are provided under the GPL License.

Copyrights
---------

DeviceCycle, Copyright 2010-present Christian Frisson / numediart Institute
hidio, Copyright 2007 Hans-Christoph Steiner, Olaf Matthes and David Merrill
flext * C++ layer for Max/MSP and pd (pure data) externals, Copyright 2001-2005 Thomas Grill
fingerpinger, Copyright 2009 Erling Ellingsen (initial code), 2009 Michael & Max Egger (Max object) and 2010 Christian Frisson (flext port)
HSP, Copyright 2008-2010 Edgar Berdahl
libnifalcon, Copyright 2007-2009 Kyle Machulis/Nonpolynomial Labs
libnifalcon Kinematics Core, Copyright 2007-2008 Kevin Ouellet, 2009 Alastair Barrow, 2007-2009 Kyle Machulis