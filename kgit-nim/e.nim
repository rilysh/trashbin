import std/posix
import os

const git = "/usr/bin/git"

proc executeSh(cmd: string) =
    let args = allocCStringArray([])
    args[0] = "/usr/bin/sh"
    args[1] = "-c"
    args[2] = cmd
    args[3] = ""

    let ret: cint = execv("/usr/bin/sh", args)
    
    if ret != 0:
        deallocCStringArray(args)
        system.quit(1)

    deallocCStringArray(args)

proc gitClone(url: string) =
    executeSh(git & " clone " & url)

if paramCount() < 1:
    echo "Error: Missing command"
    system.quit(1)

if cmp(paramStr(1), "clone") == 0:
    if paramCount() < 2:
        echo "Error: Please specify the repository URL"
        system.quit(1)

    gitClone(paramStr(2))
else:
    echo "Error: Unknown command"
