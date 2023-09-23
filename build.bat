@echo off
setlocal

if -%1-==-- (
    echo USAGE: build "<program_number>"
    exit /b
)

clang -luser32 -lgdi32 -o program.exe prog%1\program%1.cpp

endlocal
@echo on