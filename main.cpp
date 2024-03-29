#include "calcpi.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>

void usage()
{
  std::cout << "Usage: ./calcpi radius n_threads\n"
            << "   where 0 <= radius <= 100000\n"
            << "     and 1 <= n_threads <= 256\n";
  exit(-1);
}

int main(int argc, char ** argv)
{
  int r, n_threads;
  if( argc != 3) usage();
  if( 1 != sscanf( argv[1], "%d", & r)) usage();
  if( 1 != sscanf( argv[2], "%d", & n_threads)) usage();
  if( r < 0 || r > 100000 || n_threads < 1 || n_threads > 256) usage();
  
  std::cout << "Calculating PI with r=" << r
            << " and n_threads=" << n_threads << "\n";
  uint64_t count = count_pixels(r, n_threads);
  double pi = count / (double(r) * r);
  std::cout << "count: " << count << "\n";
  std::cout << "PI:    " << std::setprecision(15) << pi << "\n";
  return 0;
}

