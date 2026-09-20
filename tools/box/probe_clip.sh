#!/bin/sh
# probe_clip.sh <url> : which elementary streams does the clip contain (uridecodebin -> fakesinks, no decoder used)
timeout 20 gst-launch-1.0 -q uridecodebin uri="$1" name=d d. ! queue ! fakesink d. ! queue ! fakesink 2>&1 | head -3 >/dev/null
timeout 20 gst-launch-1.0 -v uridecodebin uri="$1" name=d expose-all-streams=false d. ! queue ! fakesink async=false 2>&1 | grep -o "caps = [a-z/0-9-]*" | sort -u | head
