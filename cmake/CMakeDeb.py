#! /usr/bin/env python
########################################################################
#    Copyright: 2013, Robert Morin
#
#    This file is part of Aweye.
#
#    Aweye is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Aweye is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Aweye.  If not, see <http://www.gnu.org/licenses/>.
#
########################################################################

from argparse import ArgumentParser
from os import path, pardir
from subprocess import call
from sys import argv

parser = ArgumentParser(description='Cmake debug command shortcut.')
parser.add_argument('--generator', '-g', '-G', dest='generator', default='',
                   help='generator used by cmake (default: let cmake choose)')

args = parser.parse_args()
path = path.abspath(path.join(path.split(argv[0])[0], pardir))

if args.generator == "" :
	call(["cmake", "-DCMAKE_BUILD_TYPE='Debug'", path])
else :
	call(["cmake", "-DCMAKE_BUILD_TYPE='Debug'", "-G", args.generator, path])
