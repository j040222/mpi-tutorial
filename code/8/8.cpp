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
      gathered_values;
   
   if (
         proc_rank == 0
      )
   {
      gathered_values.reset   
         (
         new int[7]
         )
         ;
   }
   
   int
      value_to_send = 42 + proc_rank;
   
   //
   // Gather one integer from each process:
   //
   
   MPI_Gather
      (
      &value_to_send,
      1,
      MPI_INT,
      gathered_values.get(),
      1,
      MPI_INT,
      0,
      MPI_COMM_WORLD
      )
      ;
   
   if (
         proc_rank == 0
      )
   {
      ::std::cout << "Process 0 gathered 7 values as "
                     "follows: "
                     ;
      
      for(unsigned i(0u); i< 7; ++i)
      {
         ::std::cout << gathered_values[i] << " ";
      }
      
      ::std::cout << ::std::endl;
   }
   
   MPI_Finalize();
   
   return 0;
}

