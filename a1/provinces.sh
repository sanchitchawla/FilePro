#!/bin/bash

echo 'Bangkok'
curl -sS https://en.wikipedia.org/wiki/Provinces_of_Thailand?action=raw | grep "Province|" | sed -n '3,78p' | grep -o "Province|.*" | cut -c10- | tr -d  ']]'