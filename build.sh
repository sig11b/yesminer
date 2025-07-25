# CLEAN
make distclean || echo clean

# BUILD
autoreconf -i
./configure CFLAGS="-Wall -O3 -fomit-frame-pointer -march=native $1"
make -j$(nproc)

