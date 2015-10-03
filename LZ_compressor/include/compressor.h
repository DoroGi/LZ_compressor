#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <string>
#include <limits>
#include <map>

class Compressor {
    public:
      virtual void compress(std::istream &is, std::ostream &os) = 0;
      virtual void decompress(std::istream &is, std::ostream &os) = 0;
};

#endif // COMPRESSOR_H