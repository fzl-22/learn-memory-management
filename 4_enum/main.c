#include "exercise.h"
#include <stdio.h>

int main(void) {
  HttpErrorCode code = HTTP_INTERNAL_SERVER_ERROR;
  printf("status: %s\n", http_to_str(code));

  printf("The size of BigNumbers is %zu bytes\n", sizeof(BigNumbers));
  printf("The size of HttpErrorCode is %zu bytes\n", sizeof(HttpErrorCode));
  return 0;
}
