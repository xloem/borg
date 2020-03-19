CXXFLAGS=-std=c++14
LIBS=-lblessings -lblessings_utf8

web/borg.html: borg.cpp external/emterm/node_modules makefile
	cd web; em++ -s EXIT_RUNTIME=1 -s DISABLE_EXCEPTION_CATCHING=0 --js-library ../external/emterm/library_syscall.js --js-library ../external/emterm/library_fs.js --js-library ../external/emterm/library_emterm.js --shell-file ../external/emterm/shell_emterm.html $(CXXFLAGS) $(LIBS) ../"$<" -o ../"$@"

external/emterm/node_modules:
	git submodule init
	git submodule update
	cd external/emterm && npm install

blessings-emcc:
	git submodule init
	git submodule update
	#cd external/blessings && ./configure --prefix "$$(dirname "$$(command -v emcc)")/system" CC="emcc -s DISABLE_EXCEPTION_CATCHING=0" AR=emar
	#cd external/blessings && make clean 
	cd external/blessings && make blessings_static blessings_utf8_static && make install
