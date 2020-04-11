"""
# https://zork.net/~st/jottings/sais.html#lms-substrings
"""
import os
import sys


def naively_make_suffix_array(source):
    """
    A naive, slow suffix-array construction algorithm.
    """
    print('start')

    # Construct a list of suffixes of the source string.
    suffixes = []
    for offset in range(len(source) + 1):
        suffixes.append(source[offset:])
    print(suffixes)
    # Sort the suffixes
    suffixes.sort()
    print(suffixes)

    # Calculate the start offset of each suffix, storing them in
    # sorted order into the suffix array.
    suffix_array = []
    for suffix in suffixes:
        offset = len(source) - len(suffix)
        suffix_array.append(offset)

    print(suffix_array)
    return suffix_array


def main(args):
    naively_make_suffix_array('cabbage')


if __name__ == '__main__':
    main(sys.argv[1:])
