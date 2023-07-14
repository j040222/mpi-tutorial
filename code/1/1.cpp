#include <mpi.h>
#include <iostream>

int main(int argc, char** argv)
{
   MPI_Init(NULL, NULL);
   
   int
      world_size;
   
   MPI_Comm_size(MPI_COMM_WORLD, &world_size);
   
   int
      proc_rank;
   
   MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
   
   if (
         proc_rank == 0
      )
   {
      //
      // Sender:
      //
      
      int const
         number_to_send = 42;
      
      MPI_Send
         (
         &number_to_send,
         1,
         MPI_INT,
         1, 0,
         MPI_COMM_WORLD
         );
      
      ::std::cout << "Process 0 sent "
                  << number_to_send
                  << " to process 1"
                  << ::std::endl
                     ;
   }
   else if
      (
         proc_rank == 1
      )
   {
      //
      // Receiver:
      //
      
      int
         number_received = 0;
      
      MPI_Recv
         (
         &number_received,
         1,
         MPI_INT,
         0, 0,
         MPI_COMM_WORLD,
         MPI_STATUS_IGNORE
         )
         ;
      
   ::std::cout << "Process 1 received "
               << number_received
               << " from process 0"
               << ::std::endl
                  ;
   }
   
   MPI_Finalize();
   
   return 0;
}

