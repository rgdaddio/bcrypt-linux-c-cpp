# bcrypt-linux-c-cpp
Port of OpenBSD bcrypt for c and c++ on linux

This is pretty much a direct port of the openBSD implementation.

It compiles on Ubuntu and requires libbsd Ubuntu package.

Included is a test which call a python script which generates
the bcrypt hash and this is then validated using the c/c++.

//tested with gcc 4.6.3 ubuntu 12.04
//tested with g++ 4.6.3 ubuntu 12.04
//tested with gcc 5.2.1 ubuntu 15.10
//tested with g++ 5.2.1 ubuntu 15.10

//sudo apt-get install libbsd-dev

//gcc -lbsd test.c bcrypt.c blowfish.c timing_safe.c linux_util.c -lrt `pkg-config --libs libbsd`
//g++ -lbsd test.c bcrypt.c blowfish.c timing_safe.c linux_util.c -lrt `pkg-config --libs libbsd`

To use the python test
#sudo pip install bcrypt