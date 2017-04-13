#!/bin/bash
if [ -f "./AES" ]; then rm ./AES; fi
if [ -f "./main.o" ]; then rm ./main.o; fi
if [ -f "./aes.o" ]; then rm ./aes.o; fi
make
./AES