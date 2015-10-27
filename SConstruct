# SConstruct

import os

env = Environment(
    CFLAGS = [
        '-Wall',
        '-Wextra',
        '-Wpedantic',
        '-Werror',
        '-O3',
    ],
)

if 'TERM' in os.environ:
    env['ENV']['TERM'] = os.environ['TERM']

env.VariantDir('build', 'src', duplicate = False)

srcs = [
    'array.c',
    'atoi.c',
    'bits.c',
    'chario.c',
    'control.c',
    'decomment.c',
    'detab.c',
    'entab.c',
    'expand.c',
    'fold.c',
    'hello.c',
    'limits.c',
    'lines.c',
    'maxline_extern.c',
    'misc.c',
    'power.c',
    'shellsort.c',
    'simplecheck.c',
    'strs.c',
    'switch.c',
    'temperature.c',
    'wc.c',
]

for s in srcs:
    env.Program('build/' + s)
