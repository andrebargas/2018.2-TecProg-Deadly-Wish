# Deadly Wish

## Automatic Installation

* change the permission of install script and run script

    ```sh
    chmod 777 install.sh run.sh
    ```

* Run the script ```./install.sh``` then run ```./run.sh```

* Enjoy

## Manual Installation

```sh
git clone https://github.com/fgagamedev/Deadly-Wish.git

sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev 

cd Deadly-Wish/ijengine
tar -vzxf ijengine.tar.gz
make
sudo make install
mkdir ../libs/ && cp kernel/sdl2/kernel.so.0.1.0 ../libs/ 

cd ..
mkdir build && cd build
cmake ..
make
cd ..
./Deadly_Wish
```


