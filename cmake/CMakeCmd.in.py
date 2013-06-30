#! /usr/bin/env python

generator = "${GENERATOR}"

from subprocess import call

if generator == "" :
	call(["cmake", "."])
else :
	call(["cmake", "-G", generator, "."])
