#!/bin/bash

# Usage : build.sh src_path port [emsdk_path]

# Here are the exported methods with a leading '_' 
EXPORT=_greetings,_greetingsAsync

EMSDK_PATH=${3:-/workspaces/emsdk}
CC=emcc
SRC="$1/*.cpp"
INC=
METHODS=ccall
OPT="-gsource-map -sASYNCIFY"
OUTPUT=$1/www/a.out.js

source $EMSDK_PATH/emsdk_env.sh
$CC $SRC -o $OUTPUT $OPT $INC -sEXPORTED_FUNCTIONS=$EXPORT -sEXPORTED_RUNTIME_METHODS=$METHODS

echo Live preview should be listening on https://${CODESPACE_NAME}-$2.${GITHUB_CODESPACES_PORT_FORWARDING_DOMAIN}/www/

