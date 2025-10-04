build:
	cc -O0 -g -pedantic -std=c89 main.c -o main

check:
	cc -O0 -g -pedantic -std=c89 -fsanitize=address,undefined -fno-omit-frame-pointer main.c -o main
