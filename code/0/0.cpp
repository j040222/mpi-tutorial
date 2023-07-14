#include <mpi.h>
#include <iostream>

int main(int argc, char** argv)
{
   //
   // Initialize the MPI environment:
   //
   
   MPI_Init(NULL, NULL);
   
   //
   // Get the total number of processes in the group:
   //
   
   int
      world_size;
   
   MPI_Comm_size(MPI_COMM_WORLD, &world_size);
   
   //
   // Get the rank of this process:
   //
   
   int
      proc_rank;
   
   MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
   
   //
   // Get the name of the processor running this process:
   //
   
   char
      processor_name[MPI_MAX_PROCESSOR_NAME];
   int
      name_number_of_chars;
   
   MPI_Get_processor_name
      (
      processor_name
         ,
      &name_number_of_chars
      )
      ;
   
   //
   // Print a message:
   //
   
   ::std::cout << "Hello from processor '"
             << processor_name
             << "', rank "
             << proc_rank
             << "/"
             << world_size
             << " processors"
             << ::std::endl
                ;
   
   //
   // Finalize the MPI environment before shutting it down:
   //
   
   MPI_Finalize();
   
   return 0;
}

