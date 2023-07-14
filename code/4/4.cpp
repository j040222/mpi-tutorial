#include <mpi.h>
#include <iostream>
#include <memory>

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
      
      MPI_Status
         status;
      
      //
      // Probe the size of the incoming message:
      //
      
      MPI_Probe
         (
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
      
      ::std::cout << "Process 1 will receive "
                  << length_of_message
                  << " numbers from process 0"
                  << ::std::endl
                     ;
      
      ::std::shared_ptr
         <
         int[]
         >
         numbers_received
            (
            new int[length_of_message]
            )
            ;
      
      MPI_Recv
         (
         numbers_received.get(),
         length_of_message,
         MPI_INT,
         0, 0,
         MPI_COMM_WORLD,
         &status
         )
         ;
      
      ::std::cout << "Process 1 received "
                  << length_of_message
                  << " numbers from process 0"
                  << ::std::endl
                     ;
   }
   
   MPI_Finalize();
   
   return 0;
}

