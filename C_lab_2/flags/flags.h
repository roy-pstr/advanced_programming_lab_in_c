#ifndef FLAG_H
#define FLAG_H

#include <stdbool.h>

typedef struct Flag_st {
	bool is_on;
	int counter;
}Flag;

bool is_flag(Flag *flg){
	return (flg->is_on);
}

void update_counter(Flag *flg, int value) {

}


#endif
