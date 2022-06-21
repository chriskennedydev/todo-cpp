@echo off
if not exist build (
	mkdir build
)

if not exist obj (
	mkdir obj
)

cl /EHcs /Fo:obj\todo /Fe:build\todo /std:c++17 /O2 src\main.cpp