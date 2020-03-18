blessings-emcc:
	git submodule init
	git submodule update
	cd blessings && ./configure --prefix "$$(dirname "$$(readlink -m emcc)")" CC=emcc
	cd blessings && make uninstall && make clean && make blessings_static && make install
