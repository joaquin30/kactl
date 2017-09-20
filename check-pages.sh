#!/bin/bash
set -euo pipefail
pages=$(pdfinfo kactl.pdf | awk '/Pages/ { print $2 }')
max=26
if [[ $pages -gt $max ]]; then
	echo "Too many pages: $pages > $max"
	exit 1
fi
