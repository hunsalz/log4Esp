#!/bin/bash

function build_sketches() {
    
    local arduino=$1
    local srcpath=$2
    local sketches=$(find $srcpath -name *.ino)
    for sketch in $sketches; do
        local sketchdir=$(dirname $sketch)
        echo -e "\n\n ------------ Building $sketch ------------ \n\n";
        $arduino --verify $sketch;
        local result=$?
        if [ $result -ne 0 ]; then
            echo "Build failed ($1)"
            return $result
        fi
    done
}