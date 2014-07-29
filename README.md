voltdb-shardit-src
==================

Source code for event: VoltDB: Shard It!
Author: Vitalii Torshyn

Intro
-----

Very simple chat-like application where VoltDB cluster
acts as a chat-server. Like lemons says: it is a simple 
VoltDB C++ client which calls Java stored procedures 
to post and get data asynch-ly.

Requirements
------------

Java JDK: 1.6.x or higher (make sure javac in your PATH)
GNU GCC g++: 4.x or higher (tested with 4.7.0 only)
Glibc: 2.16 or higher
GNU Make
CMake
Kernel headers

Directory Structure
-------------------

Makefile - main GNU make file
README
build - here you can find compiled application
db - contains VoltDB Java procedures, DDL and deployment files
voltdb-3.7 - VoltDB Database package (shipped)
voltdb-client-cpp-linux-x86_64-3.0-glibc2.16 - compiled libvoltdbcpp library and its dependecies with new glibc
voltdb-client-cpp-linux-x86_64-3.0-orig - official build of libvoltcpp (http://voltdb.com)
voltdb-post-get-cpp-src - source code of C++ client

Compilation
-----------

$ make all
will compile the C++ client, Java stored procedures and will prepare VoltDB catalog.

Testing
-------

$ make test
will start VoltDB db server, post date as a message to server and will print last 5 messages.

$ make heavy-test
will execute chater 10000 times (should be around 125 calls per second)

Make targets
------------
$ make clean 
will stop VoltDB server, will clean all bin objects, will remove VoltDB catalog.

Troubleshooting
---------------

If you have C++ 'Invalid pointer exception' or 'Double free()' errors, try to 
change symlink of VoltDB C++ client binaries:
$ rm voltdb-client-cpp-linux-x86_64-3.0
$ ln -s voltdb-client-cpp-linux-x86_64-3.0-orig voltdb-client-cpp-linux-x86_64-3.0
If it won't help you have to compile from source code voltdb-client-cpp 
(Git: https://github.com/VoltDB/voltdb-client-cpp).
