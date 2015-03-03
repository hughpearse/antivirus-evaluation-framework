all: filesystem-dropper http-useragent http-domain

filesystem-dropper: ./filesystem-tests/dropper.c
	wine gcc.exe filesystem-tests/dropper.c -o bin/dropper.exe

http-useragent: ./network-tests/http-useragent.c
	wine gcc.exe network-tests/http-useragent.c -lws2_32 -o bin/http-useragent.exe

http-domain: ./network-tests/http-domain.c
	wine gcc.exe network-tests/http-domain.c -lws2_32 -o bin/http-domain.exe

clean:
	rm bin/*.exe
