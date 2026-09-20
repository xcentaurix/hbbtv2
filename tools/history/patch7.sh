#!/bin/bash
set -euo pipefail
cd /home/alpha/wpe-src/wpewebkit-2.54.0
LAYER=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-browser/wpewebkit/files
git checkout -q -- Source/WebCore/platform/MIMETypeRegistry.cpp Source/WebCore/dom/DOMImplementation.cpp
F1=Source/WebCore/platform/MIMETypeRegistry.cpp
F2=Source/WebCore/dom/DOMImplementation.cpp
# 1) displayable type
grep -c '            "application/xhtml+xml"_s,' $F1 | grep -qx 1
sed -i 's|^            "application/xhtml+xml"_s,$|            "application/xhtml+xml"_s,\n            "application/vnd.hbbtv.xhtml+xml"_s, // HbbTV applications (ETSI TS 102 796), an XHTML document|' $F1
# 2) parsed as XHTML
grep -c 'if (equalLettersIgnoringASCIICase(contentType, "application/xhtml+xml"_s))' $F2 | grep -qx 1
sed -i 's|    if (equalLettersIgnoringASCIICase(contentType, "application/xhtml+xml"_s))$|    if (equalLettersIgnoringASCIICase(contentType, "application/xhtml+xml"_s) \|\| equalLettersIgnoringASCIICase(contentType, "application/vnd.hbbtv.xhtml+xml"_s))|' $F2
git diff --stat
{
  echo "From: HbbTV2 experiment <noreply@localhost>"
  echo "Subject: [PATCH] Treat application/vnd.hbbtv.xhtml+xml as XHTML"
  echo
  echo "HbbTV applications are commonly served as application/vnd.hbbtv.xhtml+xml. WebKit does not know the type: the"
  echo "main resource is refused (\"Frame load interrupted\"), and it would not be parsed as XHTML anyway. Make it a"
  echo "displayable non-image type and create an XHTML document for it."
  echo
  echo "---"
  git diff --no-color -- $F1 $F2
} > $LAYER/0007-Treat-application-vnd.hbbtv.xhtml-xml-as-XHTML.patch
git diff --no-color -- $F1 $F2 | grep '^[+-]' | grep -v '^+++\|^---'
