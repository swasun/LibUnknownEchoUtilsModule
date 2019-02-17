cmake -Bbuild/release -H. -DCMAKE_BUILD_TYPE=Release
cd %cd%/build/release
cmake --build . --config Release
cd %~dp0
