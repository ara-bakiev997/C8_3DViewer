#include "parser.h"
#include "s21_matrix.h"

int main() {
  int error = 0;

  // Data vertexes = {0};
  // Data facets = {0};

  Vertexes vertexes;
  Facets facets;
  // FILE *f = fopen("cube.obj", "r");

  error = parser("objFiles/cube.obj", &vertexes, &facets);
  // error = parser("lamp.obj", &vertexes, &facets);
  //   parser("lamp.obj");

  switch (error) {
    case 0:
      printf("%s\n", "\nFile open successfully\n");
      break;
    case 1:
      printf("%s\n", "ERROR: File not open");
      break;
    default:
      break;
  }

  printf("vertexes->count = %d\n", vertexes.count);
  printf("facets.count = %d\n", facets.count);

  printf("vertexes print\n");
  print_vertex(vertexes);
  printf("facets print\n");
  print_facets(facets);

  // printf("\n************\n");

  // char* str = "f    1     2     3 4 ";
  // int a = 0;
  // printf("str-> = %s\n", str);
  // count_number_in_string(&a, str);
  // printf("count_words-> = %d\n", a);

  // if (f) fclose(f);

  return error;
}