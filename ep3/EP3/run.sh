#!/bin/bash

rm Whiteboard/*.class
javac Whiteboard/*.java

rmiregistry &
java Whiteboard.WbAdmin
