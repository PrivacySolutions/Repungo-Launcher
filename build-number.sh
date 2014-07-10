#!/bin/bash
number=`cat build_number`
let number++
echo "$number" | tee build_number #<-- output and save the number back to file
echo "#define BUILD ""$number" > build.h
