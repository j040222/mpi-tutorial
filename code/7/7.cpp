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
      scattered_values,
      chunk_sizes,
      displacements,
      received_values;
   
   chunk_sizes.reset
      (
      new int[] { 1, 1, 1, 1, 1, 1, 2 }
      )
      ;
   
   received_values.reset
      (
      new int[ chunk_sizes[proc_rank] ]
      )
      ;
   
   if (
         proc_rank == 0
      )
   {
      //
      // Only populate these buffers on process 0:
      //
      
      scattered_values.reset
         (
         new int[] { 42, 43, 44, 45, 46, 47, 48, 49 }
         )
         ;
      
      displacements.reset
         (
         new int[] { 0, 1, 2, 3, 4, 5, 6 }
         )
         ;
   }
   
   //
   // Send one integer to each process, except the last,
   // which receives 2 integers:
   //
   
   MPI_Scatterv
      (
      scattered_values.get(),
      chunk_sizes.get(),
      displacements.get(),
      MPI_INT,
      received_values.get(),
      chunk_sizes[proc_rank],
      MPI_INT,
      0,
      MPI_COMM_WORLD
      )
      ;
   
   ::std::cout << "Process "
               << proc_rank
               << " received "
               << chunk_sizes[proc_rank]
               << " datums from process 0: "
                  ;
   
   for(unsigned i(0u); i< chunk_sizes[proc_rank]; ++i)
   {
      ::std::cout << received_values[i] << " ";
   }
   
   ::std::cout << ::std::endl;
   
   MPI_Finalize();
   
   return 0;
}

