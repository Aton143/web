mkdir -p ../build
pushd ../build
em++ -std=c++11 ../src/main.cpp -s USE_SDL=2 -s FULL_ES2=1 -s WASM=1 -o hello_tri.js
clang -std=c++11 ../src/main.cpp -L/usr/local/lib -lSDL2 -framework OpenGL -g
cp ../src/index.html index.html
popd
