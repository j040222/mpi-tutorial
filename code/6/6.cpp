#include <mpi.h>
#include <iostream>
#include <memory>

int main(int argc, char** argv)
{
   MPI_Init(NULL, NULL);
   
   int
      proc_rank;
   
   MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
   
   ::std::shared_ptr
      <
      int[]
      >
      scattered_values;
   
   int
      received_value = 0;
   
   if (
         proc_rank == 0
      )
   {
      //
      // Only populate this buffer on process 0:
      //
      
      scattered_values.reset
         (
         new int[] { 42, 43, 44, 45, 46, 47, 48 }
         )
         ;
   }
   
   //
   // Send one integer to each process:
   //
   
   MPI_Scatter
      (
      scattered_values.get(),
      1,
      MPI_INT,
      &received_value,
      1,
      MPI_INT,
      0,
      MPI_COMM_WORLD
      )
      ;
   
   ::std::cout << "Process "
               << proc_rank
               << " received "
               << received_value
               << " from process 0"
               << ::std::endl
                  ;
   
   MPI_Finalize();
   
   return 0;
}

