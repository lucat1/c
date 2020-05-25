#include <stdio.h>
#include <dirent.h>
#include <errno.h>

// print the program usage
int usage()
{
  printf("usage: ls (path)\n");
}

// list folder contents
int list(char *path)
{
  DIR *dd = opendir(path);
  if (dd == NULL)
  {
    perror(path);
    return 1;
  }

  struct dirent *current;
  while (current = readdir(dd))
  {
    if (current == NULL)
    {
      return errno;
    }

    printf("%s\n", current->d_name);
    errno = 0;
  }

  return 0;
}

// program entry
int main(int argc, char *argv[])
{
  // equals calling ls with not path
  if (argc == 1)
  {
    return list("./");
  }

  if (argc > 2)
  {
    usage();
    return 1;
  }

  return list(argv[1]);
}