# ifndef LEARNING_H
#define LEARNING_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

# define EPSILON (0.00001)

/*
	type: pointer type is 1.0, vector type is 0.0;
*/
typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	float	type;
}	t_tuple;


#endif
