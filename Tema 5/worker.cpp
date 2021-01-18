#include <stdio.h>
#include <string.h>
#include <mpi.h>
#define NPROCS 16
//tema 5
int main(int argc, char* argv[]) {
	int my_rank;
	int p;
	int p_remote;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm parentcomm;
	char sir[100];
	MPI_Status status;

	MPI_Comm_get_parent(&parentcomm);

	MPI_Comm_remote_size(parentcomm, &p_remote);

	int count = 0;

	MPI_Recv(&sir, 100, MPI_CHAR, 0, 0, parentcomm, &status);
	for (unsigned int i = 0; i < strlen(sir); ++i)
	{

		if (sir[i] == 's')
			count++;
	}

	printf("WORKER %d - %s - numarul de aparitii este %d", my_rank, sir, count);
	MPI_Send(&count, 1, MPI_INT, 0, 0, parentcomm);
	MPI_Comm_free(&parentcomm);

	MPI_Finalize();

	return 0;
}
