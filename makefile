DIR_SOURCE = ..\Source
DIR_DEBUG = .\Debug
DIR_RELEASE = .\Release

CL_DEBUG_FLAGS = /Zi /FS /EHsc /nologo /DUNICODE /D_UNICODE
CL_RELEASE_FLAGS = /GL /O2 /Zi /FS /EHsc /nologo /DUNICODE /D_UNICODE
OUTPUT_EXE = Bletris.exe

SOURCE_FILES = $(DIR_SOURCE)\cpp\*.cpp

all: build

clean:
	@echo Cleaning...
	@if exist $(DIR_DEBUG) rmdir /S /Q $(DIR_DEBUG)
	@if exist $(DIR_RELEASE) rmdir /S /Q $(DIR_RELEASE)

build:
	@echo Building Debug...
	@if not exist $(DIR_DEBUG) mkdir $(DIR_DEBUG)
	@cd $(DIR_DEBUG)
	cl.exe $(CL_DEBUG_FLAGS) /Fe:$(OUTPUT_EXE) $(SOURCE_FILES)

release:
	@echo Building Release...
	@if not exist $(DIR_RELEASE) mkdir $(DIR_RELEASE)
	@cd $(DIR_RELEASE)
	cl.exe $(CL_RELEASE_FLAGS) /Fe:$(OUTPUT_EXE) $(SOURCE_FILES)

rebuild: clean build
rebuild-release: clean release

Bletris.exe: rebuild-release
