name rawer
version 0.0.7
description "rawer"
# files 
setup()
{
    gcc -O3 -Wl,-rpath=/lib -o rawer main.c std.c -g
}

debug()
{
    ./ferawc example/hello-world.fw > example/hello-world.rw
    valgrind     --leak-check=full     --show-leak-kinds=all     --track-origins=yes     --log-file=./valgrind-out.txt     --verbose ./rawer example/hello-world.rw
}