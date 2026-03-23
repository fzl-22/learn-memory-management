#include "exercise.h"
#include <limits.h>
#include <stdio.h>
int main(void) {
  // Union
  char buffer[100];

  snek_object_t i = new_integer(5);
  format_object(i, buffer);
  printf("buffer: %s\n", buffer);

  snek_object_t s = new_string("Hello!");
  format_object(s, buffer);
  printf("buffer: %s\n", buffer);

  // Memory Layout
  val_or_err_t lanes_score = {.value = -420};
  printf("value (set): %d\n", lanes_score.value);
  printf("err (unset): %u\n", lanes_score.err);

  val_or_err_t teejs_score = {.err = UINT_MAX};
  printf("value (unset): %d\n", teejs_score.value);
  printf("err (set): %u\n", teejs_score.err);

  // Helper Fields
  packet_header_t header = {};
  // size will be 8: tcp_header -> 2 + 2 + 4 bytes, raw = 1 + 1 + 1 + 1 + 1 + 1
  // + 1 + 1. The size of memory is the same for both tcp_header & raw, that
  // is 8.
  printf("packet_header_t union size: %lu\n", sizeof(header));

  header.tcp_header.src_port = 0x1234;
  header.tcp_header.dest_port = 0x5678;
  header.tcp_header.seq_num = 0x9ABCDEF0;
  printf("header.tcp_header.src_port = %x\n",
         header.tcp_header.src_port); // takes 2 bytes
  printf("header.tcp_header.dest_port = %x\n",
         header.tcp_header.dest_port); // takes 2 bytes
  printf("header.tcp_header.seq_num = %x\n",
         header.tcp_header.seq_num); // takes 4 bytes
  // these header.raw[0-7] each element takes 1 byte
  printf("header.raw[0] = %x\n", header.raw[0]);
  printf("header.raw[1] = %x\n", header.raw[1]);
  printf("header.raw[2] = %x\n", header.raw[2]);
  printf("header.raw[3] = %x\n", header.raw[3]);
  printf("header.raw[4] = %x\n", header.raw[4]);
  printf("header.raw[5] = %x\n", header.raw[5]);
  printf("header.raw[6] = %x\n", header.raw[6]);
  printf("header.raw[7] = %x\n", header.raw[7]);
  // 8 bits -> 1 byte
  // uint8_t -> 8 bits -> 1 byte = unsigned char
  // uint16_t -> 16 bits -> 2 bytes = unsigned short
  // uint32_t -> 32 bits -> 4 bytes = unsigned int
  // uint64_t -> 64 bits -> 8 bytes = unsigned long long
  //
  // Results:
  // header.tcp_header.src_port = 1234
  // header.tcp_header.dest_port = 5678
  // header.tcp_header.seq_num = 9abcdef0
  // header.raw[0] = 34
  // header.raw[1] = 12
  // header.raw[2] = 78
  // header.raw[3] = 56
  // header.raw[4] = f0
  // header.raw[5] = de
  // header.raw[6] = bc
  // header.raw[7] = 9a
}
