all: filesystem-dropper http-useragent http-domain delete-registry create-registry

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

clean:
	rm bin/*.exe
