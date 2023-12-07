mkdir -p build
cd build
cmake -DCMAKE_OSX_ARCHITECTURES=arm64 -DWITH_ACCELERATE=ON -DWITH_MKL=OFF -DOPENMP_RUNTIME=NONE ..
make -j4
export CTRANSLATE_INSTALL_PATH=/Users/tarekziade/Dev/ctranslate2-demo/ctranslate2
cmake .. -DCMAKE_INSTALL_PREFIX=$CTRANSLATE_INSTALL_PATH
make -j4 install
