

// System includes
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

// Ignore warnings about deprecated declarations.
// #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <cstdlib>
#include <random>

// Convolution includes


// using-declarations
using G = std::mt19937; // mersenne_twister_engine for random numbers
using D = std::uniform_int_distribution<>; // Distribution range (inclusive)

// namespaces
using namespace std;




// Regular convolution function.
void convolute(int ** output, int ** input, int ** kernel)
{
    int convolute = 0; // This holds the convolution results for an index.
    int x, y; // Used for input matrix index

	// Fill output matrix: rows and columns are i and j respectively
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			x = i;
			y = j;

			// Kernel rows and columns are k and l respectively
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					// Convolute here.
					convolute += kernel[k][l] * input[x][y];
					y++; // Move right.
				}
				x++; // Move down.
				y = j; // Restart column position
			}
			output[i][j] = convolute; // Add result to output matrix.
			convolute = 0; // Needed before we move on to the next index.
		}
	}
}


int main(int argc, char * argv[])
{

    // For randomly generating numbers.
    G g;
    g.seed(random_device()());
    D d(0, 9); // Random number in range.

    int ** kernel = new int*[3];

    for(int i = 0; i < 3; ++i)
    {
        kernel[i] = new int[3];
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
            kernel[i][j] = d(g);
    }

    int ** matrixIn = new int*[8];
    for(int i = 0; i < 8; ++i)
    {
        matrixIn[i] = new int[8];
    }

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
            matrixIn[i][j] = d(g);
    }

    int ** output = new int*[6];
    for(int i = 0; i < 6; ++i)
    {
        output[i] = new int[6];
    }

    for(int i = 0; i < 6; i++)
        output[i][i] = 0;

    convolute(output, matrixIn, kernel);

    // Print out the resulting matrix.
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            cout << output[i][j] << " ";
        }
        cout << endl;
    }

    delete[] kernel;
    delete[] matrixIn;
    delete[] output;

    return 0;
}




