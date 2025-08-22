PACKAGE="feraw"
VERSION="0.2.4"

if [ -z "$2" ]; then
    FILENAME="hello"
else
    FILENAME="$2"
fi

# buildweb needs fix
buildweb()
{
    modname="$1_Module"
    modname="${modname//\//_}"
    modname="${modname//./_}"
    modname="${modname//-/_}"
    ./ferawc lib/* > ferawtemplate.c
    echo "var $modname = {};" > pre.js
    cat "$1" >> ferawtemplate.c
    filename=$1
    emcc ferawtemplate.c -o "${filename//.c/.js}" --pre-js pre.js \
        -s EXPORT_NAME="$modname" \
        -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap","HEAPU8"]' \
        -s ASYNCIFY=1 \
        -s EXIT_RUNTIME=1 \
        -I../bruter/
    rm ferawtemplate.c pre.js
}

debug()
{
    ./feraw.js "example/$FILENAME.feraw" "example/$FILENAME.debug.c"
    gcc -o $FILENAME.exe "example/$FILENAME.debug.c" -O3 -g -lm 
    valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --log-file=./valgrind-out.txt \
    --verbose ./$FILENAME.exe
}

run-bsr()
{
    ./feraw.js "example/$FILENAME.feraw" "example/$FILENAME.debug.c"
    gcc -o $FILENAME.exe "example/$FILENAME.debug.c" -O3 -g -lm -lminifb -lX11 -lGL
    ./$FILENAME.exe
}

debug-bsr()
{
    ./feraw.js "example/$FILENAME.feraw" "example/$FILENAME.debug.c"
    gcc -o $FILENAME.exe "example/$FILENAME.debug.c" -O3 -g -lm -lminifb -lX11 -lGL
    valgrind \
    --leak-check=full \
    --show-leak-kinds=definite \
    --track-origins=yes \
    --log-file=./valgrind-out.txt \
    --verbose \
    ./$FILENAME.exe
}

debug-raylib()
{
    ./feraw.js "example/raylib/$FILENAME.feraw" "example/raylib/$FILENAME.debug.c"
    gcc -o $FILENAME.exe "example/raylib/$FILENAME.debug.c" /usr/local/lib/libraylib.a -O3 -g -lm -lpthread -ldl -lrt -lGL -lX11
    valgrind \
    --leak-check=full \
    --show-leak-kinds=definite \
    --track-origins=yes \
    --log-file=./valgrind-out.txt \
    --verbose \
    ./$FILENAME.exe
}

run-raylib()
{
    ./feraw.js "example/raylib/$FILENAME.feraw" "example/raylib/$FILENAME.debug.c"
    gcc -o $FILENAME.exe "example/raylib/$FILENAME.debug.c" /usr/local/lib/libraylib.a -O3 -g -lm -lpthread -ldl -lrt -lGL -lX11
    ./$FILENAME.exe
}

"$@"