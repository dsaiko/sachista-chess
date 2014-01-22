export CC="icc"
export CXX="icpc"
export CFLAGS="-march=native -O3 -no-prec-div -fno-alias -pipe"
export CXXFLAGS="${CFLAGS}"
export LDFLAGS="-Wl,-O1,--sort-common,--as-needed"
export AR="xiar"
export LD="xild"

./build.sh