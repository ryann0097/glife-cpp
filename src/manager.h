#ifndef MANAGER_H_
#define MANAGER_H_

#include "life.h"
#include "reader.h"

enum LifeState {
    START,
    CONFIG,
    PROCESSING,
    CREATE_CANVA,
    INIT,
    COPY,
    READING,
    VERIFY_END,
    END,
    LAST,
    EXIBITION
};

class Manager { // Classe Matriz
private:
    LifeState lifeState = START;
    Reader* newReader;
    Life* newLife;
    Canvas* newCanva;

    int Rows;
    int Columns;

    bool image_out = false;
    bool end_flag = false;
    std::string cell_color;
    std::string bkg_color;
    int block_size = 0;
    std::string output_path;
    int fps = 2;

public:
    Manager() {
        newReader = new Reader();
        newLife = nullptr;
        newCanva = nullptr;
    }
    void process();
    void update();
    void render();
    bool quit() { return (lifeState == END); }

    ~Manager() {
        delete newReader;
        delete newLife;
        delete newCanva;
    }
};

#endif
