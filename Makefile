all: filesystem-dropper

filesystem-dropper: ./filesystem-tests/dropper.c
	wine gcc.exe filesystem-tests/dropper.c -o bin/dropper.exe

clean:
	rm bin/*.exe
