#include "snekobject.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

snek_object_t *new_snek_integer(int value) {
  snek_object_t *new_obj = malloc(sizeof(snek_object_t));
  if (new_obj == NULL) {
    return NULL;
  }

  new_obj->kind = INTEGER;
  new_obj->data.v_int = value;

  return new_obj;
}

snek_object_t *new_snek_float(float value) {
  snek_object_t *new_obj = malloc(sizeof(snek_object_t));
  if (new_obj == NULL) {
    return NULL;
  }

  new_obj->kind = FLOAT;
  new_obj->data.v_float = value;

  return new_obj;
}

snek_object_t *new_snek_string(char *value) {
  snek_object_t *new_obj = malloc(sizeof(snek_object_t));
  if (new_obj == NULL) {
    return NULL;
  }

  size_t size = strlen(value) + 1;

  char *ptr_str = malloc(size * sizeof(char));
  if (ptr_str == NULL) {
    free(new_obj);
    return NULL;
  }

  strcpy(ptr_str, value);

  new_obj->kind = STRING;
  new_obj->data.v_string = ptr_str;

  return new_obj;
}

snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y,
                                snek_object_t *z) {
  if (x == NULL || y == NULL || z == NULL) {
    return NULL;
  }

  snek_object_t *new_obj = malloc(sizeof(snek_object_t));
  if (new_obj == NULL) {
    return NULL;
  }

  new_obj->kind = VECTOR3;
  new_obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};

  return new_obj;
}

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *new_obj = malloc(sizeof(snek_object_t));
  if (new_obj == NULL) {
    return NULL;
  }

  snek_object_t **elements = calloc(size, sizeof(snek_object_t *));
  if (elements == NULL) {
    free(new_obj);
    return NULL;
  }

  new_obj->kind = ARRAY;
  new_obj->data.v_array = (snek_array_t){.size = size, .elements = elements};

  return new_obj;
}

bool snek_array_set(snek_object_t *snek_obj, size_t index,
                    snek_object_t *value) {
  if (snek_obj == NULL || value == NULL) {
    return false;
  }

  if (snek_obj->kind != ARRAY) {
    return false;
  }

  if (index > snek_obj->data.v_array.size - 1) {
    return false;
  }

  snek_obj->data.v_array.elements[index] = value;
  return true;
}

snek_object_t *snek_array_get(snek_object_t *snek_obj, size_t index) {
  if (snek_obj == NULL) {
    return NULL;
  }

  if (snek_obj->kind != ARRAY) {
    return NULL;
  }

  if (index > snek_obj->data.v_array.size - 1) {
    return NULL;
  }

  return snek_obj->data.v_array.elements[index];
}

int snek_length(snek_object_t *obj) {
  if (obj == NULL) {
    return -1;
  }

  switch (obj->kind) {
  case INTEGER:
    return 1;
  case FLOAT:
    return 1;
  case STRING:
    return strlen(obj->data.v_string);
  case VECTOR3:
    return 3;
  case ARRAY:
    return obj->data.v_array.size;
  default:
    return -1;
  }
}

snek_object_t *snek_add(snek_object_t *a, snek_object_t *b) {
  if (a == NULL || b == NULL) {
    return NULL;
  }

  if (a->kind == INTEGER) {
    if (b->kind == INTEGER) {
      return new_snek_integer(a->data.v_int + b->data.v_int);
    } else if (b->kind == FLOAT) {
      return new_snek_float(a->data.v_int + b->data.v_float);
    } else {
      return NULL;
    }
  } else if (a->kind == FLOAT) {
    if (b->kind == INTEGER) {
      return new_snek_float(a->data.v_float + b->data.v_int);
    } else if (b->kind == FLOAT) {
      return new_snek_float(a->data.v_float + b->data.v_float);
    } else {
      return NULL;
    }
  } else if (a->kind == STRING) {
    if (b->kind != STRING) {
      return NULL;
    } else {
      size_t len = strlen(a->data.v_string) + strlen(b->data.v_string) + 1;
      char *tmp_str = calloc(len, sizeof(char));
      strcat(tmp_str, a->data.v_string);
      strcat(tmp_str, b->data.v_string);
      snek_object_t *str_obj = new_snek_string(tmp_str);
      free(tmp_str);
      return str_obj;
    }
  } else if (a->kind == VECTOR3) {
    if (b->kind != VECTOR3) {
      return NULL;
    } else {
      snek_object_t *vect3_obj = new_snek_vector3(
          a->data.v_vector3.x, a->data.v_vector3.y, a->data.v_vector3.z);
      vect3_obj->data.v_vector3.x =
          snek_add(vect3_obj->data.v_vector3.x, b->data.v_vector3.x);
      vect3_obj->data.v_vector3.y =
          snek_add(vect3_obj->data.v_vector3.y, b->data.v_vector3.y);
      vect3_obj->data.v_vector3.z =
          snek_add(vect3_obj->data.v_vector3.z, b->data.v_vector3.z);
      return vect3_obj;
    }
  } else if (a->kind == ARRAY) {
    if (b->kind != ARRAY) {
      return NULL;
    } else {
      size_t len = a->data.v_array.size + b->data.v_array.size;
      snek_object_t *arr_obj = new_snek_array(len);
      for (int i = 0; i < a->data.v_array.size; i++) {
        snek_array_set(arr_obj, i, snek_array_get(a, i));
      }
      for (int i = a->data.v_array.size; i < arr_obj->data.v_array.size; i++) {
        snek_array_set(arr_obj, i, snek_array_get(b, i - a->data.v_array.size));
      }
      return arr_obj;
    }
  } else {
    return NULL;
  }
}
