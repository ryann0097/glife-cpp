#include "reader.h"

bool Reader::is_empty() const {
    return filename.empty();
}

bool Reader::is_empty_output() const {
    return (image_out && output_path.empty());
}

void Reader::processINI() {
    std::ifstream ini_file("glife.ini");
    if (!ini_file.is_open()) {
        std::cerr << "\t>> tErro: Não foi possível abrir arquivo para leitura.\n";
        return;
    }
    std::string line;
    bool in_image_section = false;
    bool in_text_section = false;

    while (std::getline(ini_file, line)) {
        if(line.empty() || line[0] == ';'){ continue; }

        std::size_t pos = line.find(';'); // Esse negócio é para desconsiderar comentários de orientação p/ preenchimento
        if(pos != std::string::npos){ line = line.substr(0, pos); }

        if(line.find("[Image]") != std::string::npos){ // Verificação de seções de acordo com o que o caba escolheu de saída
            in_image_section = true;
            in_text_section = false;
            continue;
        } 
        else if(line.find("[Text]") != std::string::npos){
            in_text_section = true;
            in_image_section = false;
            continue;
        }
        if(in_image_section) {
            if(line.find("alive") != std::string::npos){ alive_color = line.substr(line.find('=') + 1); } 
            else if(line.find("bkg") != std::string::npos){ bkg_color = line.substr(line.find('=') + 1); } 
            else if(line.find("block_size") != std::string::npos){ block_size = std::stoi(line.substr(line.find('=') + 1)); } 
            else if(line.find("path") != std::string::npos){ output_path = line.substr(line.find('=') + 1); }
        } 
        else if(in_text_section){
            if(line.find("fps") != std::string::npos){ fps = std::stoi(line.substr(line.find('=') + 1)); }
        } 
        else{
            if(line.find("input_cfg") != std::string::npos){ filename = line.substr(line.find('=') + 1); } 
            else if(line.find("generate_image") != std::string::npos){ image_out = (line.find("true") != std::string::npos); } 
            else if(line.find("max_gen") != std::string::npos){ generations = std::stoi(line.substr(line.find('=') + 1)); }
        }
    } 
    if(is_empty()){std::cerr << "\t>> Erro: O campo de arquivo para leitura está vazio.\n";}
    else if(is_empty_output()){std::cerr << "\t>> Erro: O campo de arquivo para saída está vazio.\n"; }
    ini_file.close();   
}

void Reader::processFile(){
    inputFile.open(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Erro ao abrir arquivo para leitura\n";
        return;
    }
    std::string lineToBeRead;
    int counter = 0;
    while (std::getline(inputFile, lineToBeRead)) {
        if (counter == 0) {
            size_t pos = lineToBeRead.find(' ');
            if (pos == std::string::npos) {
                std::cerr << "The input line may be \"[row_size],[column_size]\"\n";
                return;
            }
            rows = std::stoi(lineToBeRead.substr(0, pos));
            columns = std::stoi(lineToBeRead.substr(pos + 1));
            std::cout << "\tMatrix dimensions: " << rows << "x" << columns << "\n";
        } else if (counter == 1) {
            aliveCellChar = lineToBeRead[0];
            std::cout << "\tAlive cell symbol: " << aliveCellChar << "\n";
        } else {
            for (size_t i = 0; i < lineToBeRead.size(); ++i) {
                if (lineToBeRead[i] == aliveCellChar) {
                    cellCoord newToSet;
                    newToSet.row = counter - 2;
                    newToSet.column = i;
                    aliveCellToSet.push_back(newToSet);
                }
            }
        } counter++;
    } inputFile.close();
}

short Reader::getGenerations() const { return generations; }
short Reader::getRows() const { return rows; }
short Reader::getColumns() const { return columns; }
bool Reader::getOutput() const { return image_out; }
std::string Reader::getAliveColor() const { return alive_color; }
std::string Reader::getBkgColor() const { return bkg_color; }
int Reader::getBlockSize() const { return block_size; }
std::string Reader::getFileName () const { return filename; }
std::string Reader::getOutputPath() const { return output_path; }
int Reader::getFps() const { return fps; }


