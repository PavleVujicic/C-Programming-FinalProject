#include "escape.h"

int main(int argc, char* argv[]) {
    
    if (argc == 1) {
        
        runEscape();
    } else if (argc == 2) {
        
        char* ip = argv[1];
        viewEscape(ip);
    } else {
        printf("Usage: %s [ip]\n", argv[0]);
        return 1;
    }

    return 0;
}

