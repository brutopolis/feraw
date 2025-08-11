PACKAGE="feraw"
VERSION="0.1.7"

FILENAME="if"

setup()
{
    ./ferawc --interpreter lib/* > interpreter.c
    gcc -o feraw interpreter.c -O3 -g -lm -Wno-unused-result
    # rm interpreter.c
}

debug()
{
    ./ferawc --transpile "example/$FILENAME.feraw" > "example/$FILENAME.br"
    valgrind     \
    --leak-check=full     \
    --show-leak-kinds=all     \
    --track-origins=yes     \
    --log-file=./valgrind-out.txt     \
    --verbose ./feraw "example/$FILENAME.br"
}

"$@"