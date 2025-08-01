name rawer
version 0.0.8
description "rawer"
# files 
setup()
{
    bpm install-from localhost:3000/packages std condition
    gcc -O3 -Wl,-rpath=/lib -o rawer main.c .bpm/std/std.c .bpm/condition/condition.c -g
}

debug()
{
    ./ferawc example/hello-world.fw > example/hello-world.rw
    valgrind     --leak-check=full     --show-leak-kinds=all     --track-origins=yes     --log-file=./valgrind-out.txt     --verbose ./rawer example/hello-world.rw
}