#include <iostream>
#include <optional>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

constexpr int MAX_SIZE = 100;

typedef std::vector<std::vector<int> > Matrix;

struct KunnData
{
	int leftSize = 0;
	int rightSize = 0;
	std::vector<std::vector<int>> edges;
	std::vector<int> matchingPair; 
	std::vector<bool> usedPair;   
};

struct Args
{
	std::string inputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid number of argments\n";
		return std::nullopt;
	}

	Args args;
	args.inputFileName = argv[1];

	return args;
}

int ReadMatrix(std::ifstream& input, Matrix& field, int sizeX, int sizeY)
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			input >> field[i][j];
		}
	}

	return 0;
}


KunnData ReadKunnDataFromMatrix(Matrix& matrix, int sizeX, int sizeY)
{
	KunnData data;

	data.edges.resize(sizeY);

	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			if (matrix[i][j])
			{
				data.edges[i].push_back(j);
			}
		}
	}

	data.leftSize = sizeY;
	data.rightSize = sizeX;

	return data;
}

void PrintMatrix(Matrix& field, int sizeX, int sizeY, std::ostream& output)
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			output << field[i][j] << ' ';
		}
		output << std::endl;
	}
	output << std::endl;
}

bool UseKunn(KunnData& data, int vertex)
{
	if (data.usedPair[vertex])
	{
		return false;
	}

	data.usedPair[vertex] = true;
	for (size_t i = 0; i < data.edges[vertex].size(); ++i)
	{
		int to = data.edges[vertex][i];
		if (data.matchingPair[to] == -1 || UseKunn(data, data.matchingPair[to]))
		{
			data.matchingPair[to] = vertex;
			return true;
		}
	}
	return false;
}

void SolveKunn(KunnData& data)
{
	data.matchingPair.assign(data.rightSize, -1);
	for (int vertexNumber = 0; vertexNumber < data.leftSize; vertexNumber++)
	{
		data.usedPair.assign(data.leftSize, false);
		UseKunn(data, vertexNumber);
	}
}

void PrintKunnResult(KunnData data)
{
	bool isHaveSolution = true;
	for (int vertex = 0; vertex < data.rightSize; vertex++)
	{
		if (isHaveSolution && data.matchingPair[vertex] == -1)
		{
			isHaveSolution = false;
		}
	}

	if (!isHaveSolution)
	{
		std::cout << "No\n";
		return;
	}
	else
	{
		std::cout << "Yes\n";
		for (int vertex = 0; vertex < data.rightSize; vertex++)
		{
			std::cout << data.matchingPair[vertex] + 1 << ' ' << vertex + 1 << "\n";
		}
	}

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

	int p = 0, q = 0;
	input >> p >> q;

	if (p <= 0 || p > MAX_SIZE || q <= 0 || q > MAX_SIZE)
	{
		std::cout << "Invalid matrix attributes\n";
		return 1;
	}

	Matrix matrix(p, std::vector<int>(q, 0));
	ReadMatrix(input, matrix, q, p);

	KunnData kunnData = ReadKunnDataFromMatrix(matrix, q, p);

	SolveKunn(kunnData);

	PrintKunnResult(kunnData);

	return 0;
}