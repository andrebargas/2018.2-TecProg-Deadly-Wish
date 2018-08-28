echo "Install some required packages"
sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev
echo "Unzip ijengine"
cd ijengine
tar -vzxf ijengine.tar.gz
echo "Install ijengine"
make
echo "Copy the lib to system folder"
sudo make install
echo "Create libs folder and copy kernel to it"
mkdir ../libs/ && cp kernel/sdl2/kernel.so.0.1.0 ../libs/
echo "Install the game"
cd ..
mkdir build
cd build
cmake ..
make
