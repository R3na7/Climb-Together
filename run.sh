check_success() {
    if [ $? -ne 0 ]; then
        echo "Error: $1 failed"
        exit 1
    fi
}

cmake -B ./cmake-build-debug
cmake --build ./cmake-build-debug

check_success "Project build"

if [ $? -eq 0 ]; then
    cd ./cmake-build-debug/bin/ || exit
    ./Climb_Together
else
    echo "Build failed, not running the program"
    exit 1
fi