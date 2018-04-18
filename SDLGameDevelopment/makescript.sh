#!/usr/bin/env bash

JOBS=$1;

if [ "x" == "x$JOBS" ]; then
	make
else
	make -j$JOBS
fi
