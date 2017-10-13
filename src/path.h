#ifndef _PATH_H_
#define _PATH_H_

typedef struct {
    float x;
    float y;
} point_t;

typedef struct {
    int nb_points;
    point_t * points;
} path_t;

/* Display a path using printf
** [in]  path: path to display
*/
void display_path(path_t * path);

#endif // _PATH_H_
