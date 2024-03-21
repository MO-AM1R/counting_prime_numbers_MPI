# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <mpi.h>

int takeInputs(int *var, char c);
int countPrimes(int start, int end) ;

int main(int argc , char* argv[]) {
    int processesNumber, rank = 0, counter = 0;
    MPI_Status status;

    // Initialize the MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processesNumber);

    int n = processesNumber - 1;

    // The master
    if (rank == 0){
        // take the range form user
        int to, from;
        int check1 = takeInputs(&from, 'x');

        if(check1 == 0){
            printf("Invalid Input");
            return 0;
        }

        int check2 = takeInputs(&to, 'y');
        if (check2 == 0){
            printf("Invalid Input");
            return 0;
        }

        // declare the limits for each core
        int totalNumber = to - from;
        int split = totalNumber / n;
        int start = from, end;

        // send the start and the end for each core
        for (int i = 1; i < n; ++i){
            MPI_Send(&start, 1, MPI_INT,i, 0, MPI_COMM_WORLD);
            end = start + split;

            MPI_Send(&end, 1, MPI_INT,i, 0, MPI_COMM_WORLD);
            start = end;

            totalNumber -= split;
        }
        // send the final range
        end = start + split;
        totalNumber -= split;
        end += totalNumber > 0 ? totalNumber : 0;

        MPI_Send(&start, 1, MPI_INT,n, 0, MPI_COMM_WORLD);
        MPI_Send(&end, 1, MPI_INT,n, 0, MPI_COMM_WORLD);
    }

    if (rank != 0){
        // subStart represent the start for the local range
        // sunEnd represent the end for the local range
        int subStart, subEnd;

        // receive from the master core the limit of the range
        MPI_Recv(&subStart, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&subEnd, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        // count primes from subStart to subEnd
        int subCount = countPrimes(subStart, subEnd);
        printf("Total number of prime numbers in P%d is: %d\n", rank, subCount);

        // send the counter to master core
        MPI_Send(&subCount, 1, MPI_INT,0, 0, MPI_COMM_WORLD);
    } else{
        // iterate over all cores
        for (int source = 1; source < processesNumber; ++source){
            int subCount;

            // receive the counter from each core
            MPI_Recv(&subCount, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &status);
            counter += subCount;
        }
        printf("Total number of prime numbers is: %d\n", counter);
    }

    // finalize the MPI
    MPI_Finalize();
    return 0;
}

int countPrimes(int start, int end) {
    int count = 0;

    for (int number = start; number < end; ++number){
        if (number == 1) continue;
        int prime = 1;
        for (int c = 2 ; c * c <= number ; c++){
            if(number % c == 0){
                prime = 0;
                break;
            }
        }
        if (prime == 1) ++count;
    }

    return count;
}

int takeInputs(int* var, char c) {
    enum { INPUT_SIZE = 30 };
    char* ptr;
    char input[INPUT_SIZE];

    printf("Enter %c number -> ", c);
    // To make stdout unbuffered
    fflush(stdout);

    // store the input int input variable
    fgets(input, INPUT_SIZE, stdin);
    // convert the input to long and cast it to int
    *var = (int)strtol(input, &ptr, 10);

    // return 0 if the input is wrong else 1
    return (*var == INT_MAX || *var == INT_MIN || !*var) ? 0 : 1;
}