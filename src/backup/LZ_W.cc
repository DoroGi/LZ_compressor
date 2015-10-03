#include "LZ_W.h"
#include <limits>
#include <istream>
#include <iostream>
#include <vector>

using namespace std;

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
   */

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
}


void LZWCompressor::fast_decompress(istream &is, ostream &os) {
  // Initialize dictionary
  vector<vector<char> > dictionary;
  dictionary.clear();
  const long int minc = numeric_limits<char>::min();
  const long int maxc = numeric_limits<char>::max();
  for (long int c = minc; c <= maxc; ++c)
    dictionary.push_back({(char) (c)});


  uint16_t index;
  vector<char> last_decompressed_string; // Decompressed index
  while (is.read((char*) &index, sizeof (uint16_t))) {

    // Handle errors
    if (index > dictionary.size()) {
      cerr << "ERROR: Cannot uncompress. Compress only using the proper tool";
      cerr << endl;
      exit(1);
    }

    // Add new entry to dictionary
    
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
      dictionary.push_back(new_entry);
    }

    // Write decompressed index in the output stream
    os.write(&dictionary.at(index).front(), dictionary.at(index).size());
    // Store new chars like we did while compressing
    last_decompressed_string = dictionary.at(index);
  }
}