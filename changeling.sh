#!/usr/bin/env bash

file=CHANGELOG.md

echo "# Changelog" > $file
echo >> $file 

git log --reverse --pretty=%B | awk '
BEGIN {
    version = " 0.0.0"
}

!NF { next }

/^bump/ {
    versions[++vcount] = version

    for (i = 1; i <= n; i++) {
        groups[version, i] = msgs[i]
    }
    size[version] = n

    version = substr($0, 6)
    n = 0
    next
}

NF {
    type = $0
    sub(/:.*/, "", type)   # extract prefix before :

    # filter out chore
    if (type == "chore") next

    # filter out task
    if (type == "task") next

    # remove "feat:" or whatever type
    sub(/^[^:]*:[ ]*/, "")

    msgs[++n] = $0
}

END {
    versions[++vcount] = version

    for (i = 1; i <= n; i++) {
        groups[version, i] = msgs[i]
    }
    size[version] = n

    # print in reverse order
    for (vi = vcount; vi >= 1; vi--) {
        v = versions[vi]

        if (size[v] != 0) {
            print "##" v

            for (i = size[v] + 1; i-- > 1;) {
                print " - " groups[v, i]
            }

            print ""
        }
    }
}
' >> $file

