#include <iostream>
#include <cstdlib>
#include <ctime>
#include <experimental/random>
#include <numeric>
#include <fstream>



int get_wrapped_index(int index, int grid_size) {
    if (index >= grid_size) {
        return index - grid_size;
    }
    else if (index < 0)     {
        return grid_size + index;
    }
    else    {
        return index;
    }
}



int main()  {
    int grid_size = 10;
    int J = 1;
    int grid[grid_size][grid_size];

    float kT = 1;

    int i,j;

    std::srand(std::time(nullptr));

    /* initialise the values in the array */
    for(i=0;i<grid_size;i++)
	{
		for(j=0;j<grid_size;j++)    {
            int random_number = std::experimental::randint(0, 1);
            if (random_number == 0) {
                random_number -= 1;
            }
            grid[i][j] = random_number;
        }
	}


    int nsweeps = 4;
    std::ofstream file;

    for (int n=0; n<nsweeps; n++)   {
        // update the grid

        // choose random site
        int j = std::experimental::randint(0, grid_size-1);
        int k = std::experimental::randint(0, grid_size-1);

        int spin_value = grid[j][k];

        int nn_spins[4] = {
            grid[get_wrapped_index(j+1, grid_size)][k],
            grid[get_wrapped_index(j-1, grid_size)][k],
            grid[j][get_wrapped_index(k+1, grid_size)],
            grid[j][get_wrapped_index(k-1, grid_size)]
        };

        int nn_sum = nn_spins[0] + nn_spins[1] + nn_spins[2] + nn_spins[3];

        float deltaE = 2 * J * spin_value * nn_sum;

        float prob_flip = std::exp(-deltaE/kT);

        float reference_prob = ((double) rand() / (RAND_MAX));

        if (reference_prob < prob_flip) {
            grid[j][k] *= -1;
        }

        file.open ("output.dat");

        /* print values in array */
        for(int a=0;a<grid_size;a++)
        {
            for(int b=0;b<grid_size;b++)
            {
                int value = grid[a][b];
                if (value == 1) {
                    std::cout<<"  "<<value;
                }
                else    {
                    std::cout<<" "<<value;
                }
            }
            std::cout<<std::endl;
        }
        std::cout<<"\n\n";
        std::cout<<j<<" "<<k<<" "<<spin_value<<" "<<deltaE<<"\n\n";
        std::cout<<nn_spins[0]<<nn_spins[1]<<nn_spins[2]<<nn_spins[3]<<"\n\n";
        // std::cout<<nn_spins[-1%4]<<"\n";
    }

    file.close();
}