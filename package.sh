name feraw
version 0.1.1
description "feraw"
# files 
setup()
{
    ./ferawc --interpreter lib/* > interpreter.c
    gcc -o feraw interpreter.c -O3 -g
    rm interpreter.c
}

debug()
{
    ./ferawc --transpile example/hello-world.fw > example/hello-world.rw
    valgrind     \
    --leak-check=full     \
    --show-leak-kinds=all     \
    --track-origins=yes     \
    --log-file=./valgrind-out.txt     \
    --verbose ./feraw example/hello-world.rw
}