#ifndef _USERS_LANDINGS_DOCUMENTS_OPENGL_C8_3DVIEWER_V1_0_1_DEVELOP_SRC_SRC_PARSER_H_
#define _USERS_LANDINGS_DOCUMENTS_OPENGL_C8_3DVIEWER_V1_0_1_DEVELOP_SRC_SRC_PARSER_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Matrix {
  double **matrix;
  int rows;
  int cols;
} matrix_t;

typedef struct facets {
  int *vertexes;
  int numbers_of_vertexes_in_facets;
} polygon_t;

struct data {
  int count_of_vertexes;
  int count_of_facets;
  matrix_t matrix_3d;
  polygon_t *polygons;
};

struct data start(char *str);
int parser(struct data *file, char *str1);
int count_lexem(char *str);
void remove_matrix(struct data *file);

#endif  // _USERS_LANDINGS_DOCUMENTS_OPENGL_C8_3DVIEWER_V1_0_1_DEVELOP_SRC_SRC_PARSER_H_
