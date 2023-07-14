#include <mpi.h>
#include <iostream>
#include <memory>
#include <sstream>

int main(int argc, char** argv)
{
   MPI_Init(NULL, NULL);
   
   int
      world_size;
   
   MPI_Comm_size(MPI_COMM_WORLD, &world_size);
   
   int
      proc_rank;
   
   MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
   
   unsigned const
      number_of_values_per_proc = 4;
   
   ::std::shared_ptr
      <
      int[]
      >
      values_to_reduce
         (
         new int[number_of_values_per_proc]
         )
         ;
   
   for(unsigned i(0u); i< number_of_values_per_proc; ++i)
   {
      values_to_reduce[i] =
         proc_rank * number_of_values_per_proc + i;
   }
   
   ::std::cout << "Process "
               << proc_rank
               << " created the following values: "
                  ;
   
   for(unsigned i(0u); i< number_of_values_per_proc; ++i)
   {
      ::std::cout << values_to_reduce[i] << " ";
   }
   
   ::std::cout << ::std::endl;
   
   ::std::shared_ptr
      <
      int[]
      >
      counts
         (
         new int[] { 1, 2, 1 }
         )
         ;
   
   ::std::shared_ptr
      <
      int[]
      >
      received_values
         (
         new int[ counts[proc_rank] ]
         )
         ;
   
   MPI_Reduce_scatter
      (
      values_to_reduce.get(),
      received_values.get(),
      counts.get(),
      MPI_INT,
      MPI_MAX,
      MPI_COMM_WORLD
      )
      ;
   
   ::std::stringstream
      ss;
   
   ss << "Process "
      << proc_rank
      << " received the following values: "
         ;
   
   for(
      unsigned i(0u);
      i< counts[proc_rank];
      ++i
      )
   {
      ss << received_values[i] << " ";
   }
   
   ss << ::std::endl;
   
   ::std::cout << ss.str();
   
   MPI_Finalize();
   
   return 0;
}

