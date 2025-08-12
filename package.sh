PACKAGE="feraw"
VERSION="0.1.8"

FILENAME="if"

setup()
{
    ./ferawc --interpreter lib/* > interpreter.c
    gcc -o feraw interpreter.c -O3 -g -lm -Wno-unused-result
}

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
        -I../bruter/
    rm ferawtemplate.c pre.js
}

debug()
{
    ./ferawc --transpile "example/$FILENAME.feraw" > "example/$FILENAME.br"
    valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --log-file=./valgrind-out.txt \
    --verbose ./feraw "example/$FILENAME.br"
}

"$@"