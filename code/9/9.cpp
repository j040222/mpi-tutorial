#include <mpi.h>
#include <iostream>
#include <memory>

int main(int argc, char** argv)
{
   MPI_Init(NULL, NULL);
   
   int
      proc_rank;
   
   MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
   
   //
   // Process 1 sends 1 element to process 0:
   // Process 2 sends 2 elements to process 0:
   // Process 3 sends 3 elements to process 0 (and so on)
   //
   
   ::std::shared_ptr
      <
      int[]
      >
      gathered_values
         (
         new int[21] // 6 + 5 + ... + 1 + 0
         )
         ,
      displacements
         (
         new int[7] { 0, 0, 1, 3, 6, 10, 15 }
         )
         ,
      receive_counts
         (
         new int[7] { 0, 1, 2, 3, 4, 5, 6 }
         )
         ,
      sent_values;
   
   sent_values.reset( new int [proc_rank] );
   
   for(unsigned i(0u); i< proc_rank; ++i)
   {
      sent_values[i] =
         displacements[proc_rank] + i;
   }
   
   MPI_Gatherv
      (
      sent_values.get(),
      proc_rank,
      MPI_INT,
      gathered_values.get(),
      receive_counts.get(),
      displacements.get(),
      MPI_INT,
      0,
      MPI_COMM_WORLD
      )
      ;
   
   if (
         proc_rank == 0
      )
   {
      ::std::cout << "Process "
                  << proc_rank
                  << " received 21 datums: "
                     ;
      
      for(unsigned i(0u); i< 21; ++i)
      {
         ::std::cout << gathered_values[i] << " ";
      }
      
      ::std::cout << ::std::endl;
   }
   
   MPI_Finalize();
   
   return 0;
}

