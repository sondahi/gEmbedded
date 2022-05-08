#!/bin/bash

TARGET_NATIVES="./src/main/c/native/include"

API_JAR="./target/lib/*.jar"

SOURCE_CLASSES="./src/main/java/com/comert/gEmbedded/nativeinterface/*.java
                ./src/main/java/com/comert/gEmbedded/nativeinterface/util/*.java"

TARGET_CLASSES="target/classes"

javac -h ${TARGET_NATIVES} -cp ${API_JAR} ${SOURCE_CLASSES} -d ${TARGET_CLASSES}
