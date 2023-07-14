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
         numbers_to_send[3] = { 42, 42, 42 };
      
      MPI_Send
         (
         &numbers_to_send,
         3,
         MPI_INT,
         1, 0,
         MPI_COMM_WORLD
         );
      
      ::std::cout << "Process 0 sent 3 numbers to process "
                     "1"
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
         numbers_received[10];
      
      //
      // Pass this to MPI_Recv to be populated with
      // information about the sender, and information
      // about the length of the message:
      //
      
      MPI_Status
         status;
      
      MPI_Recv
         (
         &numbers_received,
         sizeof(numbers_received) / sizeof(int),
         MPI_INT,
         0, 0,
         MPI_COMM_WORLD,
         &status
         )
         ;
   
      int
         length_of_message(0);
      
      //
      // Get the length of the message from the status
      // object:
      //
      
      MPI_Get_count(&status, MPI_INT, &length_of_message);
      
      ::std::cout << "Process 1 received "
                  << length_of_message
                  << " numbers from process 0"
                  << ::std::endl
                     ;
   }
   
   MPI_Finalize();
   
   return 0;
}

