#ifndef LIFE_H_
#define LIFE_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <unordered_map>
#include "./ext_lib/canvas.h"

using namespace life;

struct cellCoord {
    int row = 0, column = 0;
    bool operator==(const cellCoord& other) const {
        return row == other.row && column == other.column;
    }
};

namespace std {
    template <>
    struct hash<cellCoord> {
        size_t operator()(const cellCoord& coord) const {
            return hash<int>()(coord.row) ^ hash<int>()(coord.column);
        }
    };

    template <>
    struct hash<std::vector<cellCoord>> {
        size_t operator()(const std::vector<cellCoord>& vec) const {
            size_t seed = 0;
            for (const auto& coord : vec) {
                seed ^= hash<cellCoord>()(coord) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

class Life {
private:
    int Rows, Columns, genCounter = 0, genNum;
    bool image_out = false;
    int** Matrix;

    std::string bkg_color;
    std::string cell_color;
    int block_size = 0;
    std::string output;
    std::string filename;

    int fps;

    Canvas *newCanva; // rows, columns, blocksize, colors

    std::unordered_map<std::vector<cellCoord>, int> no_repeat;
    std::unordered_map<std::string, int> no_repeat_string;
    std::vector<std::string>glife_view;
    std::vector<std::vector<cellCoord>>glife_coord;

public:
    Life(){}

    Life(const int nRow, const int nCol) : Rows(nRow), Columns(nCol) {
        Matrix = new int*[nRow];
        for(int i = 0; i < nRow; ++i){ Matrix[i] = new int[nCol](); }
    }

Life(const int nRow, const int nCol, const int numOfGen) : Rows(nRow), Columns(nCol), genNum(numOfGen) {
    Matrix = new int*[nRow];
    for(int i = 0; i < nRow; ++i){ Matrix[i] = new int[nCol](); }
}


void set_bkg_color(const std::string &color);
void set_cell_color(const std::string &color);
void set_block_size(const int &bs);
void set_filename(const std::string &filename);
void set_output(const std::string &output);
void set_fps(const int &f);

void fillMatrix(const std::vector<cellCoord>& aliveCellToSet);

bool operator==(const Life& other) const {
    for (int i = 0; i < Rows; ++i) {
        for (int j = 0; j < Columns; ++j) {
            if(other.Matrix[i][j] != Matrix[i][j]){ return false; }
        }
    } return true;
}

int aliveCellVerifier(const int& row, const int& column)const;
int aliveCellVerifier(const int& row, const int& column, const int& rowOffset, const int& columnOffset) const;
int aliveCellsCounter(const int& row, const int& column) const;

bool stable();
bool extinct();
void create_canvas();

//===[SAVING AND PROCESSMENT FUNCTIONS]
bool saving(Life &other);
bool saving_string(Life &other);

void copying(Life& other);
std::string glife_string(Life &other); //< Stringficação de uma matriz para a opção de geração textual

bool update_glife(); //< Update para geração imagética
bool update_glife_string(); //< Update para geração textual

void print_glife();
int image_glife();

bool endGen(){return genCounter == genNum;}

~Life(){
    for(int i = 0; i < Rows; ++i){ delete[] Matrix[i]; }
        delete[] Matrix;
}
}; // Life Class

#endif
#ifndef LIFE_H_
#define LIFE_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <unordered_map>
#include "./ext_lib/canvas.h"

using namespace life;

/**
 * @brief Struct representing coordinates of a cell.
 */
struct cellCoord {
    int row = 0, column = 0;

    /**
     * @brief Equality operator for cellCoord.
     */
    bool operator==(const cellCoord& other) const {
        return row == other.row && column == other.column;
    }
};

namespace std {
    /**
     * @brief Hash specialization for cellCoord struct.
     */
    template <>
    struct hash<cellCoord> {
        size_t operator()(const cellCoord& coord) const {
            return hash<int>()(coord.row) ^ hash<int>()(coord.column);
        }
    };

    /**
     * @brief Hash specialization for vector of cellCoord.
     */
    template <>
    struct hash<std::vector<cellCoord>> {
        size_t operator()(const std::vector<cellCoord>& vec) const {
            size_t seed = 0;
            for (const auto& coord : vec) {
                seed ^= hash<cellCoord>()(coord) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

/**
 * @brief Class representing the Game of Life simulation.
 */
class Life {
private:
    int Rows, Columns, genCounter = 0, genNum;
    bool image_out = false;
    int** Matrix;

    std::string bkg_color;
    std::string cell_color;
    int block_size = 0;
    std::string output;
    std::string filename;

    int fps;

    Canvas *newCanva;

    std::unordered_map<std::vector<cellCoord>, int> no_repeat;
    std::unordered_map<std::string, int> no_repeat_string;
    std::vector<std::string> glife_view;
    std::vector<std::vector<cellCoord>> glife_coord;

public:
    /**
     * @brief Default constructor.
     */
    Life(){}

    /**
     * @brief Constructor initializing with number of rows and columns.
     * @param nRow Number of rows.
     * @param nCol Number of columns.
     */
    Life(const int nRow, const int nCol) : Rows(nRow), Columns(nCol) {
        Matrix = new int*[nRow];
        for(int i = 0; i < nRow; ++i){ Matrix[i] = new int[nCol](); }
    }

    /**
     * @brief Constructor initializing with number of rows, columns, and generations.
     * @param nRow Number of rows.
     * @param nCol Number of columns.
     * @param numOfGen Number of generations.
     */
Life(const int nRow, const int nCol, const int numOfGen) : Rows(nRow), Columns(nCol), genNum(numOfGen) {
    Matrix = new int*[nRow];
    for(int i = 0; i < nRow; ++i){ Matrix[i] = new int[nCol](); }
}

    // Setters
void set_bkg_color(const std::string &color);
void set_cell_color(const std::string &color);
void set_block_size(const int &bs);
void set_filename(const std::string &filename);
void set_output(const std::string &output);
void set_fps(const int &f);

    // Matrix operations
void fillMatrix(const std::vector<cellCoord>& aliveCellToSet);

    // Comparison operator
bool operator==(const Life& other) const;

    // Cell state operations
int aliveCellVerifier(const int& row, const int& column) const;
int aliveCellVerifier(const int& row, const int& column, const int& rowOffset, const int& columnOffset) const;
int aliveCellsCounter(const int& row, const int& column) const;

    // Stability check
bool stable();
bool extinct();

    // Canvas operations
void create_canvas();

    // Saving and processing functions
bool saving(Life &other);
bool saving_string(Life &other);
void copying(Life& other);
std::string glife_string(Life &other);
bool update_glife();
bool update_glife_string();
void print_glife();
int image_glife();

    // Utility functions
bool endGen() { return genCounter == genNum; }

    /**
     * @brief Destructor.
     */
~Life() {
    for(int i = 0; i < Rows; ++i){ delete[] Matrix[i]; }
        delete[] Matrix;
}
}; // Life Class

#endif // LIFE_H_
