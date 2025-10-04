#!/bin/bash

cp /data/checker/image_check .
mv * ../src/
cd ../src
chmod +x tasks/image_editor/grader

date

./check