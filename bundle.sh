#!/usr/bin/env bash

declare -A seen
headers=()

add_unique() {
    local value="$1"

    if [[ -z "${seen[$value]}" ]]; then
        headers+=("$value")
        seen["$value"]=1
    fi
}

echo "/* Generated header */" > mini.h

for arg in "$@"; do
    case $arg in
        containers)
            add_unique $arg
            ;;
        fmt)
            add_unique containers
            add_unique $arg
            ;;
        io)
            add_unique containers
            add_unique $arg
            ;;
        proc)
            add_unique containers
            add_unique io
            add_unique $arg
            ;;
        log)
            add_unique containers
            add_unique fmt
            add_unique io
            add_unique $arg
            ;;
        math)
            add_unique $arg
            ;;
        *)
            echo "unrecognized header $arg" >&2
            exit 1
            ;;
    esac
done

echo -n "bundling: "
for file in "${headers[@]}"; do
    filename="mini-${file}.h"

    echo -n $filename " "
    cat $filename >> mini.h
done
echo

