#include <stdio.h>
#include <iostream>
#include <random>
#include <fstream>
#include <math.h>
#include <string>
#include "mpi.h"

using namespace std;

double genRan()
{
  return ((double)rand() / (RAND_MAX));
}

float gaussian(float x, float mu, float sigma)
{
  return exp(-(pow(x - mu, 2.0)) / (2.0 * sigma * sigma)) / (pow(2.0 * M_PI * sigma * sigma, 0.5));
}

void metHastings(int N, double mu, double sigma, int rank)
{

  // array to store samples
  double *samples = new double[N];

  // initialize random gaussian
  // USING LIBRARIES
  // default_random_engine generator;
  // normal_distribution<double> distribution(mu, sigma);

  ofstream myfile;
  int modRank = rank + 1;
  cout << rank << " " << modRank << endl;
  myfile.open("sample_" + to_string(modRank) + ".dat");

  // initialize at mean
  samples[0] = mu;
  myfile << samples[0] << "\n";

  for (int i = 1; i < N; i++)
  {
    //using libraries
    // samples[i] = distribution(generator);

    double dx = (genRan() - 0.5) * sigma;

    double cand = samples[i - 1] + dx;

    double alpha = gaussian(cand, mu, sigma) / gaussian(samples[i - 1], mu, sigma);

    if (genRan() <= alpha)
    {
      samples[i] = cand;
    }
    else
    {
      samples[i] = samples[i - 1];
    }

    myfile << samples[i] << "\n";
  }
  myfile.close();
}

int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    cout << "Insuficient parameters." << endl;
    ;
  }
  else
  {
    int rank, size;
    /* starts MPI */
    MPI_Init(&argc, &argv);
    /* get current process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    /* get number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    /* print the rank and number of processes */
    cout << "Process " << rank << " of " << size << " started." << endl;
    srand(time(NULL) + rank);

    int N;
    double mu, sigma;
    N = atoi(argv[1]);
    mu = atof(argv[2]);
    sigma = atof(argv[3]);

    int pointsPerProc = N / size;

    metHastings(pointsPerProc, mu, sigma, rank);

    /* ends MPI */

    cout << "Process " << rank << " of " << size << " finished." << endl;

    MPI_Finalize();
  }
  return 0;
}