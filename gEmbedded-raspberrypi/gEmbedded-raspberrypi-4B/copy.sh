#!/bin/bash

SOURCE_NATIVE="/root/native32/cmake-build-release/src/libgEmbeddedRasPi4B32.so"
TARGET_NATIVE="./target/classes"

scp root@192.168.1.12:${SOURCE_NATIVE} ${TARGET_NATIVE}