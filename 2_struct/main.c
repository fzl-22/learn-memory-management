#include "coord.h"
#include <stdio.h>

int main() {
  coordinate_t coord = new_coord(1, 2, 3);
  printf("Coordinate: (%d, %d, %d)\n", coord.x, coord.y, coord.z);
  coordinate_t scaled = scale_coord(coord, 3);
  printf("Scaled coordinate: (%d, %d, %d)\n", scaled.x, scaled.y, scaled.z);

  sneklang_var_t var_bad;
  printf("Size BAD: %ld\n", sizeof(var_bad));
  sneklang_var_good_t var_good;
  printf("Size GOOD: %ld\n", sizeof(var_good));
  return 0;
}
