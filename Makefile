all: create-target-dir controls filesystem-dropper http-useragent http-domain delete-registry create-registry take-screenshot malloc-crc32 contigious-malloc contigious-variables list-processes pe-inject-by-midox pe-inject-by-zwclose7 keylogger-to-logfile

create-target-dir:
	mkdir -p ./bin

controls: ./EICAR/EICAR.com ./EICAR/eicar-with-padding.com
	cp ./EICAR/* ./bin/

filesystem-dropper: ./src/filesystem-tests/dropper.c
	wine gcc.exe ./src/filesystem-tests/dropper.c -o ./bin/dropper.exe

http-useragent: ./src/network-tests/http-useragent.c
	wine gcc.exe ./src/network-tests/http-useragent.c -lws2_32 -o ./bin/http-useragent.exe

http-domain: ./src/network-tests/http-domain.c
	wine gcc.exe ./src/network-tests/http-domain.c -lws2_32 -o ./bin/http-domain.exe

delete-registry: ./src/filesystem-tests/delete-registry.c
	wine gcc.exe ./src/filesystem-tests/delete-registry.c -o ./bin/delete-registry.exe

create-registry: ./src/filesystem-tests/create-registry.c
	wine gcc.exe ./src/filesystem-tests/create-registry.c -o ./bin/create-registry.exe

take-screenshot: ./src/graphical-tests/screenshot.cpp
	wine g++.exe ./src/graphical-tests/screenshot.cpp -lgdiplus -lgdi32 -lws2_32 -Wno-write-strings -o ./bin/screenshot.exe

malloc-crc32: ./src/memory-tests/malloc.c
	wine gcc.exe ./src/memory-tests/malloc.c -o ./bin/malloc.exe

contigious-malloc: ./src/memory-tests/contigious-malloc.c
	wine gcc.exe ./src/memory-tests/contigious-malloc.c -o ./bin/contigious-malloc.exe

contigious-variables: ./src/memory-tests/contigious-variables.c
	wine gcc.exe ./src/memory-tests/contigious-variables.c -o ./bin/contigious-variables.exe

list-processes: ./src/process-management/list-processes.cpp
	wine g++.exe ./src/process-management/list-processes.cpp -Wno-write-strings -lws2_32 -o ./bin/list-processes.exe

pe-inject-by-midox: ./src/memory-tests/pe-inject-by-midox.cpp
	wine g++.exe -mconsole -mwindows -e _mainCRTStartup ./src/memory-tests/pe-inject-by-midox.cpp -lws2_32 -lwinmm -DUNICODE -o ./bin/pe-inject-by-midox.exe

pe-inject-by-zwclose7: ./src/memory-tests/pe-inject-by-zwclose7.cpp
	wine g++.exe ./src/memory-tests/pe-inject-by-zwclose7.cpp -lws2_32 -o ./bin/pe-inject-by-zwclose7.exe

keylogger-to-logfile: ./src/peripherals-tests/keyboard-input.cpp
	wine g++.exe ./src/peripherals-tests/keyboard-input.cpp -o ./bin/keyboard-input.exe

clean:
	rm -rf ./bin
