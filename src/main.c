#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void open_file(char *argv, int v, int f) {
  FILE *file;
  char *str = NULL;
  size_t n, c;
  if ((file = fopen(argv, "r")) != NULL) {
    while ((int)(c = getline(&str, &n, file)) != EOF) {
      //  Replacement '\n' on '\ 0' in end line
      if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';
      strcpy(optionsF->templ[optionsF->countP++], str);
    }
    optionsF->err = 0;
    free(str);
    fclose(file);
  } else {
    if (!optionsF->opt_s) {
      optionsF->err = 1;
      printf("s21_grep: %s: %s\n", argv, strerror(errno));
    }
  }
}

int main(int argc, char **argv) {
    int v = 0, f = 0;
    open_file_1(argv, &v, &f);


  return 0;
}