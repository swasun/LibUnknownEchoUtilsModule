cmake -Bbuild/debug -H. -DCMAKE_BUILD_TYPE=Debug
cd %cd%/build/debug
cmake --build . --config Debug
cd %~dp0
