#ifndef _PARSE_H_
#define _PARSE_H_

#include "path.h"

/* Parse a file and get all coordinates
** See ../star5.txt as example
** [in]  filename: name of the file to parse
** [out] path found in the file
*/
path_t      parse(const char * filename);

#endif // _PARSE_H_
