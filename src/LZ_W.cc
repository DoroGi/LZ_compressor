#include "LZ_W.h"
#include "bit_IO.h"
#include <math.h>
#include <limits>
#include <istream>
#include <iostream>
#include <bitset>
#include <list>
#include <queue>
#include <vector>

using namespace std;

void LZWCompressor::compress(istream &is, ostream &os) {
  // Initialize dictionary
  map<vector<char>, uint16_t> dictionary;
  dictionary.clear();
  const long int minc = numeric_limits<char>::min();
  const long int maxc = numeric_limits<char>::max();
  for (long int c = minc; c <= maxc; ++c) {
    const uint16_t dictionary_size = dictionary.size();
    dictionary[{(char) (c)}] = dictionary_size;
  }
  /* Example of Dictionary:
   *  a         1
   *  b         2
   *  c         3
   *  d         4
   *  e         5
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

      // Save new string in dictionary
      const uint16_t s_index = dictionary.size();
        dictionary[s] = s_index;

      // Write only s without last char in bitstream
      s.pop_back();
      const int index_lenght = ceil(log2((float) dictionary.size()));
      
      // Translate the codeword in bits
      const vector<bool> bit_index = index2bits(dictionary[s], index_lenght);

      // Write codeword in the bit buffer
      for(bool bit : bit_index)
        bit_buffer.push(bit);

      // Store last char, so we can add a new word to the dictionary
      s = {c};
    }
  }

  // If there are some chars in s here, they must be the final ones. They are
  // already in the dictionary. We do not need to handle this in the decompr.
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


void LZWCompressor::decompress(istream &is, ostream &os) {
  // Initialize dictionary
  vector<vector<char> > dictionary;
  dictionary.clear();
  const long int minc = numeric_limits<char>::min();
  const long int maxc = numeric_limits<char>::max();
  for (long int c = minc; c <= maxc; ++c)
    dictionary.push_back({(char) (c)});

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
  int index_lenght = 0;
  vector<char> last_decompressed_string; // Decompressed index

  while (bit_buffer.size() > 0) {

    //Retrieve the index
      index_lenght = ceil(log2((float) dictionary.size()+2));
    uint16_t index = 0;
    for (int i=1; i<=index_lenght; i++) {
      index += bit_buffer.front()*pow(2,index_lenght-i);
      bit_buffer.pop_front();
    }

    // Handle errors
    if (index > dictionary.size()) {
      cerr << "ERROR: Cannot uncompress. Compress only using the proper tool";
      cerr << endl;
      exit(1);
    }

    // Add new entry to dictionary    
    if (dictionary.size() < max_dictionary_size) {
      // Special case: see report
      if (index == dictionary.size()) {
        vector<char> new_entry = last_decompressed_string;
        new_entry.push_back(last_decompressed_string.front());
        dictionary.push_back(new_entry);
      }
      // Normal case:
      else if (!last_decompressed_string.empty()) {
        vector<char> new_entry = last_decompressed_string;
        new_entry.push_back(dictionary.at(index).front());
        if (dictionary.size()+1 < max_dictionary_size)
          dictionary.push_back(new_entry);
      }
    }

    // Write decompressed index in the output stream
    os.write(&dictionary.at(index).front(), dictionary.at(index).size());
    // Store new chars like we did while compressing
    last_decompressed_string = dictionary.at(index);
  }

  cout << endl << endl << endl;
  return;
}

/******************************************************************************* 

  First version of LZW... way faster, but with lower compression ratio

 *******************************************************************************
 
void LZWCompressor::fast_compress(istream &is, ostream &os) {
  // Initialize dictionary
  map<vector<char>, uint16_t> dictionary;
  dictionary.clear();
  const long int minc = numeric_limits<char>::min();
  const long int maxc = numeric_limits<char>::max();
  for (long int c = minc; c <= maxc; ++c) {
    const uint16_t dictionary_size = dictionary.size();
    dictionary[{(char) (c)}] = dictionary_size;
  }
  /* Example of Dictionary:
   *  a         1
   *  b         2
   *  c         3
   *  d         4
   *  e         5
   *  ...
   *//*

  vector<char> s; // String
  char c;

  while (is.get(c)) {
    // Continue to add characters to s until...
    s.push_back(c);

    // s is not in the dictionary!
    if (dictionary.count(s) == 0) {

      // Save new string in dictionary
      const uint16_t dictionary_size = dictionary.size();
      dictionary[s] = dictionary_size;

      // Write only s without last char in outputstream
      s.pop_back();
      os.write((const char*) &dictionary.at(s), sizeof (uint16_t));

      // Store last char, so we can add a new word to the dictionary
      s = {c};
    }
  }

  // If there are some chars in s here, they must be the final ones. They are
  // already in the dictionary. We do not need to handle this in the decompr.
  if (!s.empty())
    os.write((const char*) &dictionary.at(s), sizeof (uint16_t));

  return;
}

void LZWCompressor::decompress(istream &is, ostream &os) {
  // Initialize dictionary
  vector<vector<char> > dictionary;
  dictionary.clear();
  const long int minc = numeric_limits<char>::min();
  const long int maxc = numeric_limits<char>::max();
  for (long int c = minc; c <= maxc; ++c)
    dictionary.push_back({(char) (c)});

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
  int index_lenght = 0;
  vector<char> last_decompressed_string; // Decompressed index

  while (bit_buffer.size() > 0) {

    //Retrieve the index
    if (dictionary.size()+1 < max_dictionary_size)
      index_lenght = ceil(log2((float) dictionary.size()+2));
    else
      index_lenght = ceil(log2((float) dictionary.size()));

    uint16_t index = 0;
    for (int i=1; i<=index_lenght; i++) {
      index += bit_buffer.front()*pow(2,index_lenght-i);
      bit_buffer.pop_front();
    }

    // Handle errors
    if (index > dictionary.size()) {
      cerr << "ERROR: Cannot uncompress. Compress only using the proper tool";
      cerr << endl;
      exit(1);
    }

    // Add new entry to dictionary    
    if (dictionary.size() < max_dictionary_size) {
      // Special case: see report
      if (index == dictionary.size()) {
        vector<char> new_entry = last_decompressed_string;
        new_entry.push_back(last_decompressed_string.front());
        dictionary.push_back(new_entry);
      }
      // Normal case:
      else if (!last_decompressed_string.empty()) {
        vector<char> new_entry = last_decompressed_string;
        new_entry.push_back(dictionary.at(index).front());
        if (dictionary.size()+1 < max_dictionary_size)
          dictionary.push_back(new_entry);
      }
    }

    // Write decompressed index in the output stream
    os.write(&dictionary.at(index).front(), dictionary.at(index).size());
    // Store new chars like we did while compressing
    last_decompressed_string = dictionary.at(index);
  }

  cout << endl << endl << endl;
  return;
}

/**/