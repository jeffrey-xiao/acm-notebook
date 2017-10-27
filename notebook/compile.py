#!/usr/bin/env python
import argparse
import sys


def read_options(argv=None):
    parser = argparse.ArgumentParser(
        description='Compiling script for acm notebook',
    )
    parser.add_argument(
        "-i", "--input", dest="input", metavar="FILE",
        help="read latex layout from FILE",
    )
    parser.add_argument(
        "-o", "--output", dest="output", metavar="FILE",
        help="write output latex to FILE",
    )
    parser.add_argument(
        "-c", "--code", dest="folder", metavar="DIR",
        help="retrieves code from DIR",
    )

    return parser.parse_args(argv)


def get_style(filename):
    ext = filename.lower().split('.')[-1].strip()
    if ext in ['c', 'cc', 'cpp']:
        return 'cpp'
    if ext in ['java']:
        return 'java'
    if ext in ['py']:
        return 'py'
    else:
        return 'txt'


def get_tex(input, folder):
    tex = ''
    with open('./' + input) as input_file:
        for line in input_file:
            if len(line) > 3 and line[0:3] == ' - ':
                tex += "\section{{{}}}\n".format(line[3:].strip())
            elif len(line.strip()) > 1:
                tokens = line.split("/")
                tex += "\subsection{{{}}}\n".format(
                    tokens[1].strip().replace("_", "\\_")
                )
                tex += "\lstinputlisting[style={}]{{{}/{}}}\n".format(
                    get_style(line),
                    folder,
                    line.strip(),
                )

    return tex


def write_output(output, tex):
    with open(output, "w") as output_file:
        output_file.write(tex)


if __name__ == "__main__":
    args = read_options(sys.argv[1:])
    input = args.input or "content.txt"
    output = args.output or "content.tex"
    folder = args.folder or "../codebook"

    tex = get_tex(input, folder)
    write_output(output, tex)
