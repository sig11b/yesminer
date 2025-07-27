# CLEAN
make distclean || echo clean

# BUILD
autoreconf -i
./configure $*
make -j$(nproc)

