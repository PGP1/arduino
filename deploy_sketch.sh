#!/bin/bash

arduino-cli compile --fqbn arduino:avr:uno controller_main
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno controller_main -v
