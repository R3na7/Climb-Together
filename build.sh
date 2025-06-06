check_success() {
    if [ $? -ne 0 ]; then
        echo "Error: $1 failed"
        exit 1
    fi
}

mkdir cmake-build-debug
cmake -B cmake-build-debug
cd external
git clone https://github.com/fallahn/tmxlite.git
cd tmxlite
cd tmxlite
mkdir build
cmake -B build -DTMXLITE_STATIC_LIB=ON
cmake --build build
cd ../../../
cmake --build cmake-build-debug
check_success "Project build"

if [ $? -eq 0 ]; then
    cd ./cmake-build-debug/bin/ || exit
    ./Climb_Together
else
    echo "Build failed, not running the program"
    exit 1
fi