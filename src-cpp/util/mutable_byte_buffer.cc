#include "mutable_byte_buffer.h"

#include <cstdint>
#include <cstring>

MutableByteBuffer::MutableByteBuffer(std::size_t initial_size) : ByteBuffer(NULL, initial_size) {
  data_ = new uint8_t[size_];
}

MutableByteBuffer::MutableByteBuffer(const MutableByteBuffer &other) : ByteBuffer(NULL, other.size_) {
  read_ = other.read_;
  write_ = other.write_;
  data_ = new uint8_t[size_];
  std::memcpy(data_, other.data_, size_);
}

MutableByteBuffer::~MutableByteBuffer() {
  delete data_;
}

void MutableByteBuffer::write_unsigned_long(uint64_t val) {
  write(reinterpret_cast<uint8_t *>(&val), sizeof(val));
}

void MutableByteBuffer::write_short(int16_t val) {
  write(reinterpret_cast<uint8_t *>(&val), sizeof(val));
}

void MutableByteBuffer::write_n_shorts(const int16_t *vals, std::size_t n) {
  write(reinterpret_cast<const uint8_t *>(vals), sizeof(*vals) * n);
}

void MutableByteBuffer::write(const uint8_t *data, std::size_t nbytes) {
  for (std::size_t idx = 0; idx < nbytes; idx++) {
    if (write_ >= size_) {
      increase_size();
    }

    *(data_ + write_) = *(data_);
    data_++;
    write_++;
  }
}

uint8_t* data() {
  uint8_t *rdata = new uint8_t[size()];
  std::memcpy(rdata, data_, size());
  return rdata;
}

void MutableByteBuffer::increase_size() {
  uint8_t *ndata = new uint8_t[size_ * 2];
  std::memcpy(ndata, data_, size_);
  data_ = ndata;
  size_ *= 2;
}

std::size_t MutableByteBuffer::size() const {
  return write_;
}
