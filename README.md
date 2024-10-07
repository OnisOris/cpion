sudo pacman -S eigen


sudo ln -s /usr/lib/libmavsdk.so.1 /usr/lib/libmavsdk.so


https://mavsdk.mavlink.io/main/en/cpp/guide/installation.html


g++ -fPIC -shared -o libpion.so pion.cpp -lmavsdk -pthread


pamac build mavsdk


