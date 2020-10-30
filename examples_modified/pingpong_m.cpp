
#include<mpi.h>
#include<stdio.h>

int main(int argc, char* argv[])
{
	int token, size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		token = -1;
		printf("assign: token = %d\n", token);
		MPI_Send(&token, 1, MPI_INT, 1 - rank, 0, MPI_COMM_WORLD);
		printf("Process %d pinged token %d to process %d\n", rank, token, 1 - rank);
		token = 2;
		printf("reassign: token = %d\n", token);
		MPI_Recv(&token, 1, MPI_INT, 1 - rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d received token %d\n", rank, token);
	}
	else if (rank == 1) {
		MPI_Recv(&token, 1, MPI_INT, 1 - rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d: processing...\n", rank);
		sleep(3);
		MPI_Send(&token, 1, MPI_INT, 1 - rank, 0, MPI_COMM_WORLD);
		printf("Process %d ponged token %d back to process %d\n", rank, token, 1 - rank);
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}