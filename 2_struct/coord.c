#include "coord.h"

coordinate_t new_coord(int x, int y, int z) {
  coordinate_t c = {
      .x = x,
      .y = y,
      .z = z,
  };
  return c;
}

coordinate_t scale_coord(coordinate_t c, int factor) {
  coordinate_t scaled = {
      .x = c.x * factor,
      .y = c.y * factor,
      .z = c.z * factor,
  };
  return scaled;
}
