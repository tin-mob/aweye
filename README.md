**Aweye**
================================

*Aweye will ease your eyes.*

This is a work in progress.

Aweye is a small app to remind you to take breaks when you are happily
working or playing on your computer and forget the time. You only need
to start it and it will notify you if you forget to stop. Otherwise, it
will stay in the background and watch you using a webcam.

(versions using the power state or a punch system is in the [roadmap](github.com/tin-mob/aweye/issues)
for shy people)

Required
-------------------------

*	[WxWidgets 2.9.5](http://www.wxwidgets.org/)
*	[OpenCV](http://opencv.org/)
	(minimally core, objdetect imgproc and highgui)
*	A Webcam (for now) 

Installation
-------------------------

*@todo windows + test everything* 

*	Download the project
*	Go to the project download directory
*	mkdir build
*	cd build
*	cmake ..

After that, you have a few options:

1.	make install (no support for uninstalling).
2.	make package + install with your favourite package manager
	(deb only for now).

Documentation
-------------------------

The app is rather straightforward.  You can issue commands using the
menu or by right clicking the icon :

*	Start/Stop to start/stop(!) the checking.
*	Mute/Resume to whether to pester you when it should be pause time.
*	Options to tweak the settings.
*	About to display a bunch of legalese.
*	You can guess what Exit does.

Clicking the X button on the title bar minimize the app, keeping only
the icon. The icon will change colour depending on the status.

*	Black: Stopped.
*	Green: Enjoy the computer.
*	Yellow: You should get away soon if you don't want a notice.
*	Red: Too late!

A thing to note is that using the webcam to determine if you are
there is not always right. Therefore, it takes a few tries before it
changes state, to be certain that it is not a fluke.

Anyway, you will [soon](github.com/tin-mob/aweye/issues) be able to
hover over everything to see what it does.

Contributing
-------------------------

This is mainly a personal learning project. I am also new to this
git/github thing. If you have feedback or suggestions, you can use the
[issues list](github.com/tin-mob/aweye/issues) and hopefully I will be able to answer (I learn as I go).

License
-------------------------

Copyright (C) 2013 - Robert Morin

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
[GNU General Public License](COPYING.txt) for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


Note
-------------------------

webcam.ico is part of WPZOOM Developer Icon Set by WPZOOM,
designed by David Ferreira. <http://www.wpzoom.com>
webcam- * .png are derived from webcam.ico.

The icons are licensed under a Creative Commons Attribution-Share Alike
3.0 Unported License <http://creativecommons.org/licenses/by-nc-sa/3.0/>.
