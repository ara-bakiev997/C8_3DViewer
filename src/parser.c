#include "parser.h"

struct data start(char *str) {
  struct data file = {0};
    str = "/Users/landings/Documents/C8_3DViewer_v1.0-1/src/QT/QT_3DView/cube.obj";
  if (str == NULL) {
    printf("EMPTY\n");
  } else {
    parser(&file, str);
  }
  return file;
}

int parser(struct data *file, char *str1) {
  int error = 0;

  //************************
  FILE *f = fopen(str1, "r");
  char *temp_string = NULL;
  size_t len = 0;
  ssize_t lineSize = 0;
  //************************

  // первый проход с подсчетом строк: v f
  while ((int)(lineSize = getline(&temp_string, &len, f)) != EOF) {
    if (temp_string[0] == 'v' && temp_string[1] == ' ')
      file->count_of_vertexes++;

    if (temp_string[0] == 'f' && temp_string[1] == ' ') file->count_of_facets++;
  }

  // второй проход заполняем данные
  rewind(f);
  file->matrix_3d.rows = file->count_of_vertexes;
  file->matrix_3d.cols = 3;
  // Выделяем память под матрицу F, polygons
  if (file->count_of_facets > 0) {
    file->polygons =
        (polygon_t *)malloc(file->count_of_facets * sizeof(polygon_t));
  }
  // Создаем матрицу координат вершин V, matrix_3d.matrix
  if (file->matrix_3d.rows > 0) {
    file->matrix_3d.matrix =
        (double **)calloc(file->matrix_3d.rows, sizeof(double *));
    for (register int i = 0; i < file->matrix_3d.rows; i++) {
      file->matrix_3d.matrix[i] = calloc(file->matrix_3d.cols, sizeof(double));
    }
  } else {
    error = 1;
  }
  int rowsV = 0;
  int count_str_f = 0;  // счетчик строк f
  while ((int)(lineSize = getline(&temp_string, &len, f)) != EOF) {
    if (temp_string[0] == 'v' && temp_string[1] == ' ') {
      sscanf(temp_string + 2, "%lg %lg %lg", &file->matrix_3d.matrix[rowsV][0],
             &file->matrix_3d.matrix[rowsV][1],
             &file->matrix_3d.matrix[rowsV][2]);
      rowsV++;
    }
    if (temp_string[0] == 'f' && temp_string[1] == ' ') {
      int s = 0, cnt = 0;
      // подсчитываем колличество lexem разделенных пробелом в строке f
      int cnt_words = count_lexem(temp_string);
      if (cnt_words > 0) {
        file->polygons[count_str_f].numbers_of_vertexes_in_facets = cnt_words;
        // выделяем память для записи lexem в значение vertexes стурктуры
        // polygons
        file->polygons[count_str_f].vertexes = (int *)malloc(
            (file->polygons[count_str_f].numbers_of_vertexes_in_facets) *
            sizeof(int));

        while (cnt !=
               file->polygons[count_str_f].numbers_of_vertexes_in_facets) {
          if (temp_string[s] == ' ' && isdigit(temp_string[s + 1])) {
            sscanf(temp_string + s + 1, "%d",
                   &file->polygons[count_str_f].vertexes[cnt]);
            cnt++;
          }
          s++;
        }
      } else {
        error = 1;
      }
      count_str_f++;
    }
  }

  //** PRINT
  printf("file->count_of_vertexes = %d\n", file->count_of_vertexes);
  printf("file->count_of_facets = %d\n", file->count_of_facets);

  printf("\n");
  printf("print vertex\n");
  printf("\n");
  for (int i = 0; i < file->count_of_vertexes; i++) {
    printf("print number string vertex: %d ", i);
    for (int j = 0; j < file->matrix_3d.cols; j++) {
      printf(" %f", file->matrix_3d.matrix[i][j]);
    }
    printf("\n");
  }

  printf("\n");
  printf("print facets \n");
  printf("\n");
  for (int i = 0; i < file->count_of_facets; i++) {
    printf("print number string facet: %d ", i);
    for (int j = 0; j < file->polygons[i].numbers_of_vertexes_in_facets; j++)
    {
      printf(" %d", file->polygons[i].vertexes[j]);
    }
    printf("\n");
  }
  //************************
  
  if (temp_string) {
    free(temp_string);
  }
  if (f) fclose(f);
  remove_matrix(file);

  return error;
}

int count_lexem(char *str) {
  //   int cnt = 0;
  //   while (strlen(str)) {
  //     if (*str == ' ' && isdigit(*(str - 1)) && isdigit(*(str + 1))) {
  //       cnt++;
  //     }
  //     str++;
  //   }
  //   return cnt + 1;
  // }
  int cnt = 0;
  int cnt_srlen = strlen(str);
  int x = 0;
  while (x <= cnt_srlen) {
    if (str[x] == ' ' && isdigit((str[x - 1])) && isdigit((str[x + 1]))) {
      cnt++;
    }
    x++;
  }
  return cnt + 1;
}

void remove_matrix(struct data *file) {
  for (register int i = 0; i < file->matrix_3d.rows; i++) {
    if (file->matrix_3d.matrix[i]) {
      free(file->matrix_3d.matrix[i]);
    }
  }
  if (file->matrix_3d.matrix) {
    free(file->matrix_3d.matrix);
  }
  file->matrix_3d.rows = 0;
  file->matrix_3d.cols = 0;
  for (register int j = 0; j < file->count_of_facets; j++) {
    if (file->polygons[j].vertexes) free(file->polygons[j].vertexes);
  }
  if (file->polygons) free(file->polygons);
  file->count_of_facets = 0;
  file->count_of_vertexes = 0;
}
