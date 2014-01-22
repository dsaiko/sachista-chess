export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

export CFLAGS="-O3"
export CXXFLAGS="${CFLAGS}"
export LDFLAGS="-Wl,-O3"

./build.sh