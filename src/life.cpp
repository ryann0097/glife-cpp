
#include "life.h"
#include "./ext_lib/lodepng.h"

void encode_png(const char* filename, const unsigned char* image, unsigned width, unsigned height) {
    std::vector<unsigned char> png;
    unsigned error = lodepng::encode(png, image, width, height);

    if (error != 0U) {
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        return;
    }

    // Save the PNG to a file
    error = lodepng::save_file(png, filename);
    if (error != 0U) {
        std::cout << "file save error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}

void Life::fillMatrix(const std::vector<cellCoord>&aliveCellToSet){
    for(int i = 0; i < aliveCellToSet.size(); ++i){
        int current_row = aliveCellToSet[i].row;
        int current_column = aliveCellToSet[i].column;
        Matrix[current_row][current_column] = 1;
    }
}

void Life::set_bkg_color(const std::string &color){  bkg_color = color; }
void Life::set_cell_color(const std::string &color){ cell_color = color; }
void Life::set_block_size(const int &bs){ block_size = bs; }
void Life::set_filename(const std::string &fm){ filename = fm; }
void Life::set_output(const std::string &op){ output = op; }
void Life::set_fps(const int &f){ fps = f; }

int Life::aliveCellVerifier(const int& row, const int& column) const { return Matrix[row][column]; }

int Life::aliveCellVerifier(const int& row, const int& column, const int& rowOffset, const int& columnOffset) const{
    int result_row = row + rowOffset;
    int result_column = column + columnOffset;
    if ((result_row < 0 || result_row >= Rows) || (result_column < 0 || result_column >= Columns)) { return 2; } 
    else { return Matrix[result_row][result_column]; }
}

int Life::aliveCellsCounter(const int& row, const int& column) const{
    int all_neighbors = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j){
            if(i == 0 && j == 0){ continue; }
            else if(aliveCellVerifier(row, column, i, j) == 1){ all_neighbors++; }
        }
    } return all_neighbors;
}

bool Life::stable(){
    for(int i = 0; i < Rows; ++i){
        for (int j = 0; j < Columns; ++j) {
            if(aliveCellsCounter(i, j) <= 1 || aliveCellsCounter(i, j) >= 4){ return false; }
        }
    } return true;
}

bool Life::extinct(){
    for (int i = 0; i < Rows; ++i) {
        for (int j = 0; j < Columns; ++j) {
            if (Matrix[i][j] == 1) { return false; }
        }
    } return true;
}

void Life::create_canvas(){
    newCanva = new Canvas(Rows, Columns, block_size);
}

void Life::copying(Life& other){
    for(int i = 0; i < Rows; ++i){
        for(int j = 0; j < Columns; ++j){ other.Matrix[i][j] = Matrix[i][j]; }
    }
}

std::string Life::glife_string(Life &other){
    std::ostringstream current_glife;
    for(int i = 0; i < Rows; ++i){
        current_glife << "["; 
        for(int j = 0; j < Columns; ++j){
            if(other.Matrix[i][j] == 1){
                current_glife << " * ";
            } else { current_glife << "   ";}
        }
        current_glife << "]\n";
    }
    return current_glife.str();
}

bool Life::saving(Life& other){
    std::vector<cellCoord> genSave;
    for(int i = 0; i < Rows; ++i){
        for(int j = 0; j < Columns; ++j){ 
            if(other.Matrix[i][j] == 1){
                genSave.emplace_back(cellCoord{i, j}); // Queremos apenas as coordenadas para pintar o canvas
            }
        }
    }
    if(no_repeat.find(genSave) != no_repeat.end()){ return false; } 
    else{ no_repeat[genSave] = genCounter; genCounter++; glife_coord.push_back(genSave); return true; }
}


bool Life::saving_string(Life& other){
    std::string genSave = glife_string(other);
    if(no_repeat_string.find(genSave) != no_repeat_string.end()){
        return false;
    } else { no_repeat_string[genSave] = genCounter; genCounter++; return true; }
}

bool Life::update_glife_string(){
    Life tempLife(Rows, Columns);
    copying(tempLife);
    if(saving_string(tempLife)){
        glife_view.push_back(glife_string(tempLife));
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Columns; ++j) {
                int aliveNeighbors = tempLife.aliveCellsCounter(i, j);
                if(tempLife.Matrix[i][j] == 1){
                    if(aliveNeighbors < 2 || aliveNeighbors > 3){ Matrix[i][j] = 0; }
                } else {
                    if(aliveNeighbors == 3){ Matrix[i][j] = 1; }
                }
            }
        }
        return true;
    } else {
        return false;
    }
}

bool Life::update_glife(){
    Life tempLife(Rows, Columns);
    copying(tempLife);
    if(saving(tempLife)){
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Columns; ++j) {
                int aliveNeighbors = tempLife.aliveCellsCounter(i, j);
                if(tempLife.Matrix[i][j] == 1){
                    if(aliveNeighbors < 2 || aliveNeighbors > 3){ Matrix[i][j] = 0; }
                } else {
                    if(aliveNeighbors == 3){ Matrix[i][j] = 1; }
                }
            }
        }
        return true;
    } else {
        return false;
    }
}

void Life::print_glife(){
    for(const auto & i : glife_view){
        std::cout << i << "\n";
        usleep(1000000 / fps);
        std::cout << "\033[2J\033[1;1H";
    }
}

int Life::image_glife() {
    int counter = 0;
    for (const auto& vector : glife_coord) {
        newCanva->clear(color_pallet[bkg_color]);
        for (const auto& point : vector) {
            size_t square_x = point.row * block_size;
            size_t square_y = point.column * block_size;

            for (size_t i = 0; i < block_size; ++i) {
                for (size_t j = 0; j < block_size; ++j) {
                    size_t pixel_x = square_x + i;
                    size_t pixel_y = square_y + j;
                    newCanva->pixel(pixel_x, pixel_y, color_pallet[cell_color]);
                }
            }
        }
        std::ostringstream output_name;
        output_name << output << "_" << counter << ".png";
        std::string archive_name = output_name.str();
        const char* name = archive_name.c_str();
        encode_png(name, newCanva->pixels(), newCanva->width(), newCanva->height());
        counter++;
    }
    return 0;
}

