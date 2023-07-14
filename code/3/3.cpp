#include <mpi.h>
#include <chrono>
#include <thread>
#include <iostream>

int main(int argc, char** argv)
{
   MPI_Init(NULL, NULL);
   
   int
      proc_rank;
   
   MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
   
   ::std::this_thread::sleep_for
      (
      ::std::chrono::minutes(1)
      )
      ;
   
   ::std::cout << "Rank: "
               << proc_rank
               << ::std::endl
                  ;
   
   MPI_Finalize();
   
   return 0;
}

