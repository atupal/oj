#!/bin/bash
find -type f | xargs file  | grep "ELF 64-bit" | awk '{split($1,a, ":"); print a[1]}' | xargs rm
