#include <mpi.h>
#include <iostream>
#include <memory>

int main(int argc, char** argv)
{
   MPI_Init(NULL, NULL);
   
   int
      proc_rank;
   
   MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
   
   int
      broadcast_value = 0;
   
   if (
         proc_rank == 0
      )
   {
      broadcast_value = 42;
   }
   
   MPI_Bcast
      (
      &broadcast_value,
      1,
      MPI_INT,
      0,
      MPI_COMM_WORLD
      )
      ;
   
   if (
         proc_rank != 0
      )
   {
      ::std::cout << "Process "
                  << proc_rank
                  << " received "
                  << broadcast_value
                  << " from process 0"
                  << ::std::endl
                     ;
   }
   
   MPI_Finalize();
   
   return 0;
}

