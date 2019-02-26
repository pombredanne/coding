# modify CC to your own obfuscator-llvm location!

OUT := rc4-level-1
SRC := main.c

# default: $(OUT) 
.PHONY:main
build: $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ 

.PHONY:clean
clean:	*.o
	rm -rf *.o
