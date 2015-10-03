#ifndef LZ_W_H
#define LZ_W_H

#include "compressor.h"

class LZWCompressor: public Compressor {
  public:
    void compress(std::istream &is, std::ostream &os) override;
    void decompress(std::istream &is, std::ostream &os) override;

  private:
    const uint16_t max_dictionary_size = 32768;
};

#endif // LZ_W_H