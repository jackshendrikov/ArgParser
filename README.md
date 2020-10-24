**ArgParser v1.0**
==================

Annotation
----------

**ArgParser** is a very simple and primitive argument parser written in C ++. The .cpp 
file of the same name contains a basis for the simple and convenient
creation of many arguments. The main file is just a test case of how it might
look and work.

Current options
---------------

| Short form |  Long form  |                           Description                          |
|:----------:|:-----------:|:--------------------------------------------------------------:|
|     -h     | \-\-help    | See Help.                                                      |
|     -v     | \-\-version | Print version information.                                     |
|     -n     | \-\-number  | Print number or numbers.                                       |
|     -l     | \-\-list    | Print list content.                                            |
|            | \-\-elf     | Elves only come in long (tall) form, there are no short elves. |
|     -d     |             | D is for dwarfs. They are only in short form.                  |

Usage
-----

First, open the Terminal, execute `make`, then mark the file as executable with
the `chmod +x main` command and run `./main <options>`. 

**Note:** such arguments as `-n` or `-l` (or their long forms) must be followed 
by numeric or some symbolic values, otherwise the arguments after them will not work,
because they will be considered as symbolic or numerical values.

Examples
--------

```
$ ./main -h
Number of flags found: 1

Test for ArgParser project.

Usage:
        ./main_test <options>

Options:
-h, --help      See Help.
-v, --version   Print version information.
-n, --number    Print number, any number.
-l, --list      Print list content.
    --elf       Elves only come in long (tall) form, there are no short elves.
-d              D is for dwarfs. They are only in short form.

Arg: help
```

```
$ ./main -h -l
Number of flags found: 2

Test for ArgParser project.

Usage:
        ./main_test <options>

Options:
-h, --help      See Help.
-v, --version   Print version information.
-n, --number    Print number, any number.
-l, --list      Print list content.
    --elf       Elves only come in long (tall) form, there are no short elves.
-d              D is for dwarfs. They are only in short form.


Arg: help
Arg: list
```

```
$ ./main -vhl
Number of flags found: 3

Test for ArgParser project.

Usage:
        ./main_test <options>

Options:
-h, --help      See Help.
-v, --version   Print version information.
-n, --number    Print number, any number.
-l, --list      Print list content.
    --elf       Elves only come in long (tall) form, there are no short elves.
-d              D is for dwarfs. They are only in short form.


Arg: help
Arg: version
Arg: list
```

```
$ ./main --list Elvis --version -v -hl
Number of flags found: 5

Test for ArgParser project.

Usage:
        ./main_test <options>

Options:
-h, --help      See Help.
-v, --version   Print version information.
-n, --number    Print number, any number.
-l, --list      Print list content.
    --elf       Elves only come in long (tall) form, there are no short elves.
-d              D is for dwarfs. They are only in short form.


Arg: help
Arg: version
Arg: list Elvis
```

```
$ ./main -d --elf -n 5 -v --version --number 54 --list 12,45,67,90
Number of flags found: 7
Arg: version
Arg: elf
Arg: dwarf
Arg: number 54
Arg: list 12,45,67,90
```

```
$ ./main -dddddddddd
Number of flags found: 10
Arg: dwarf
```

```
$ ./main -vdn 24 -l Python,Java,C,JS,Assembly --elf
Number of flags found: 5
Arg: version
Arg: elf
Arg: dwarf
Arg: number 24
Arg: list Python,Java,C,JS,Assembly
```

```
$ ./main --elf Random
Number of flags found: 1
Arg: elf
Got text argument: Random
```

Error Examples
--------

```
$ ./main -t
Short flag t wasn't found.
Couldn't parse arguments...
```

```
$ ./main -lv
Flag l needs to be followed by a value string.
Couldn't parse arguments...
```

```
$ ./main h
Number of flags found: 0
Got text argument: h
```