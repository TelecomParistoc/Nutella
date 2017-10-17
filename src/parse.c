#include "parse.h"
#include <stdio.h>
#include <stdlib.h>

/* Return if the input caracter is a figure
** [in]  c: input character
** [out] 0 if c is not a figure, else, not 0
*/
static inline int isFigure(char c)
{
    return (c >= 48 && c <= 57);
}

/* Return the number of lines into a file
** [in]  file: file to parse
** [out] number of lines found
*/
static int get_nb_lines(FILE* file)
{
    int nb_lines = 0;
    int c;
    while((c = fgetc(file)) != EOF)
        if(c == '\n')
            nb_lines++;
    return nb_lines;
}

path_t parse(const char* filename)
{
    FILE* file = fopen(filename, "r");
    // Open file
    if(file == 0) {
        printf("[ERROR][PARSING] An error occured during file opening\n");
        exit(-1);
    }

    int c;
    int posX = 0;
    int posY = 0;
    // 0: read x, 1: read y
    int      mode   = 0;
    int      line   = get_nb_lines(file);
    point_t* points = malloc(sizeof(point_t) * line);
    path_t   path   = {line, points};

    // Read each character
    fseek(file, 0, SEEK_SET);
    line = 0;
    while((c = fgetc(file)) != EOF) {
        if(isFigure(c)) {
            if(mode)
                posY = posY * 10 + c - '0';
            else
                posX = posX * 10 + c - '0';
        } else if(c == '\n') {
            mode                = 0;
            path.points[line].x = posX;
            path.points[line].y = posY;
            line++;
            posX = 0;
            posY = 0;
        } else if(c == ' ') {
            mode = 1;
        } else {
            printf("[ERROR][PARSING] Unexpected character line %d: %c (%x)\n", line, c, c);
            exit(-1);
        }
    }
    fclose(file);
    return path;
}
