#! /usr/bin/env python

generator = "${GENERATOR}"

from subprocess import call

if generator == "" :
	call(["cmake", "-DCMAKE_BUILD_TYPE='Debug'", "."])
else :
	call(["cmake", "-DCMAKE_BUILD_TYPE='Debug'", "-G", generator, "."])
