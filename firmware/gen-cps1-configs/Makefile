CC=gcc

gen-cps1-configs: gen-cps1-configs.c
	$(CC) -o gen-cps1-configs gen-cps1-configs.c

run: gen-cps1-configs
	./gen-cps1-configs > ../openkey-cps1/cps1-configs.h

clean:
	rm gen-cps1-configs

