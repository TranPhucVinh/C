#!/bin/bash

set -e

sudo gcc kmess.c -o kmess
sudo chmod +x kmess
sudo cp kmess /usr/local/bin

echo "Done installation. type kmess to run"