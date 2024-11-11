# RegexCompiler
DISCLOSURE: This is for educational purposes and is in no way intended to be used in larger production or final products

A regex compiler based of a deterministic finite state machine.

Syntax:
    '^' : At the beginning, forces the match to start at the start of the string
    '.' : Wildcard, accepts all characters from ascii code 20 to 126 (All visible characters)
    '$' : At the end, says that the string needs to end after matching the hole string.
    'c' : c is all other instances or escaped characters and is direct match
