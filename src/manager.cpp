#include <iostream>
#include "manager.h"

void Manager::process() {
    if(lifeState == LifeState::CONFIG){
        newReader->processINI();
        image_out = newReader->getOutput();
        if(image_out){
            cell_color = newReader->getAliveColor(); // life
            bkg_color = newReader->getBkgColor(); // life
            block_size = newReader->getBlockSize(); // life
            output_path = newReader->getOutputPath(); // manager
        } else { fps = newReader->getFps(); }
    }
    else if (lifeState == LifeState::PROCESSING) {
        newReader->processFile();
        Rows = newReader->getRows(), Columns = newReader->getColumns(); 
        int Generations = newReader->getGenerations();
        newLife = new Life(Rows, Columns, Generations);
    }
    else if (lifeState == LifeState::INIT) {
        if(image_out){
            newLife->set_bkg_color(bkg_color);
            newLife->set_cell_color(cell_color);
            newLife->set_block_size(block_size);
            newLife->set_filename(newReader->getFileName());
            newLife->set_output(newReader->getOutputPath());
            newLife->create_canvas();
        } else { newLife->set_fps(newReader->getFps()); }
        newLife->fillMatrix(newReader->aliveCellToSet);
    }
    else if (lifeState == LifeState::COPY){
        if(image_out){
            end_flag = newLife->update_glife();
        } else { end_flag = newLife->update_glife_string(); }
    }
}

void Manager::update() {
    if (lifeState == LifeState::START){
        lifeState = LifeState::CONFIG;
    }
    else if(lifeState == LifeState::CONFIG){
        lifeState = LifeState::PROCESSING;
    }
    else if (lifeState == LifeState::PROCESSING){
        lifeState = LifeState::INIT;
    }
    else if (lifeState == LifeState::INIT) {
        lifeState = LifeState::COPY; // aqui faremos a copia da matriz original para o objeto copia.
    }
    else if (lifeState == LifeState::COPY) {
        lifeState = LifeState::VERIFY_END;
    }
    else if (lifeState == LifeState::VERIFY_END) {
        if (newLife->stable() || newLife->extinct() || !end_flag) {
            lifeState = LifeState::EXIBITION;
        } else {
            lifeState = LifeState::COPY; 
        }
    }
    else if ( lifeState == LifeState::EXIBITION){
        lifeState = LifeState::END;
    }
}



void Manager::render() {
    if (lifeState == LifeState::START) {
        std::cout << "\tWelcome to Life Game!\n";
    }
    else if (lifeState == LifeState::PROCESSING) {
        std::cout << "\n\tA'ight, let's start the processing...\n";
    }
    else if (lifeState == LifeState::EXIBITION){
        if(!image_out){
            std::cout << "\n\tWhoa! Processment done!\n";
            usleep(500000);
            newLife->print_glife();
        }
        else{
            std::cout << "\n\tWhoa! Processment done!\n";
            newLife->image_glife();
        }
    }
}
