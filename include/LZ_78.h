#ifndef LZ_78_H
#define LZ_78_H

#include "compressor.h"
#include <vector>

class LZ78Compressor: public Compressor {
  public:
    void compress(std::istream &is, std::ostream &os) override;
    void decompress(std::istream &is, std::ostream &os) override;

  private:
    const uint16_t max_dictionary_size = 32768;
};

#endif // LZ_78_H