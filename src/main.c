#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include "path.h"
#include "coordinate.h"

int main(int argc, char * argv[])
{
    if(argc != 3) {
        printf("[ERROR][MAIN] Unexpected number of parameters\n\
            \tUsage: ./nutella <filename> <diameter>\n\
    		\t  filename: file wich contain points coordinates (ex: start5.txt)\n\
    		\t  diameter: diameter of the 'crepe'\n");
    }
    path_t path = parse(argv[1]);
    int diameter = atoi(argv[2]);
#ifdef DEBUG
    printf("[DEBUG][PARSE] path after parsing:\n");
    display_path(&path);
#endif
    resize_coordinates(&path, diameter);
#ifdef DEBUG
    printf("[DEBUG][RESIZE] path after resizing and scaling:\n");
    display_path(&path);
#endif

    return 0;
}
