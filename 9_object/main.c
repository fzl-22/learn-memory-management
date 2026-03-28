#include "snekobject.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  snek_object_t *object = malloc(sizeof(snek_object_t));
  object->kind = INTEGER;
  object->data.v_int = 0;
  printf("object->kind is integer: %d\n", object->kind == INTEGER);
  printf("object->data.v_int: %d\n", object->data.v_int);
  free(object);

  printf("\n");

  snek_object_t *int_object = new_snek_integer(42);
  printf("int_object->kind is integer: %d\n", int_object->kind == INTEGER);
  printf("int_object->data.v_int: %d\n", int_object->data.v_int);
  // free(int_object);
  // int_object = NULL;

  snek_object_t *float_object = new_snek_float(3.14);
  printf("float_object->kind is float: %d\n", float_object->kind == FLOAT);
  printf("float_object->data.v_float: %f\n", float_object->data.v_float);
  // free(float_object);
  // float_object = NULL;

  char *input = "Hello, World!";
  snek_object_t *str_object = new_snek_string(input);
  printf("str_object->kind is string: %d\n", str_object->kind == STRING);
  printf("str_object->data.v_string: %s\n", str_object->data.v_string);
  // free(str_object->data.v_string);
  // free(str_object);
  // str_object = NULL;

  snek_object_t *vector3_object =
      new_snek_vector3(int_object, float_object, str_object);
  printf("vector3_object->kind is vector3: %d\n",
         vector3_object->kind == VECTOR3);
  printf("vector3_object->data.v_vector3->x: %d\n",
         vector3_object->data.v_vector3.x->data.v_int);
  ;
  printf("vector3_object->data.v_vector3->y: %f\n",
         vector3_object->data.v_vector3.y->data.v_float);

  ;
  printf("vector3_object->data.v_vector3->z: %s\n",
         vector3_object->data.v_vector3.z->data.v_string);
  ;

  snek_object_t *array_object = new_snek_array(2);
  snek_object_t *first = new_snek_string("First");
  snek_object_t *second = new_snek_string("Second");
  snek_object_t *third = new_snek_string("Third");
  printf("array_object->kind is array: %d", array_object->kind == ARRAY);
  printf("array_object->data.v_array.size: %lu\n",
         array_object->data.v_array.size);
  printf("set first: %d\n", snek_array_set(array_object, 0, first));
  printf("set second: %d\n", snek_array_set(array_object, 1, second));
  printf("set third: %d\n", snek_array_set(array_object, 2, third));
  snek_object_t *first_get = snek_array_get(array_object, 0);
  if (first_get != NULL) {
    printf("get first: %s\n", first_get->data.v_string);
  } else {
    printf("get first: array out of bound\n");
  }
  snek_object_t *second_get = snek_array_get(array_object, 1);
  if (second_get != NULL) {
    printf("get second: %s\n", second_get->data.v_string);
  } else {
    printf("get second: array out of bound\n");
  }
  snek_object_t *third_get = snek_array_get(array_object, 2);
  if (third_get != NULL) {
    printf("get third: %s\n", third_get->data.v_string);
  } else {
    printf("get third: array out of bound\n");
  }

  free(int_object);
  int_object = NULL;

  free(float_object);
  float_object = NULL;

  free(str_object->data.v_string);
  free(str_object);
  str_object = NULL;

  free(vector3_object);
  vector3_object = NULL;

  free(first->data.v_string);
  free(first);
  first = NULL;
  free(second->data.v_string);
  free(second);
  second = NULL;
  free(third->data.v_string);
  free(third);
  third = NULL;

  free(array_object->data.v_array.elements);
  free(array_object);
  array_object = NULL;

  // Object Operations
  snek_object_t *one = new_snek_integer(1);
  snek_object_t *three = new_snek_integer(3);
  snek_object_t *four = snek_add(one, three);
  printf("four is integer : %d\n", four->kind == INTEGER);
  printf("four->data.v_int: %d\n", four->data.v_int);
  free(one);
  free(three);
  free(four);

  snek_object_t *one_five = new_snek_float(1.5);
  snek_object_t *three_five = new_snek_float(3.5);
  snek_object_t *five = snek_add(one_five, three_five);
  printf("five is float : %d\n", five->kind == FLOAT);
  printf("five->data.v_float: %f\n", five->data.v_float);

  snek_object_t *hello = new_snek_string("hello");
  snek_object_t *world = new_snek_string(", world");
  snek_object_t *greeting = snek_add(hello, world);
  printf("greeting is string: %d\n", greeting->kind == STRING);
  printf("greeting->data.v_string: %s\n", greeting->data.v_string);
  free(hello->data.v_string);
  free(hello);
  free(world->data.v_string);
  free(world);
  free(greeting->data.v_string);
  free(greeting);

  snek_object_t *repeated = new_snek_string("(repeated)");
  snek_object_t *result_str = snek_add(repeated, repeated);
  printf("result_str is a string: %d\n", result_str->kind == STRING);
  printf("result_str->data.v_string: %s\n", result_str->data.v_string);
  free(repeated->data.v_string);
  free(repeated);
  free(result_str->data.v_string);
  free(result_str);

  snek_object_t *one_zero = new_snek_float(1.0);
  snek_object_t *two_zero = new_snek_float(2.0);
  snek_object_t *three_zero = new_snek_float(3.0);
  snek_object_t *four_zero = new_snek_float(4.0);
  snek_object_t *five_zero = new_snek_float(5.0);
  snek_object_t *six_zero = new_snek_float(6.0);
  snek_object_t *v1 = new_snek_vector3(one_zero, two_zero, three_zero);
  snek_object_t *v2 = new_snek_vector3(four_zero, five_zero, six_zero);
  snek_object_t *result_vect = snek_add(v1, v2);
  printf("result_vect is a vector3: %d\n", result_vect->kind == VECTOR3);
  printf("result_vect->data.v_vector3.x->data.v_float: %f\n",
         result_vect->data.v_vector3.x->data.v_float);
  printf("result_vect->data.v_vector3.y->data.v_float: %f\n",
         result_vect->data.v_vector3.y->data.v_float);
  printf("result_vect->data.v_vector3.z->data.v_float: %f\n",
         result_vect->data.v_vector3.z->data.v_float);
  free(v1->data.v_vector3.x);
  free(v1->data.v_vector3.y);
  free(v1->data.v_vector3.z);
  free(v1);
  free(v2->data.v_vector3.x);
  free(v2->data.v_vector3.y);
  free(v2->data.v_vector3.z);
  free(v2);
  free(result_vect->data.v_vector3.x);
  free(result_vect->data.v_vector3.y);
  free(result_vect->data.v_vector3.z);
  free(result_vect);

  snek_object_t *eleven = new_snek_integer(11);
  snek_object_t *elevens = new_snek_array(2);
  snek_array_set(elevens, 0, eleven);
  snek_array_set(elevens, 1, eleven);

  snek_object_t *hi = new_snek_string("hi");
  snek_object_t *hellos = new_snek_array(3);
  snek_array_set(hellos, 0, hi);
  snek_array_set(hellos, 1, hi);
  snek_array_set(hellos, 2, hi);
  snek_object_t *result_arr = snek_add(elevens, hellos);
  printf("result_arr is a array: %d\n", result_arr->kind == ARRAY);
  printf("result_arr->data.v_array.size: %lu\n", result_arr->data.v_array.size);

  snek_object_t *result_arr_0 = snek_array_get(result_arr, 0);
  printf("result_arr_0->data.v_int: %d\n", result_arr_0->data.v_int);
  snek_object_t *result_arr_1 = snek_array_get(result_arr, 1);
  printf("result_arr_1->data.v_int: %d\n", result_arr_1->data.v_int);
  snek_object_t *result_arr_2 = snek_array_get(result_arr, 2);
  printf("result_arr_2->data.v_string: %s\n", result_arr_2->data.v_string);
  snek_object_t *result_arr_3 = snek_array_get(result_arr, 3);
  printf("result_arr_3->data.v_string: %s\n", result_arr_3->data.v_string);
  snek_object_t *result_arr_4 = snek_array_get(result_arr, 4);
  printf("result_arr_4->data.v_string: %s\n", result_arr_4->data.v_string);
  snek_object_t *result_arr_5 = snek_array_get(result_arr, 5);
  if (result_arr_5 == NULL) {
    printf("result_arr_5 is out of bound\n");
  } else {
    printf("result_arr_5->data.v_string: %s\n", result_arr_5->data.v_string);
  }

  free(eleven);
  free(elevens->data.v_array.elements);
  free(elevens);
  free(hi->data.v_string);
  free(hi);
  free(hellos->data.v_array.elements);
  free(hellos);
  free(result_arr->data.v_array.elements);
  free(result_arr);

  return 0;
}
