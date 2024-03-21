**Repository Name:** counting_prime_numbers_MPI

**README.md**

---

# Counting Prime Numbers using MPI

This repository contains a parallel C program for counting prime numbers within a given range using MPI_Send and MPI_Receive.

## Description

The provided C program allows users to calculate the number of prime numbers occurring between a lower bound number `x` and an upper bound number `y`, utilizing the Message Passing Interface (MPI) for parallelization. The program distributes the computation of prime numbers across multiple processes, with a master process coordinating the distribution of sub-ranges and aggregation of results.

## Input

- **Lower Bound (x):** The starting point of the range for counting prime numbers.
- **Upper Bound (y):** The ending point of the range for counting prime numbers.

## Output

- **Total Count of Prime Numbers:** The total count of prime numbers occurring between the lower and upper bounds.
- **Partial Counts in Each Process:** The count of prime numbers occurring in each individual process.

## Usage

1. **Clone the Repository:**
   ```
   git clone <repository-url>
   ```

2. **Compile the Program:**
   ```
   mpicc counting_primes_mpi.c -o counting_primes_mpi
   ```

3. **Execute the Program:**
   ```
   mpirun -n <num-processes> ./counting_primes_mpi
   ```

   Replace `<num-processes>` with the desired number of MPI processes for parallel execution.

4. **Follow the On-Screen Instructions:**
   - Enter the lower bound (`x`) and upper bound (`y`) numbers as prompted.
   - View the output displaying the total count of prime numbers and the partial counts in each process.

## Parallelization Scenario

**Master Process:**
- Calculates the sub-range size `(y - x) / p`, where `p` is the number of processes.
- Broadcasts `x` and the sub-range size to each slave process using MPI_Send.
- Receives sub-count from each slave process using MPI_Receive.
- Prints the total count of primes between `x` and `y`.

**Slave Process:**
- Receives `x` and the sub-range size through MPI_Receive.
- Calculates the lower bound `a` and upper bound `b` according to its rank.
- Counts primes in its sub-range (between `a` and `b`).
- Prints the partial count.
- Sends this partial count to the master process using MPI_Send.

## Example

### Input
```
Lower Bound (x): 1
Upper Bound (y): 100
```

### Output
```
Total number of prime numbers is: 25
Total number of prime numbers in P1 is: 11
Total number of prime numbers in P2 is: 7
Total number of prime numbers in P3 is: 7
```

---

This program provides an efficient way to distribute the computation of prime numbers across multiple processes using MPI, resulting in faster execution times for large ranges.

Feel free to explore the code, experiment with different input ranges, and contribute improvements to enhance its functionality further.

For any questions or suggestions, please contact the repository owner. Enjoy prime number counting with MPI!

