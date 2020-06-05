#include <stdlib.h>

void rrt(
	int dim,			// number of dimensions that Cspace have 
	int node_count, 		// size of tree
	float max_step, 		// max length that edges can have
	float *boundary,		// lower and upper limits of Cspace
	float *start,			// root node
	float *goal, 			// goal point and radius (pass NULL if you want to search all space)
	float(*d)(float*, float*),	// distance function
	int(*coll)(float*), 		// collision function, if the configuration is Cfree than it should return 0
	float(*rd)(int),		// random function that take a seed and generate a number between [0, 1]
	float **conf_data,		// configurations of nodes will be stored in this
	unsigned short **parent_data)	// parent of every node will be stored in this
{
	int i, j;
	unsigned short node, nearest_node, offset, *parent;
	float distance, min_distance, pos_inf, tmp, *node_conf, *sample;

	pos_inf = 1.0f / 0.0f;

	(*parent_data) = malloc(sizeof(unsigned short) * node_count);
	(*conf_data) = malloc(sizeof(float) * node_count * dim);
	sample = malloc(sizeof(float) * dim);

	node_conf = *conf_data;
	parent = *parent_data;

	for(i = 0; i < dim; i++)
		node_conf[i] = start[i];

	for(i = 1; i < node_count; i++){
		do{
			for(j = 0; j < dim; j++){
				offset = 2 * j;
				sample[j] = boundary[offset] + rd(i) * (boundary[offset + 1] - boundary[offset]);
			}
		}while(coll(sample));

		min_distance = pos_inf;

		for(j = 0; j < i; j++){
			distance = d(&node_conf[j * dim], sample);

			if(distance < min_distance){
				min_distance = distance;
				nearest_node = j;
			}
		}

		if(min_distance > max_step){
			tmp = (max_step / min_distance);
			offset = nearest_node * dim;

			for(j = 0; j < dim; j++)
				sample[j] = node_conf[offset + j] + tmp * (sample[j] - node_conf[offset + j]);
		}

		parent[i] = nearest_node;
		offset = i * dim;

		for(j = 0; j < dim; j++)
			node_conf[offset + j] = sample[j];

		if(goal){
			distance = d(&node_conf[offset], goal);
			if(distance < goal[dim])
				break;
		}
	}
}

int main()
{
	float *node;
	unsigned short *parent;

	float boundary[] = {0.0f, 10.0f, 0.0f, 10.0f};
	float start[] = {3.0f, 3.0f};

	rrt(2, 30000, 1.0f, boundary, start, 0, 0, 0, 0, &node, &parent);
	return 0;
}
