#!/bin/bash 

grep -r --include=*.{cc,h,s} "wait(0)" >> changelog.txt


