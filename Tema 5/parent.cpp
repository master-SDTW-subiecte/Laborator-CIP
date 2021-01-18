#include <stdio.h>
#include <mpi.h>
#include <string.h>
#define ROOT 2
#define NO_WORKERS 5
//tema 5
int main(int argc, char* argv[]) {
	int i;
	int my_rank;
	int p;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Group grp_world;
	MPI_Group grp_new;
	MPI_Comm newComm;
	MPI_Comm_group(MPI_COMM_WORLD, &grp_world);
	MPI_Group_incl(grp_world, 1, &my_rank, &grp_new);
	MPI_Comm_create(MPI_COMM_WORLD, grp_new, &newComm);
	int my_rank_grp;
	int p_grp;
	MPI_Comm_rank(newComm, &my_rank_grp);
	MPI_Comm_size(newComm, &p_grp);
	MPI_Comm workercomm;
	int b = my_rank;
	MPI_Status status;

	for (i = 0; i < p; ++i) {
		if (i == my_rank && my_rank == ROOT) {

			MPI_Comm_spawn("C:\\LaboratorCIP\\x64\\Debug\\Worker.exe",
				MPI_ARGV_NULL, 5, MPI_INFO_NULL, 0, newComm, &workercomm,
				MPI_ERRCODES_IGNORE);
		}

		MPI_Barrier(MPI_COMM_WORLD);
	}

	if (my_rank == ROOT)
	{
		char sir[][15] = { "sesizare", "laptop", "soneriess", "sus", "cascada", "casanova" };
		for (int i = 0; i < 5; ++i)
		{
			MPI_Send(&sir[i][15], 15, MPI_CHAR, i, 0, workercomm);
			MPI_Recv(&b, 1, MPI_INT, MPI_ANY_SOURCE, 0, workercomm, &status);
			printf("PARENT %d, COPIL %d, numar aparitii %d\n", my_rank, status.MPI_SOURCE, b);
		}


		MPI_Comm_free(&workercomm);
	}

	MPI_Finalize();
	return 0;
}