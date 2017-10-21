#include <stdio.h>
#include <stdlib.h>
#include "ax12.h"
#include "coordinate.h"
#include "parse.h"
#include "path.h"

int main(int argc, char* argv[])
{
    printf("Starting Nutella printer program\n\n");
    if(argc != 3) {
        printf(
            "[ERROR][MAIN] Unexpected number of parameters\n\
            \tUsage: ./nutella <filename> <diameter>\n\
    		\t  filename: file wich contain points coordinates (ex: start5.txt)\n\
    		\t  diameter: diameter of the 'crepe'\n");
    }
    // Init AX12
    init_ax12();
    // Extract cooridnates from the input file
    path_t path     = parse(argv[1]);
    int    diameter = atoi(argv[2]);
    // Convert coordinates to motor angles
    compute_path(&path, diameter);
    // Go to center position ('crepe' center)
    move(center_pos());
    // Wait for user to continue
    printf("The printing head must be at the 'crepe' center\n");
    printf("Press Any Key to Continue\n");
    getchar();
    follow_path(&path);

    return 0;
}
