mkdir build
cmake -B build -G"MinGW Makefiles"
cd external
git clone https://github.com/fallahn/tmxlite.git
cd tmxlite
cd tmxlite
mkdir build
cmake -B build -DTMXLITE_STATIC_LIB=ON -G"MinGW Makefiles"
cmake --build build
cd ../../../
cmake --build build