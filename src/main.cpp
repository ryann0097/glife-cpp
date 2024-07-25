#include "life.h"
#include "manager.h"

int main(int argc, char const *argv[]){
    Manager newManager;
    
    while(!newManager.quit()){
        newManager.process();
        newManager.update();
        newManager.render();
        // std::cout << "\033[2J\033[1;1H";
    } 
    return 0;
}