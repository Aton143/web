@echo off

IF NOT EXIST ..\build mkdir ..\build

pushd ..\build
cl /Od /Zi /nologo /I..\external\SDL2\include /I..\external\glew\include ..\src\main.cpp /link /libpath:..\external\SDL2\lib\ /libpath:..\external\glew\lib\Release\x64\
copy ..\external\SDL2\bin\SDL2.dll SDL2.dll
copy ..\external\glew\bin\Release\x64\glew32.dll glew32.dll
popd
