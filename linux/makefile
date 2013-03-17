################################################################################
# Main executable name
EXECUTABLE = websitecatalog

################################################################################
# All source files
SRC = ../source/WebsiteCatalog.c \
../source/BstManager.c \
../source/HashManager.c \
../source/InsertManager.c \
../source/queueADT.c \
../source/Utility.c \
../source/WebsiteManager.c

HEAD = ../header/WebsiteCatalog.h \
../header/queueADT.h

################################################################################
# Target compile and link main executable
bin/$(EXECUTABLE): bin $(SRC) $(HEAD)
	cp ../resource/* bin/release
	cp ../resource/* bin/debug
	gcc -o bin/release/$(EXECUTABLE) $(SRC) -O3 -I ../header
	gcc -o bin/debug/$(EXECUTABLE) $(SRC) -O0 -g -I ../header

################################################################################
# Misc targets

.PHONY: bin
bin:
	mkdir -p bin/release
	mkdir -p bin/debug

.PHONY: clean
clean:
	test -d bin && rm -r bin || true

################################################################################

