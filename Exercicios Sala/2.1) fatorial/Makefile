CXX = g++

CFLAGS= -fsanitize=address -O1 -fno-omit-frame-pointer -g -Wall -Wshadow -Wno-unused-result \
-Wno-sign-compare -DNDEBUG -D_FORTIFY_SOURCE=2 -O2 -Wl,-O2 -Wl,--sort-common \
-Wl,--as-needed -Wl,-z,relro -Wl,-z,now -Wl,--disable-new-dtags -Wl,--gc-sections

CXXFLAGS= -fsanitize=address -O1 -fno-omit-frame-pointer -g -Wall -Wshadow -Wno-unused-result \
-Wno-sign-compare -DNDEBUG -D_FORTIFY_SOURCE=2 -O2 -Wl,-O2 -Wl,--sort-common \
-Wl,--as-needed -Wl,-z,relro -Wl,-z,now -Wl,--disable-new-dtags -Wl,--gc-sections

clear:
	find . -maxdepth 1 -type f -executable -exec rm {} +