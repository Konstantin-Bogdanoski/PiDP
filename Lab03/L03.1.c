//
// Created by Konstantin Bogdanoski (konstantin.b@live.com)
//
#include <mpi/mpi.h>
#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 100

int main() {
    MPI_Init(NULL, NULL);

    int world_rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    MPI_Request requests[2];
    MPI_Status statuses[2];

    char recv_buff[BUFF_SIZE];
    char send_buff[BUFF_SIZE];

    sprintf(send_buff, "MSG from CPU #%d to CPU #%d", world_rank, 1 - world_rank);

    MPI_Irecv(recv_buff, BUFF_SIZE, MPI_BYTE, 1 - world_rank, 0, MPI_COMM_WORLD, &requests[0]);
    MPI_Isend(send_buff, strlen(send_buff) + 1, MPI_BYTE, 1 - world_rank, 0, MPI_COMM_WORLD, &requests[1]);

    MPI_Waitall(2, requests, statuses);

    printf("CPU #%d: %s\n", world_rank, recv_buff);

    MPI_Finalize();
    return 0;
}