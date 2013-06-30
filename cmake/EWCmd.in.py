#! /usr/bin/env python

from subprocess import call
call(["./EyesWatcher", "-c", "${CONFIG_PATH}", "-d", "${DATA_DIR}"])

