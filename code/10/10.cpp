#include <mpi.h>
#include <iostream>
#include <memory>
#include <algorithm>

int main(int argc, char** argv)
{
   MPI_Init(NULL, NULL);
   
   int
      proc_rank;
   
   MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
   
   //
   // Create 10 integers per process, and populate them
   // with values:
   //
   
   unsigned const
      number_of_values_per_proc = 10;
   
   ::std::shared_ptr
      <
      int[]
      >
      values
         (
         new int[number_of_values_per_proc]
         )
         ;
   
   for(unsigned i(0u); i< number_of_values_per_proc; ++i)
   {
      values[i] =
         proc_rank * number_of_values_per_proc + i;
   }
   
   //
   // Compute the maximum value among integers belonging
   // to this process:
   //
   
   int
      maximum_value[2] = { 0, proc_rank };
   
   maximum_value[0] =
      *::std::max_element
         (
         values.get(),
         values.get() + number_of_values_per_proc
         )
         ;
   
   int
      reduced_data[2];
   
   //
   // Reduce the maximum values:
   //
   
   MPI_Reduce
      (
      &maximum_value,
      reduced_data,
      1,
      MPI_2INT,
      MPI_MAXLOC,
      0,
      MPI_COMM_WORLD
      )
      ;
   
   if (
         proc_rank == 0
      )
   {
      ::std::cout << "The maximum value, "
                  << reduced_data[0]
                  << ", was found on process "
                  << reduced_data[1]
                  << ::std::endl
                     ;
   }
   
   MPI_Finalize();
   
   return 0;
}

