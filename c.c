#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main() {
  srand(time(NULL));
  int par_to_child[2];
  int child_to_par[2];
  int READ = 0;
  int WRITE = 1;
  pipe(par_to_child);
  pipe(child_to_par);

  if (fork()) { //Parent
    close(par_to_child[READ]);
    close(child_to_par[WRITE]);
    int data = rand() % 100;

    printf("[parent] sending: %d\n", data);
    write(par_to_child[WRITE], &data, sizeof(data));

    read(child_to_par[READ], &data, sizeof(data));
    printf("[parent] received: %d\n", data);
  }
  else { //Child
    close(par_to_child[WRITE]);
    close(child_to_par[READ]);

    int data;
    read(par_to_child[READ], &data, sizeof(data));
    printf("[child] received: %d\nsquaring...\n", data);
    data *= data;
    write(child_to_par[WRITE], &data, sizeof(data));
  }

  return 0;
}
