#include <iostream>
#include <vector>
using namespace std;

vector<vector<char>> grid;
int n;

int floodFill(int r, int c)
{

    if (grid[r][c] != 'W')
    {
        return 0;
    }

    grid[r][c] = 'V';

    int count = 1;

    count += floodFill(r - 1, c); 
    count += floodFill(r + 1, c); 
    count += floodFill(r, c - 1); 
    count += floodFill(r, c + 1); 

    return count;
}

int main()
{
    cout << "Enter size of square (n): ";
    cin >> n;


    grid.resize(n + 2, vector<char>(n + 2, 'B'));

    cout << "\nEnter the square:\n";
    cout << "Use W for White and B for Black\n\n";


    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> grid[i][j];
        }
    }

    vector<int> areas;

    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            
            if (grid[i][j] == 'W')
            {
                int size = floodFill(i, j);
                areas.push_back(size);
            }
        }
    }

    
    cout << "\nNumber of white areas: "
         << areas.size() << endl;

    
    if (areas.size() > 0)
    {
        cout << "\nSizes of white areas:\n";

        for (int i = 0; i < areas.size(); i++)
        {
            cout << "Area " << i + 1
                 << ": " << areas[i]
                 << " cells" << endl;
        }
    }

    return 0;
}