//------------------------------------------------------------------------------
// bit_IO.cc
//
// Created on: 22/ago/2015
//     Author: Gianmarco Doro
//
// Short menu that calls the chosen compressor
//------------------------------------------------------------------------------
#include "bit_IO.h"
#include <bitset>

using namespace std;

vector<bool> index2bits (uint16_t index, int index_lenght) {
  bitset<16> bit_index (index);

  vector<bool> bool_index;
  for (int i=index_lenght; i>0; i--)
    bool_index.push_back(bit_index[i-1]);
  return bool_index;
}

vector<bool> char2bits (char c) {
  bitset<8> bit_c (c);
  vector<bool> bool_c;
  for (int i=8; i>0; i--)
    bool_c.push_back(bit_c[i-1]);
  return bool_c;
}