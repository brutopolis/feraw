PACKAGE="feraw"

if [ -z "$2" ]; then
    FILENAME="hello"
else
    FILENAME="$2"
fi

debug()
{
    cpp -P "example/$FILENAME.feraw" > "example/$FILENAME.br"
    ./feraw.sh "example/$FILENAME.br" lib/std/*.c > "example/$FILENAME.debug.c"
    gcc -o $FILENAME.exe "example/$FILENAME.debug.c" -O3 -g -lm -I../bruter/
    valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --log-file=./valgrind-out.txt \
    --verbose ./$FILENAME.exe
}

"$@"