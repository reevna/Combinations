/*
* 3.3. [# 50] ƒл€ заданного графа, содержащего ?? вершин, найдите количество остовных 
деревьев.
¬ход. ѕерва€ строка исходного файла содержит одно целое число ?? (1 ? ?? ? 100) Ц
количество вершин. ¬ершины пронумерованы от 1 до ??. ¬ последующих ?? строках 
содержатс€ по ?? чисел, разделенных пробелами: вес ребер между вершинами.
¬ыход. ¬ первой строке должно содержатьс€ одно натуральное число Ц количество 
остовных деревьев

*/




#include <iostream>
#include <optional>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>


constexpr int MAX_SIZE = 100;

struct Args
{
    std::string inputFileName;
};

typedef std::vector<std::vector<float> > Matrix;

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid number of arguments\n";
        return std::nullopt;
    }

    Args args;
    args.inputFileName = argv[1];

    return args;
}

int ReadMatrix(std::ifstream& input, Matrix& field, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            input >> field[i][j];
        }
    }

    return 0;
}

void PrintMatrix(Matrix& field, int size, std::ostream& output)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            output << field[i][j] << ' ';
        }
        output << std::endl;
    }
    output << std::endl;
}

bool FillMatrix(Matrix& inputMatrix, Matrix& kirghofMatrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        float relations = 0.0f;
        for (int j = 0; j < size; j++)
        {
            if (inputMatrix[i][j] > 0)
            {
                relations++;
                kirghofMatrix[i][j] = -1.0;
            }
            else
            {
                kirghofMatrix[i][j] = 0.0;
            }
        }
        if (relations > 0)
        {
            kirghofMatrix[i][i] = relations;
        }
        else
        {
            return false;
        }
    }
    return true;
}


double GetDeterminant(Matrix matrix, int size)
{
    double determinant = 1;

    for (int i = 0; i < size; i++)
    {
        int pivot_index = -1;
        double pivot_value = 0;

        for (int j = i; j < size; j++)
        {
            if (fabs(matrix[j][i]) > pivot_value)
            {
                pivot_index = j;
                pivot_value = fabs(matrix[j][i]);
            }
        }
        if (pivot_value == 0)
        {
            return 0;
        }

        if (pivot_index != i)
        {
            swap(matrix[i], matrix[pivot_index]);
            determinant *= -1;
        }

        for (int j = i + 1; j < size; j++)
        {
            if (matrix[j][i] != 0)
            {
                float multiplier = 1 / matrix[i][i] * matrix[j][i];

                for (int k = i; k < size; k++)
                {
                    matrix[j][k] -= matrix[i][k] * multiplier;
                }
            }
        }

        determinant *= matrix[i][i];
    }

    return determinant;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }

    std::ifstream input(args->inputFileName);
    if (!input.is_open())
    {
        std::cout << "Failed to open file\n";
        return 1;
    }

    int v = 0;
    input >> v;

    if (v <= 0 || v > MAX_SIZE)
    {
        std::cout << "Invalid matrix size\n";
        return 1;
    }

    Matrix matrix(v, std::vector<float>(v, 0));
    ReadMatrix(input, matrix, v);


    Matrix kirghoffMatrix(v, std::vector<float>(v, 0));
    if (FillMatrix(matrix, kirghoffMatrix, v))
    {
        std::cout << GetDeterminant(kirghoffMatrix, v - 1) << std::endl;
    }
    else
    {
        std::cout << "Incorrect input!" << std::endl;
        return 1;
    }

    return 0;
}



