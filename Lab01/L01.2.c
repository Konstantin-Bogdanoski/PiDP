//
// Created by Konstantin Bogdanoski (konstantin.b@live.com)
//
#include <mpi/mpi.h>
#include <stdio.h>
#include <string.h>

#define MAX_MSG_LEN 100

int main(int argc, char **argv) {
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    char buffer[MAX_MSG_LEN];

    if (world_rank == 0) {
        // sends message and then receives
        strcpy(buffer, "Message from CPU 1 to CPU 0");
        MPI_Send(buffer, strlen(buffer) + 1, MPI_BYTE, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(buffer, MAX_MSG_LEN, MPI_BYTE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("#0 RT: %s\n", buffer);
    } else if (world_rank == 1) {
        // receives message and then sends
        MPI_Recv(buffer, MAX_MSG_LEN, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("#1 RT: %s\n", buffer);

        strcpy(buffer, "Message from CPU 1 to CPU 0");
        MPI_Send(buffer, strlen(buffer) + 1, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}