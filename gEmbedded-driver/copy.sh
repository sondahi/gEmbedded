#!/bin/bash

#SOURCE_NATIVE_64="/usr/lib/libgEmbeddedRaspi4B64.so"
SOURCE_NATIVE_32="/usr/lib/libgEmbeddedRaspi4B32.so"

TARGET_NATIVE="./target/classes"

#scp root@192.168.1.13:${SOURCE_NATIVE_64} ${TARGET_NATIVE}
scp root@192.168.1.12:${SOURCE_NATIVE_32} ${TARGET_NATIVE}