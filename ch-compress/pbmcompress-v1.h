#include <tuple>
#include <vector>
#include <string>

/*

image compression pipeline:

PBM -> read file -> RLE -> huffman encoding -> write file
                         |     ^
                         v     |
                Huffman tree builder

decompression pipeline:

read file -> huffman decoding -> RLE -> display file ->
                                                    CImg

*/

/*
 * all functions return:
 *   status (true = success, false = fail)
 *   width
 *   height
 */

/*
 * PBM file format: http://netpbm.sourceforge.net/doc/pbm.html
 *
 * must return false if the PBM file is invalid or cannot be read, and
 * true otherwise
 */
std::tuple<bool, int, int, std::vector<bool> *> read_pbm_file(std::string filename);

/*
 * a run is 8 bits; the high-order bit is the value and the next 7 bits are the
 * length of the run.
 *
 * IMPORTANT: since runs of length zero are uninteresting, the run is
 * one longer than the value.
 *
 */
std::tuple<bool, int, int, std::vector<uint8_t> *> rle(std::string filename);

/*
 * last byte is padded with zeroes
 */
std::tuple<bool, int, int, std::vector<uint8_t> *> huff(std::string filename);

// file format:
//  2-byte magic number: ch
//  4-byte width (little endian)
//  4-byte height (little endian)
//  huffman encoded data

std::tuple<bool, int, int, std::vector<bool> *> unrle(std::string filename);

std::tuple<bool, int, int, std::vector<uint8_t> *> unhuff(std::string filename);

std::tuple<bool, int, int, std::vector<uint8_t> *> read_ch_file(std::string filename);

// implement these four programs:
// dump-runs pbm-file run-file
// ch-compress pbm-file ch-file
// ch-decompress ch-file pbm-file
// ch-display ch-file <- use CImg: http://cimg.eu/
