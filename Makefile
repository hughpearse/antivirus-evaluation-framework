all: filesystem-dropper http-useragent http-domain delete-registry create-registry take-screenshot malloc-crc32 list-processes pe-inject-by-midox pe-inject-by-zwclose7 contigious-malloc

filesystem-dropper: ./filesystem-tests/dropper.c
	wine gcc.exe filesystem-tests/dropper.c -o bin/dropper.exe

http-useragent: ./network-tests/http-useragent.c
	wine gcc.exe network-tests/http-useragent.c -lws2_32 -o bin/http-useragent.exe

http-domain: ./network-tests/http-domain.c
	wine gcc.exe network-tests/http-domain.c -lws2_32 -o bin/http-domain.exe

delete-registry: ./filesystem-tests/delete-registry.c
	wine gcc.exe filesystem-tests/delete-registry.c -o bin/delete-registry.exe

create-registry: filesystem-tests/create-registry.c
	wine gcc.exe filesystem-tests/create-registry.c -o bin/create-registry.exe

take-screenshot: ./graphical-tests/screenshot.cpp
	wine g++.exe ./graphical-tests/screenshot.cpp -lgdiplus -lgdi32 -lws2_32 -Wno-write-strings -o ./bin/screenshot.exe

malloc-crc32: memory-tests/malloc.c
	wine gcc.exe memory-tests/malloc.c -o bin/malloc.exe

contigious-malloc: memory-tests/contigious-malloc.c
	wine gcc.exe memory-tests/contigious-malloc.c -o bin/contigious-malloc.exe

contigious-variables: memory-tests/contigious-variables.c
	wine gcc.exe memory-tests/contigious-variables.c -o bin/contigious-variables.exe

list-processes: ./process-management/list-processes.cpp
	wine g++.exe ./process-management/list-processes.cpp -Wno-write-strings -lws2_32 -o ./bin/list-processes.exe

pe-inject-by-midox: memory-tests/pe-inject-by-midox.cpp
	wine g++.exe -mconsole -mwindows -e _mainCRTStartup memory-tests/pe-inject-by-midox.cpp -lws2_32 -lwinmm -DUNICODE -o bin/pe-inject-by-midox.exe

pe-inject-by-zwclose7:
	wine g++.exe memory-tests/pe-inject-by-zwclose7.cpp -lws2_32 -o bin/pe-inject-by-zwclose7.exe

clean:
	rm bin/*.exe
