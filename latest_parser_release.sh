#!/bin/bash

REPO="sQeeZ-scripting-language/parser"
REPO_DIR="./parser-lib"
INCLUDE_DIR="./include/parser"

if [ -d "$INCLUDE_DIR" ]; then
  rm -rf "$INCLUDE_DIR"
fi
mkdir -p "$INCLUDE_DIR"
mkdir -p "$REPO_DIR"

LATEST_RELEASE=$(curl -s "https://api.github.com/repos/$REPO/releases/latest")

if [[ "$OSTYPE" == "darwin"* ]]; then
  ZIP_URL=$(echo "$LATEST_RELEASE" | grep -o "https://.*sQeeZ-Parser-macos-.*\.zip" | head -n 1)
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
  ZIP_URL=$(echo "$LATEST_RELEASE" | grep -o "https://.*sQeeZ-Parser-linux-.*\.zip" | head -n 1)
elif [[ "$OSTYPE" == "msys"* ]]; then
  ZIP_URL=$(echo "$LATEST_RELEASE" | grep -o "https://.*sQeeZ-Parser-windows-.*\.zip" | head -n 1)
else
  echo "Unsupported OS."
  exit 1
fi

if [ -z "$ZIP_URL" ]; then
  echo "No matching asset found."
  exit 1
fi

TEMP_DIR=$(mktemp -d)

curl -L -o "$TEMP_DIR/sQeeZ-Parser.zip" "$ZIP_URL"

unzip "$TEMP_DIR/sQeeZ-Parser.zip" -d "$REPO_DIR"

mv "$REPO_DIR/"*/libsQeeZ-Parser-Lib.a "$REPO_DIR/"
mv "$REPO_DIR/"*/sQeeZ-Parser-Lib.lib "$REPO_DIR/"
mv "$REPO_DIR/parser/"* "$INCLUDE_DIR/"

rm -rf "$REPO_DIR/"*/sQeeZ-Parser-Exe
rm -rf "$REPO_DIR/"*/sQeeZ-Parser-Exe.exe
rm -rf "$TEMP_DIR"

find "$REPO_DIR" -type d -empty -delete

echo "Latest files have been downloaded and extracted to $REPO_DIR."