#include <stdio.h>
#include <unistd.h>
#include <errno.h>

// print the program usage
int usage()
{
  printf("usage: cat [...file]\n");
}

// cat the actual file into stdout
int cat(char path[])
{
  FILE *fd = fopen(path, "r");
  if (fd == NULL)
  {
    perror(path);
    return 1;
  }

  int r;
  while ((r = fgetc(fd)) != EOF)
  {
    if (write(STDOUT_FILENO, &r, 1) != 1)
    {
      perror(path);
      return 1;
    }
  }

  fclose(fd);
  return 0;
}

// program entry
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    usage();
    return 1;
  }

  for (int i = 1; i < argc; i++)
  {
    // if cat returns a number greater than 0 it means we encountered an error
    if (cat(argv[i]) > 0)
    {
      return 1;
    }
  }

  return 0;
}