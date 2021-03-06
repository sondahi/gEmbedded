#!/bin/bash

TARGET_HEADERS="./src/main/c/native/jni/include"

API_JAR="./target/lib/*.jar"

SOURCE_CLASSES="./src/main/java/com/comert/gEmbedded/nativeinterface/*.java
                ./src/main/java/com/comert/gEmbedded/nativeinterface/util/*.java"

TARGET_CLASSES="target/classes"

javac -h ${TARGET_HEADERS} -cp ${API_JAR} ${SOURCE_CLASSES} -d ${TARGET_CLASSES}
