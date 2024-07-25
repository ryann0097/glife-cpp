#ifndef READER_H_
#define READER_H_

#include "life.h"
#include <cctype>
#include <string>

class Reader{
private:
    std::ifstream inputFile;
    std::string filename;
    short generations = 10, rows = 0, columns = 0;
    char aliveCellChar = 'O';

    //< OUTPUT ATTRIBUTES
    bool image_out = false;
    std::string alive_color;
    std::string bkg_color;
    int block_size = 0;
    std::string output_path;
    
    int fps = 0;
    
public:
    Reader(){}
    std::vector<cellCoord>aliveCellToSet;

    bool is_empty() const;
    bool is_empty_output() const;

    void processINI();
    void processFile();

    //=======[GETTERS METHODS]
    short getGenerations() const;
    short getRows() const;
    short getColumns() const;
    bool getOutput() const;
    std::string getAliveColor() const;
    std::string getBkgColor() const;
    int getBlockSize() const;
    std::string getFileName() const;
    std::string getOutputPath() const;
    int getFps() const;
    ~Reader(){}
};

#endif