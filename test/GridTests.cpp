#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/Grid.cpp"

TEST_CASE("Default constructor works as expected", "[ctor]") {
	Grid<unsigned> grid;

	grid.setRows(5);
	grid.setColumns(20);

    REQUIRE(grid.numRows() * grid.numColumns() == 100);
}

TEST_CASE("A grid of unsigned type is correctly initialized on a 9x9 board for size", "[init]") {
	unsigned dimension = 9;
	std::vector<unsigned> vec{3, 4, 6, 1, 2, 4, 6, 7, 2};

	Grid<unsigned> grid(dimension, dimension, vec);

    REQUIRE(grid.getMatrix().size() == dimension);
}

TEST_CASE("A grid of unsigned type is correct on a 9x9 board for content", "[init]") {
	unsigned dimension = 9;
	std::vector<unsigned> vec{3, 4, 6, 1, 2, 4, 6, 7, 2};

	Grid<unsigned> grid(dimension, dimension, vec);
	std::vector<unsigned> check;

	for(unsigned j = 0; j < grid.numRows(); j++) {
		for(unsigned k = 0; k < grid.numColumns(); k++) {
			check.push_back(grid.getMatrix()[j][k]);
		}
	}
	check.resize(vec.size());

	REQUIRE(vec == check);
}

TEST_CASE("Grid is correctly initialized on a 9x9 board", "[initialize]") {
	unsigned dimension = 9;
	std::string str = "___8_5____3__6___7_9___38___4795_3______71_9____2__5__1____"; 
	str.append("248___9____5______6___");

	std::vector<char> vec;

	for(unsigned i = 0; i < str.length(); i++) {
		vec.push_back(str[i]);
	}

	Grid<char> board(dimension, dimension, vec);

    REQUIRE(str.length() == board.gridSize());
}

TEST_CASE("Grid is correctly initialized on a 28x28 board", "[initialize]") {
	unsigned dimension = 28;
	std::string str = "";

	for(unsigned i = 0; i < 784; i++) {
		str.append("a");
	}

	Grid board(dimension, dimension, str);

    REQUIRE(str.length() == board.gridSize());
}

TEST_CASE("Grid correctly initializes a grid of +'s,  's, and #'s", "[initialize]") {
	std::string board = "+ +###    ++++++";
	
	unsigned index = 0;
	unsigned size = 4;
	unsigned k = 0;

	Grid grid(size, size, board);

	for(unsigned i = 0; i < grid.numRows(); i++) {
		for(unsigned j = 0; j < grid.numColumns(); j++) {
			REQUIRE(grid.getVector()[i][j] == board[k]);
			k++;
		}
	}
}

TEST_CASE("Grid operator >> works as expected", "[operator]") {
	std::ostringstream out;
	unsigned dimension = 9;
	std::string str = "___8_5____3__6___7_9___38___4795_3______71_9____2__5__1____"; 
	str.append("248___9____5______6___");

	std::string str2 = "___8_5____3__6___7_9___38___4795_3______71_9____2__5__1____"; 
	str2.append("248___9____5______6___");

	Grid board(dimension, dimension, str);

	out << board;

    REQUIRE(str2 == board.getBoard());
}

TEST_CASE("Grid operator = works as expected, first element", "[operator]") {
	unsigned dimension = 3;
	std::string str = "abcdefghi"; 
	std::string str2 = "123456789"; 
	Grid board(dimension, dimension, str);
	Grid board2(dimension, dimension, str2);

	board = board2;

    REQUIRE(board.getVector()[0][0] == '_');
}

TEST_CASE("Grid operator = works as expected, last element", "[operator]") {
	unsigned dimension = 3;
	std::string str = "abcdefghi"; 
	std::string str2 = "123456789"; 
	Grid board(dimension, dimension, str);
	Grid board2(dimension, dimension, str2);

	board = board2;

    REQUIRE(board.getVector()[2][2] == '_');
}

TEST_CASE("Grid operator = works as expected, middle element", "[operator]") {
	unsigned dimension = 3;
	std::string str = "abcdefghi"; 
	std::string str2 = "123456789"; 
	Grid board(dimension, dimension, str);
	Grid board2(dimension, dimension, str2);

	board = board2;

    REQUIRE(board.getVector()[1][0] == '_');
}

TEST_CASE("Grid existsBoxElement() function works for non-edge cases", "[existsBoxElement]") {
	std::string board = " 23456789abcdefg";
	unsigned index = 0;
	unsigned size = 4;

	Grid grid(size, size, board);

    REQUIRE(grid.existsBoxElement(index, index, ' ') == true);
}

TEST_CASE("Grid existsBoxElement() function works for edge cases", "[existsBoxElement]") {
	std::string board = "12345+789abcdefg";
	unsigned index = 0;
	unsigned size = 4;

	Grid grid(size, size, board);

    REQUIRE(grid.existsBoxElement(index, index, '+') == true);
}

TEST_CASE("Grid existsBoxElement() function returns false when necessary", "[existsBoxElement]") {
	std::string board = "123456789abcdefg";
	unsigned index = 0;
	unsigned size = 4;

	Grid grid(size, size, board);

    REQUIRE(grid.existsBoxElement(index, index, 'h') == false);
}