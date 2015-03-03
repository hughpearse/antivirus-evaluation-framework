all: filesystem-dropper http-useragent

filesystem-dropper: ./filesystem-tests/dropper.c
	wine gcc.exe filesystem-tests/dropper.c -o bin/dropper.exe

http-useragent: ./network-tests/http-useragent.c
	wine gcc.exe network-tests/http-useragent.c -lws2_32 -o bin/http-useragent.exe

clean:
	rm bin/*.exe
