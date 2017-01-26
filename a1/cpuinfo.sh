#!/bin/bash

grep -i "model name" /proc/cpuinfo | cut -c14-53