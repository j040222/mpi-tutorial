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
      number_of_values_per_proc = world_size * 2u;
   
   ::std::shared_ptr
      <
      int[]
      >
      values_to_send
         (
         new int[number_of_values_per_proc]
         )
         ;
   
   for(unsigned i(0u); i< number_of_values_per_proc; ++i)
   {
      values_to_send[i] =
         proc_rank * number_of_values_per_proc + i;
   }
   
   ::std::cout << "Process "
               << proc_rank
               << " created the following values: "
                  ;
   
   for(unsigned i(0u); i< number_of_values_per_proc; ++i)
   {
      ::std::cout << values_to_send[i] << " ";
   }
   
   ::std::cout << ::std::endl;
   
   ::std::shared_ptr
      <
      int[]
      >
      received_values
         (
         new int[number_of_values_per_proc]
         )
         ;
   
   MPI_Alltoall
      (
      values_to_send.get(),
      2u,
      MPI_INT,
      received_values.get(),
      2u,
      MPI_INT,
      MPI_COMM_WORLD
      )
      ;
   
   ::std::stringstream
      ss;
   
   ss << "Process "
      << proc_rank
      << " received the following values: "
         ;
   
   for(unsigned i(0u); i< number_of_values_per_proc; ++i)
   {
      ss << received_values[i] << " ";
   }
   
   ss << ::std::endl;
   
   ::std::cout << ss.str();
   
   MPI_Finalize();
   
   return 0;
}

