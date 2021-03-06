#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <iostream>
#include <cstdlib>
#include <system_error>
#include <deque>

#include <asio.hpp>
#include <portaudio.h>
#include <sndfile.hh>

#include "util/ringbuf.h"
#include "net/mpacket.h"
#include "net/time_packet.h"
#include "net/packet.h"
#include "util/constants.h"

#define LEN 4096
// ^^ This should be approx 2x the size of util/constants::SAMPLES_PER_PACKET
// since master buffer size is in shorts (2 bytes)

using asio::ip::udp;

typedef struct streamState {
  std::deque<int16_t> *play_buffer;
  PaTime last_timestamp;
  std::deque<MPacket *> *packet_buffer;
  streamState(int int_size) : last_timestamp(0) {
    play_buffer = new std::deque<int16_t>(int_size);
    packet_buffer = new std::deque<MPacket *>();
  };
} streamState;

class Client {
 public:
  Client(asio::io_service &io_service, uint16_t p);
  void start();

 private:
  PaTime get_pa_time(mtime_t master_time);

  void receive();
  void receive_data(MPacket *mpacket);
  void receive_timesync(TPacket *tpacket, mtime_t to_recvd);

  static constexpr double OUTLIER_THRESHOLD = 2.0;
  // The offset samples between the master and the client.
  std::deque<double> offset_samples;

  uint16_t port;
  udp::socket socket;
  udp::endpoint sender_endpoint;
  uint8_t data[LEN];

  PaStream *stream;

  mtime_offset_t offset;
  mtime_offset_t pa_offset;

  streamState *s_state;
};

#endif
