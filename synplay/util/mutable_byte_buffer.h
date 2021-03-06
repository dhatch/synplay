#ifndef _MUTABLEBYTEBUF_H
#define _MUTABLEBYTEBUF_H

#include <cstring>
#include <cstddef>
#include <cstdint>

#include "util/bytebuffer.h"

// methods return the number of primitives successfully read
// from the buffer
//
class MutableByteBuffer : public ByteBuffer {
 public:
  MutableByteBuffer(std::size_t initial_size = 64);
  MutableByteBuffer(const MutableByteBuffer &other);
  ~MutableByteBuffer();

  void write_uint8(uint8_t val);
  void write_unsigned_long(uint64_t val);
  void write_signed_long(int64_t val);
  void write_short(int16_t val);
  void write_n_shorts(const int16_t *vals, std::size_t n);
  virtual std::size_t size() const;

  /**
   * Return a copy of the buffer's data.
   */
  uint8_t *data();

 private:
  void increase_size();
  void write(const uint8_t *data, std::size_t nbytes);

  std::size_t write_;
};

#endif
