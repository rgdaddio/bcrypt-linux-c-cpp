# bcrypt-linux-c-cpp
Port of OpenBSD bcrypt for c and c++ on linux

This is pretty much a direct port of the OpenBSD implementation to Ubuntu Linux.

It compiles on Ubuntu and requires libbsd Ubuntu package it also uses
suckless software explicit_bzero.

Included is a test which calls a python script that generates
the bcrypt hash and this is then validated using the c/c++
implementation. Routines to generate hashes in the test via
c/c++ are include as well in comments.

//tested with gcc 4.6.3 ubuntu 12.04

//tested with g++ 4.6.3 ubuntu 12.04

//tested with gcc 5.2.1 ubuntu 15.10

//tested with g++ 5.2.1 ubuntu 15.10

//tested with gcc 9.3.0 ubuntu 20.04

//tested with g++ 9.3.0 ubuntu 20.04

#To Use:

//sudo apt-get install libbsd-dev

//gcc -o c_bcrypt_test -lbsd test.c bcrypt.c blowfish.c timing_safe.c linux_util.c -lrt \`pkg-config --libs libbsd\`

//g++ -o cpp_bcrypt_test -lbsd test.c bcrypt.c blowfish.c timing_safe.c linux_util.c -lrt \`pkg-config --libs libbsd\`

To use the python test:

sudo pip install bcrypt

To run:

c_bcrypt_test \<yourpassword\>

or:

cpp_bcrypt_test  \<yourpassword\>
