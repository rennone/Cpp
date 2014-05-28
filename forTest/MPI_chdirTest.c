#include <mpi.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
//プロセスごとに別々のカレントディレクトリとなるか調べる

void makeDirectory(const char* name)
{
  if(mkdir(name,   S_IRUSR | S_IWUSR | S_IXUSR |         /* rwx */
    S_IRGRP | S_IWGRP | S_IXGRP |         /* rwx */
           S_IROTH | S_IXOTH | S_IXOTH ) == 0)
  {
    printf("make directory %s\n",name);
  } else {
    //作れなかったときは、多分すでに存在するとき.
    printf("directory %s is already exist\n", name);
  }
}
void moveDirectory(const char* name)
{
  if(chdir(name)==0)
  {
    printf("move to %s\n",name);
  } else {
    printf("cannot move to %s\n",name);
    exit(2);
  }
}

int main()
{
  int rank;
  MPI_Init( 0, 0 );
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  char path[512] = "";
  if(rank == 0)
  {
    makeDirectory("tmp");
    moveDirectory("tmp");

    getcwd(path, 512);
    printf("rank %d = %s\n", rank, path);
  } else {
    getcwd(path, 512);
    printf("rank %d = %s\n", rank, path);    
  }

  MPI_Barrier(MPI_COMM_WORLD);
  char buf[1024];
  sprintf(buf, "%d.txt",rank);
  FILE* fp = fopen(buf, "w");

  for(int i=0; i<1000000; i++)
  {
    fprintf(fp, "tmp\n");
  }

  printf("rank %d \n",rank);
  MPI_Finalize();
}
