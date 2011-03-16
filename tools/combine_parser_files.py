#!/usr/bin/env python
# 
# Combines the 'header' code and 'footer' code with the parser
# code generated by peg/leg from the grammar description into
# one file.
# 

import fileinput
import sys

def get_contents(fn):
    ff = open(fn, 'r')
    con = ff.read()
    ff.close()
    return con

out = sys.stdout.write

for line in fileinput.input('markdown_parser_core.c'):
    if line.strip() == '/// header_code_here':
        out(get_contents('markdown_parser_head.c'))
    elif line.strip() == '/// footer_code_here':
        out(get_contents('markdown_parser_foot.c'))
    else:
        out(line)
