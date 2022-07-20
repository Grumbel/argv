argv
====

A little tool to help with debugging mishaps in Bash one-liners. When
called, `argv` will print its command line arguments to stdout to
highlight how many arguments were given:

    $ ./argv Foo Bar Baz
    ARGV[0]='./argv'
    ARGV[1]='Foo'
    ARGV[2]='Bar'
    ARGV[3]='Baz'

The output is valid Bash code and special characters are escaped.
