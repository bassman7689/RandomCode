BIN=hello
OBJECTS=hello.o
SOURCES=hello.asm
AS=nasm
ASFLAGS=-fmacho64
LDFLAGS=-macosx_version_min 10.11 -lSystem

all: bin

run: bin
	./$(BIN)

bin: $(OBJECTS)
	ld $(LDFLAGS) $^ -o $(BIN)

$(OBJECTS): $(SOURCES) 
	$(AS) $(ASFLAGS) $^

.PHONY: clean
clean:
	rm -f $(BIN) $(OBJECTS) 
