# The Huffman Coding Algorithm

In this project, we implement the Huffman Coding algorithm. For
further details, please view the NOWEB generated documentation `huffman.pdf`.

##Source code

This repository contains the following source code and data files:

* `huffman.c` - A C programming language implementation.
* `message.txt`- A small text message file for testing.
* `huffman.pdf`- Documentation of the implementation.
* `Makefile` - For compiling the source.

##Usage

To run the algorithm on the supplied example data, first compile

    $ make

and then run the program:

    $ ./huffman encode message.txt encoded.dat
    $ ./huffman decode encoded.dat decoded.txt
    $ diff -s decoded.txt message.txt

