DIR_SOURCE = ..\Source
DIR_DEBUG = .\Debug

C_FLAGS = /Zi /FS /EHsc /nologo /DUNICODE /D_UNICODE
OUTPUT_EXE = Bletris.exe

SOURCE_FILES = $(DIR_SOURCE)\cpp\*.cpp

all: Bletris.exe

clean:
	@echo Cleaning $(DIR_DEBUG)
	@if exist $(DIR_DEBUG) rmdir /S /Q $(DIR_DEBUG)

rebuild: clean Bletris.exe

Bletris.exe:
	@echo Building
	@if not exist $(DIR_DEBUG) mkdir $(DIR_DEBUG)
	@cd $(DIR_DEBUG)
	cl.exe $(C_FLAGS) /Fe:$(OUTPUT_EXE) $(SOURCE_FILES)
