#!/bin/bash

rm result.txt
touch result.txt

./chicago_develop -scene ./scenes/research1.obj -research >> result.txt
./chicago_develop -scene ./scenes/research2.obj -research >> result.txt
./chicago_develop -scene ./scenes/research3.obj -research >> result.txt
./chicago_develop -scene ./scenes/research4.obj -research >> result.txt
