#include "LZ_78.h"
#include "bit_IO.h"
#include <math.h>
#include <istream>
#include <iostream>
#include <bitset>
#include <list>
#include <queue>
#include <string>

using namespace std;

void LZ78Compressor::compress(istream &is, ostream &os) {
  map<vector<char>, uint16_t> dictionary;
  dictionary.clear();
  /* Example of Dictionary:
   *  a         1
   *  b         2
   *  ab        3
   *  abb       4
   *  ba        5
   *  ...
   */

  queue<bool> bit_buffer;
  vector<char> s; // String
  char c;

  while (is.get(c)) {
    // Continue to add characters to s until...
    s.push_back(c);

    // s is not in the dictionary!
    if (dictionary.count(s) == 0) { 

      // Insert (s, s_index) in the dictionary 
      const uint16_t s_index = dictionary.size()+1;
      if (dictionary.size()+1 < max_dictionary_size)
        dictionary[s] = s_index;

      // Create the codeword:
      uint16_t index;
      char new_letter;

      // First element (index)
      if (s.size() == 1)
        index = 0;
      else {
        s.pop_back();
        index = dictionary.at(s);
      }
      
      // Second element (new_letter)
      new_letter = c;
      
      // Translate the codeword in bits
      const int index_lenght = ceil(log2((float) dictionary.size()));
      const vector<bool> bit_index = index2bits(index, index_lenght);
      const vector<bool> bit_new_letter = char2bits(new_letter);

      // Write couple in the bit buffer
      for(bool bit : bit_index)
        bit_buffer.push(bit);
      for(bool bit : bit_new_letter) 
        bit_buffer.push(bit);

      s.clear();
    }
  }

  // If there are some chars in s here, they must be the final ones. They are
  // already in the dictionary. This case will be handled in the receiver
  if (!s.empty()) {
    // Find index
    uint16_t index;
    index = dictionary.at(s);

    // Translate the index in bits
    const int index_lenght = ceil(log2((float) dictionary.size()));
    const vector<bool> bit_index = index2bits(index, index_lenght);

    // Write index in the bit_buffer
    for(bool bit : bit_index)
      bit_buffer.push(bit);

    s.clear();
  }

  // Here we have all the data stored in the bit buffer.
  // Store the bit_buffer into a file
  while (bit_buffer.size() >= 8) {

    // Group bits in char
    char group = 0;
    for (int i=0; i<8; i++) {
      bool bit = bit_buffer.front();
      bit_buffer.pop();
      if (bit) bit_set(group, BIT(i));
      else bit_clear(group, BIT(i));
    }

    // Write char in file
    os.write(&group,sizeof(char));
  }

  // Here, we can have spare bits, add some padding and create the last byte
  const int bits_left = bit_buffer.size();
  char last_char = 0;

  if (!bit_buffer.empty()) {
    for (int i=0; i<bits_left; i++) {
      bool bit = bit_buffer.front();
      bit_buffer.pop();
      if (bit) bit_set(last_char, BIT(i));
      else bit_clear(last_char, BIT(i));
    }
  }

  // The last 1 signals the start of the 0 padding
  bit_set(last_char, BIT(bits_left));
  
  // Write last_char in file
  os.write(&last_char,sizeof(char));

  cout << endl << endl << endl;
  return;
}

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


void LZ78Compressor::decompress(istream &is, ostream &os) {
  int count = 0;
  vector<vector<char> > dictionary;
  dictionary.clear();
  /* Example of Dictionary:
   *  a         1
   *  b         2
   *  ab        3
   *  abb       4
   *  ba        5
   *  ...
   */
  
  // Recreate bit_buffer
  list<bool> bit_buffer;
  char c;
  while (is.get(c))
    for (int i=0; i<8; i++)
      bit_buffer.push_back((bool) bit_get(c,BIT(i)));

  // Remove the padding
  for (;;) {
    bool padding_remover = bit_buffer.back();
    bit_buffer.pop_back();
    if (padding_remover == 1) break;
  }

  // Now we have all the bits.
  // Let's get all the complete codewords.
  // The codewords are all 16+8=24 bit long (but the last).
  // The last codeword is only 16 bit long. We will handle it at the end.
  while (bit_buffer.size()>16) {

    //Retrieve the index
    int index_lenght = 0;
    if (dictionary.size() > 0)
      if (dictionary.size()+1 < max_dictionary_size)
        index_lenght = ceil(log2((float) dictionary.size()+1));
      else index_lenght = ceil(log2((float) dictionary.size()));
    uint16_t index = 0;
    if (index_lenght>0) {
      for (int i=1; i<=index_lenght; i++) {
        index += bit_buffer.front()*pow(2,index_lenght-i);
        bit_buffer.pop_front();
      }
    }

    //Retrieve the character
    string string_char = "";
    for (int i=0; i<8; i++) {
      bool bit = bit_buffer.front();
      if (bit==0)
        string_char += "0";
      else if (bit == 1)
        string_char += "1";
      bit_buffer.pop_front();
    }
    bitset<8> bitset_char (string_char);
    char new_letter = (char)(bitset_char.to_ulong());

    //Create the decompressed string
    vector<char> decompressed_string;
    if (index != 0)
      decompressed_string = dictionary.at(index-1);
    decompressed_string.push_back(new_letter);

    // Add the string to the dictionary
    if (dictionary.size()+1 < max_dictionary_size)
      dictionary.push_back(decompressed_string);
    
    // Write the decompressed string in the file
    os.write((const char*) &decompressed_string[0], decompressed_string.size());
  }

  if (!bit_buffer.empty()) {
    //Retrieve the index
    int index_lenght = 0;
    if (dictionary.size() > 0)
      index_lenght = ceil(log2((float) dictionary.size()));
    uint16_t index = 0;
    if (index_lenght>0) {
      for (int i=1; i<=index_lenght; i++) {
        index += bit_buffer.front()*pow(2,index_lenght-i);
        bit_buffer.pop_front();
      }
    }

    //Create the decompressed string
    vector<char> decompressed_string;
    if (index != 0)
      decompressed_string = dictionary.at(index-1);

    // Write the decompressed string in the file
    os.write((const char*) &decompressed_string[0], decompressed_string.size());
  }
  
  cout << endl << endl << endl;
  return;
}

