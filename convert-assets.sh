#!/bin/bash

cd assets/
for file in $(ls -1 *.png)
do
	/home/nick/.small_programs/png2gba -p -t -o "../include/assets/$(basename $file .png).h" $file
done
