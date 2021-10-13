DIR_DEBUG = .\Debug
DIR_RELEASE = .\Release

# Windows
CL_DEBUG_FLAGS = /Zi /FS /EHsc /nologo /DUNICODE /D_UNICODE /DEBUG /DDEBUG /DBLETRIS_WINDOWS
CL_RELEASE_FLAGS = /GL /O2 /Zi /FS /EHsc /nologo /DUNICODE /D_UNICODE /DBLETRIS_WINDOWS
OUTPUT_EXE_WINDOWS = Bletris.exe
SOURCE_FILES = ../Source/cpp/*.cpp

# Windows SDL
INCLUDE_WINDOWS_LIBS = ole32.lib user32.lib
INCLUDE_SDL_HEADERS = ../../Libraries/SDL/include/
INCLUDE_SDL_LIBS = ../../Libraries/SDL/lib/x86/*.lib /DEF:SDL2.dll
COPY_SDL_DLL = ../../Libraries/SDL/lib/x86/*.dll

# MacOS
CLANG_DEBUG_FLAGS = -std=c++14 -stdlib=libc++
CLANG_DEFINES = -D BLETRIS_SDL -D BLETRIS_MACOS
OUTPUT_MACOS = Bletris
CLANG_INCLUDE_SDL = /usr/local/Cellar/sdl2/2.0.16
CLANG_INCLUDE_SDL_LIB = $(CLANG_INCLUDE_SDL)/lib
CLANG_INCLUDE_SDL_HEADERS = $(CLANG_INCLUDE_SDL)/include/SDL2

all: build

clean:
	@echo Cleaning...
	@if exist $(DIR_DEBUG) rmdir /S /Q $(DIR_DEBUG)
	@if exist $(DIR_RELEASE) rmdir /S /Q $(DIR_RELEASE)

build:
	@echo Building Debug...
	@if not exist $(DIR_DEBUG) mkdir $(DIR_DEBUG)
	@cd $(DIR_DEBUG)
	cl.exe $(CL_DEBUG_FLAGS) /Fe:$(OUTPUT_EXE_WINDOWS) $(SOURCE_FILES) /link $(INCLUDE_WINDOWS_LIBS)

build-sdl:
	@echo Building Debug-SDL...
	@if not exist $(DIR_DEBUG) mkdir $(DIR_DEBUG)
	@cd $(DIR_DEBUG)
	@copy $(COPY_SDL_DLL) .
	cl.exe $(CL_DEBUG_FLAGS) /DBLETRIS_SDL /Fe:$(OUTPUT_EXE_WINDOWS) /I $(INCLUDE_SDL_HEADERS) $(SOURCE_FILES) /link $(INCLUDE_WINDOWS_LIBS) $(INCLUDE_SDL_LIBS)

build-macos:
	@echo Building Debug-MacOS...
	@mkdir -p ./Debug
	cd Debug; \
	clang++ $(CLANG_DEBUG_FLAGS) $(CLANG_DEFINES) -I $(CLANG_INCLUDE_SDL_HEADERS) -L $(CLANG_INCLUDE_SDL) -lSDL2 -g $(SOURCE_FILES) -o $(OUTPUT_MACOS)

release:
	@echo Building Release...
	@if not exist $(DIR_RELEASE) mkdir $(DIR_RELEASE)
	@cd $(DIR_RELEASE)
	cl.exe $(CL_RELEASE_FLAGS) /Fe:$(OUTPUT_EXE_WINDOWS) $(SOURCE_FILES)

rebuild: clean build
rebuild-sdl: clean build-sdl
rebuild-release: clean release
rebuild-macos: clean build-macos

Bletris.exe: rebuild-release
Bletris: build-macos
