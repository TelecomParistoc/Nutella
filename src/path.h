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

/* Find when stopping pump in mm from the beginning
*/
int find_when_stop_pump(path_t * path);

#endif // _PATH_H_
