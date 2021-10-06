DIR_DEBUG = .\Debug
DIR_RELEASE = .\Release

# Windows
CL_DEBUG_FLAGS = /Zi /FS /EHsc /nologo /DUNICODE /D_UNICODE /DEBUG /DDEBUG /DBLETRIS_WINDOWS
CL_RELEASE_FLAGS = /GL /O2 /Zi /FS /EHsc /nologo /DUNICODE /D_UNICODE /DBLETRIS_WINDOWS
OUTPUT_EXE_WINDOWS = Bletris.exe

# MacOS
CLANG_DEBUG_FLAGS = -std=c++14 -stdlib=libc++
OUTPUT_MACOS = Bletris

SOURCE_FILES = ../Source/cpp/*.cpp
SOURCE_FILES_MACOS = ../Source/cpp/*.cpp

all: build

clean:
	@echo Cleaning...
	@if exist $(DIR_DEBUG) rmdir /S /Q $(DIR_DEBUG)
	@if exist $(DIR_RELEASE) rmdir /S /Q $(DIR_RELEASE)

build:
	@echo Building Debug...
	@if not exist $(DIR_DEBUG) mkdir $(DIR_DEBUG)
	@cd $(DIR_DEBUG)
	cl.exe $(CL_DEBUG_FLAGS) /Fe:$(OUTPUT_EXE_WINDOWS) $(SOURCE_FILES)

build-macos:
	@echo Building Debug-MacOS...
	@mkdir -p ./Debug
	cd Debug; \
	clang $(CLANG_DEBUG_FLAGS) -g $(SOURCE_FILES_MACOS) -o $(OUTPUT_MACOS)

release:
	@echo Building Release...
	@if not exist $(DIR_RELEASE) mkdir $(DIR_RELEASE)
	@cd $(DIR_RELEASE)
	cl.exe $(CL_RELEASE_FLAGS) /Fe:$(OUTPUT_EXE_WINDOWS) $(SOURCE_FILES)

rebuild: clean build
rebuild-release: clean release
rebuild-macos: clean build-macos

Bletris.exe: rebuild-release
Bletris: build-macos
