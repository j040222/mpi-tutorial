#include <mpi.h>
#include <iostream>

int main(int argc, char** argv)
{
   MPI_Init(NULL, NULL);
   
   int
      proc_rank;
   
   MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
   
   MPI_Request
      request;
   
   if (
         proc_rank == 0
      )
   {
      int const
         number_to_send = 42;
      
      //
      // Non-blocking send:
      //
      
      MPI_Isend
         (
         &number_to_send,
         1,
         MPI_INT,
         1, 0,
         MPI_COMM_WORLD,
         &request
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
      int
         number_received = 0;
      
      //
      // Non-blocking receive:
      //
      
      MPI_Irecv
         (
         &number_received,
         1,
         MPI_INT,
         0, 0,
         MPI_COMM_WORLD,
         &request
         )
         ;
      
      ::std::cout << "Process 1 received "
                  << number_received
                  << " from process 0"
                  << ::std::endl
                     ;
   }
   
   //
   // Wait for the request to complete:
   //
   
   MPI_Wait(&request, MPI_STATUS_IGNORE);
   
   //
   // Synchronize the processes:
   //
   
   MPI_Barrier(MPI_COMM_WORLD);
   
   MPI_Finalize();
   
   return 0;
}

