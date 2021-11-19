#include "frequency.h"

const char sorted_letter_frequency[] = "etaoinsrhdlucmfywgpbvkxqjz";
const double letter_frequency[256] = {
    [' '] = 0.171662,  ['e'] = 0.085771,  ['t'] = 0.063700, ['o'] = 0.057701,
    ['a'] = 0.051880,  ['n'] = 0.049701,  ['i'] = 0.049019, ['s'] = 0.043686,
    ['r'] = 0.042586,  ['l'] = 0.031750,  ['h'] = 0.027444, ['d'] = 0.025071,
    ['c'] = 0.021129,  ['u'] = 0.020999,  ['m'] = 0.016437, ['g'] = 0.015597,
    ['p'] = 0.015482,  ['.'] = 0.015124,  ['-'] = 0.013734, ['f'] = 0.013725,
    ['w'] = 0.013034,  ['y'] = 0.011330,  ['b'] = 0.010195, ['v'] = 0.008462,
    [','] = 0.007384,  ['k'] = 0.006753,  ['0'] = 0.005516, ['1'] = 0.004594,
    [':'] = 0.004354,  ['S'] = 0.004003,  ['C'] = 0.003906, ['M'] = 0.003529,
    ['2'] = 0.003322,  ['T'] = 0.003322,  ['I'] = 0.003211, ['D'] = 0.003151,
    ['A'] = 0.003132,  ['E'] = 0.002673,  ['P'] = 0.002614, ['W'] = 0.002527,
    ['R'] = 0.002519,  ['\''] = 0.002447, ['"'] = 0.002442, ['H'] = 0.002321,
    [')'] = 0.002233,  ['('] = 0.002178,  ['B'] = 0.002163, ['N'] = 0.002085,
    ['x'] = 0.001950,  ['L'] = 0.001884,  ['G'] = 0.001876, ['3'] = 0.001847,
    ['O'] = 0.001842,  ['J'] = 0.001726,  ['5'] = 0.001663, ['/'] = 0.001549,
    ['?'] = 0.001474,  ['F'] = 0.001416,  ['4'] = 0.001348, ['>'] = 0.001242,
    ['<'] = 0.001225,  [';'] = 0.001214,  ['_'] = 0.001159, ['6'] = 0.001153,
    ['8'] = 0.001054,  ['7'] = 0.001030,  ['9'] = 0.001024, ['V'] = 0.000892,
    ['j'] = 0.000867,  ['U'] = 0.000814,  ['q'] = 0.000747, ['K'] = 0.000687,
    ['*'] = 0.000628,  ['z'] = 0.000596,  ['$'] = 0.000561, ['X'] = 0.000343,
    ['Q'] = 0.000316,  ['Y'] = 0.000304,  ['='] = 0.000227, ['&'] = 0.000226,
    ['+'] = 0.000215,  ['#'] = 0.000179,  ['%'] = 0.000160, [']'] = 0.000088,
    ['['] = 0.000086,  ['Z'] = 0.000076,  ['@'] = 0.000073, ['!'] = 0.000072,
    ['\t'] = 0.000057, ['{'] = 0.000026,  ['}'] = 0.000026, ['\\'] = 0.000016,
    ['`'] = 0.000009,  ['|'] = 0.000007,  ['^'] = 0.000003, ['~'] = 0.000003
};
