//
// Created by Konstantin Bogdanoski (konstantin.b@live.com)
//
#include <mpi/mpi.h>
#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 100
#define REQUEST_SIZE 20

int main() {
    MPI_Init(NULL, NULL);

    int world_size;

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    MPI_Request requests[REQUEST_SIZE];
    MPI_Status statuses[REQUEST_SIZE];

    char recv_buff[BUFF_SIZE];
    char send_buff[BUFF_SIZE];

    int to_wait = 0;

    if (world_rank == 0) {
        strcpy(send_buff, "MSG from CPU #0 to ALL CPUs");
        for (int proc_idx = 1; proc_idx < world_size; ++proc_idx) {
            MPI_Isend(send_buff, strlen(send_buff) + 1, MPI_BYTE, proc_idx, 0, MPI_COMM_WORLD, &requests[proc_idx]);
        }
        MPI_Irecv(recv_buff, BUFF_SIZE, MPI_BYTE, world_size - 1, 0, MPI_COMM_WORLD, &requests[0]);
        to_wait = world_size;
    } else {
        MPI_Irecv(recv_buff, BUFF_SIZE, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &requests[0]);
        to_wait++;
        if (world_rank == world_size - 1) {
            sprintf(send_buff, "MSG back from CPU #%d to CPU #0", world_rank);
            MPI_Isend(send_buff, strlen(send_buff) + 1, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &requests[1]);
            to_wait++;
        }
    }

    MPI_Waitall(to_wait, requests, statuses);

    printf("CPU #%d: %s\n", world_rank, recv_buff);

    MPI_Finalize();
    return 0;
}