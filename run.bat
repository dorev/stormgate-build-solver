@echo off
setlocal

pushd .
cd ./tests

cmake -B build ..

if %errorlevel% neq 0 (
    echo CMake configuration failed
    popd
    exit /b %errorlevel%
)

cmake --build build

if %errorlevel% neq 0 (
    echo Build failed
    popd
    exit /b %errorlevel%
)

build\Debug\tests.exe

popd
endlocal
