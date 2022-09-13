cmake -DCMAKE_TOOLCHAIN_FILE="C:\Users\ravi\git\vcpkg\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-windows" ..
cmake --build . --parallel 10 --config Release