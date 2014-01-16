#!/bin/bash

VER=$( git describe )
DATE=$( date "+%Y-%m-%d %H:%M" )

cat > movegenerator/version.h <<EOF

#ifndef SACHISTA_CHESS_VERSION_H
#define SACHISTA_CHESS_VERSION_H

#define IMPLEMENTATION_VERSION "${VER}"
#define IMPLEMENTATION_DATE "${DATE}"

#endif


EOF



