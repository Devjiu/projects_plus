#include <stdio.h>
#include <stdlib.h>
#include <random>

struct cell {
	unsigned alive : 1;
};

#define __WORLD_H__ 10
#define __WORLD_W__ 10

cell world[__WORLD_W__][__WORLD_H__];



void create_worl(cell world[][__WORLD_H__]) {
	std::random_device rd;
	std::mt19937 gen(rd());
	//непонятно что за синтаксис
	std::uniform_int_distribution<> dis(1, 1000);

	for (int i = 0; i < __WORLD_H__; i++ ) {
		for (int j = 0; j < __WORLD_W__; j++) {
			unsigned int num = dis(gen);
			if (num % 2 == 0) {
				world[i][j].alive = 1;
			} else {
				world[i][j].alive = 0;
			}
		}
	}
}


unsigned int cout_live_cell(cell world[][__WORLD_H__]) {
	unsigned int count = 0;

	for (int i = 0; i < __WORLD_H__; i++) {
		for (int j = 0; j < __WORLD_W__; j++) {
			if (world[i][j].alive == 1) {
				count++;
			}
		}
	}
}


void where_is_neighbours(signed int nb[][2], 
							 unsigned int x, 
							 unsigned int y) {
	unsigned int i, j;
	unsigned int k = 0;
	for ( i = x - 1; i < x + 1; i++) {
		for ( j = y - 1; j < y + 1; j++ ) {
			if (i == x && j == y) {
				continue;
			}
			nb[k][0] = i;
			nb[k][0] = j;
			k++;
		}
	}
}

