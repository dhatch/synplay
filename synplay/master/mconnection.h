#ifndef M_CONNECTION_H
#define M_CONNECTION_H

struct MConnection {
  enum MConnectionState {
    NAKED = 0,
    SENT_INITIAL_TIMESYNC = 1,
    SENT_FINAL_TIMESYNC = 2,
    PENDING_ALL_SYNCED = 3,
    SENDING_DATA = 4
  };
  int attempts;
  int sync_rounds;
  asio::deadline_timer *timer;
  MConnectionState state;

  MConnection() : state(NAKED), timer(nullptr), attempts(0), sync_rounds(0){};
};

#endif
