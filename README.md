Introduction
============
I have done this project in 2 parts. 
The first one is an interactive mandelbrot set, in which
you can zoom in, zoom out, move around, and reset and so on.
The second part is focused on increasing precision and a different way of execution
which will count periodicity and also generate a video of the mandelbrot animation.

First Part
===========
The code is in `mandelbrot_interactive.cpp`

How to run this code
===========
Run the code by running the makefile by 
	$ make -f part1_make 
Execute the executable by : ```./interactive_mandelbrot```

Second Part
===========

Calculating Mandelbrot using 2 different ways.
I have tried to make a mandelbrot animation by stacking up pictures of
mandelbrot by continuously zooming in.

mandel:
 - straight forward "long double" based mandelbrot
 - this is obviously the fastest implementation but has limited precision

mandel_dd:
 - mandelbrot using custom double double math
 - this is the fastest implementation given double double precision

The code is in `mandel.cpp` and `mandel_dd.cpp`.
The custom double double math is in `doubledouble.h`.

How to run the code
==============

Compile and form the executables by running `make`.

How to obtain a single image 
==============

The bash script `make_image.sh` takes arguments : width, height, coordinates and
magnification. Output is in png format.

How to generate video of Mandelbrot zoom
==============

The bash script (with a small python helper) `run.sh` will generate and
execute a list of commands to create a zooming sequence of images.

You can create a video of the resulting sequence using:

	$ ffpmpeg -i out_%05d.png mandelbrot.mp4

Or a gif animation by using:

	$ convert -delay 20 -loop 0 out_*.png mandelbrot.gif


Algorithms
==========

Lastly, I have also implemented 2 algorithms for cycle detection.
These are inspired from https://en.wikipedia.org/wiki/Cycle_detection
This can be used for periodicity checking in Mandelbrot set.
The code for this is in `brents_alg.cpp` and `floyds_alg.cpp`


G-drive link for demo :
https://drive.google.com/drive/folders/11TNLOiSgG6gwRmmexCYb4dCwqKvntYxw?usp=sharing