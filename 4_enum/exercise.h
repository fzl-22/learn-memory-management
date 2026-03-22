#pragma once

typedef enum DaysOfWeek {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
} days_of_week_t;

typedef struct Event {
    char *title;
    days_of_week_t day;
} event_t;

typedef enum Color {
    RED = 55,
    GREEN = 176,
    BLUE = 38,
} color_t;

typedef enum {
    HTTP_BAD_REQUEST = 400,
    HTTP_UNAUTHORIZED = 401,
    HTTP_NOT_FOUND = 404,
    HTTP_TEAPOT = 418,
    HTTP_INTERNAL_SERVER_ERROR = 500
} HttpErrorCode;

char *http_to_str(HttpErrorCode code);

typedef enum {
    BIG = 123412341234123,
    BIGGER, // 123412341234124 (incremented by 1)
    BIGGEST // 123412341234125 (incremented by 1)
} BigNumbers;
