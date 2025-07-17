# CLEAN
make distclean || echo clean

# BUILD
autoreconf -i
./configure CFLAGS="-Wall -O2 -fomit-frame-pointer $1"
make -j$(nproc)
#strip -s sugarmaker

# CHECK STATIC
#file sugarmaker | grep "dynamically linked"
