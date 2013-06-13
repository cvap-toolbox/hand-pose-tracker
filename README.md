Hand Pose Estimation and Rendering
==========================================

Build the project:
    mkdir $HAND_PATH/Hand/handpose/build
    cd $HAND_PATH/Hand/handpose/build
    cmake ..
    make -j5

Create the image database:
    build/scene/renderhand 

Contributors:
-------------

* Javier Romero [1]
* Mihai Damaschin

[1]: https://github.com/libicocco


Discussion:
-----------

Lots of things to do still!


TODO:
-----

1. Improve the usability.

2. Improve robustness.

3. Integrate the rendering engine to provide online corrections to the discriminative approach.
