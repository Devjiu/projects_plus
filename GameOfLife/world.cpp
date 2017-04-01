#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <random>
#include <chrono>
#include <thread>

struct cell {
	unsigned alive : 1;
};

#define __WORLD_H__ 30
#define __WORLD_W__ 30

cell world[__WORLD_W__][__WORLD_H__];



void create_world(cell world[][__WORLD_H__]) {
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


unsigned int count_live_cell(cell world[][__WORLD_H__]) {
	unsigned int count = 0;

	for (int i = 0; i < __WORLD_H__; i++) {
		for (int j = 0; j < __WORLD_W__; j++) {
			if (world[i][j].alive == 1) {
				count++;
			}
		}
	}
	return count;
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

unsigned int count_live_neighbours(cell world[][__WORLD_H__], unsigned int x, unsigned int y) {
	unsigned int count = 0;
	unsigned int i = 0;
	signed int nb[8][2];
	signed int _x, _y;

	where_is_neighbours(nb, x, y);

	for (i = 0; i < 8; i++) {
		_x = nb[i][0];
		_y = nb[i][1];

		if (_x < 0 || _y < 0 || _x > __WORLD_W__ || _y > __WORLD_H__) {
			continue;
		}

		if (world[_x][_y].alive == 1) {
			count++;
		}

		return count;
	}
}

void next_gen(cell world[][__WORLD_H__], cell prev_world[][__WORLD_H__]) {
	unsigned int i, j;
	unsigned int live_nb;
	cell c;

	for ( i = 0; i < __WORLD_W__; i++)	{
		for ( j = 0; j < __WORLD_H__; j++) {
			c = prev_world[i][j];
			live_nb = count_live_neighbours(prev_world, i, j);

			if (c.alive == 0) {
				if (live_nb == 3) {
					world[i][j].alive = 1;
				}
			}
			else {
				if (live_nb < 2 || live_nb > 3 ) {
					world[i][j].alive = 0;
				}
			}
		}
	}
}


void copy_world(cell src[][__WORLD_H__], cell dest[][__WORLD_H__]) {
	for (unsigned int i = 0; i < __WORLD_W__; i++) {
		for (unsigned int j = 0; j < __WORLD_H__; j++) {
			dest[i][j] = src[i][j];
		}
	}
}


int cmp_world(cell w1[][__WORLD_H__], cell w2[][__WORLD_H__]) {
	for (unsigned int i = 0; i < __WORLD_W__; i++) {
		for (unsigned int j = 0; j < __WORLD_H__; j++) {
			if (w1[i][j].alive != w2[i][j].alive) {
				return -1;
			}
		}
	}
	return 0;
}


void show_world(cell world[][__WORLD_H__]) {

	for (int i = 0; i < __WORLD_H__; i++) {
		for (int j = 0; j < __WORLD_W__; j++) {
			if (world[i][j].alive == 1) {
				std::cout << '*';
			} else {
				std::cout << '-';
			}
			std::cout << '-';
		}
		std::cout << std::endl;
	}
}




int main() {
	cell world[__WORLD_W__][__WORLD_H__];
	cell prev_world[__WORLD_W__][__WORLD_H__];

	create_world(world);

	unsigned int live_cells = -1;
	bool is_optimal = false;
	
	do {
		show_world(world);
		copy_world(world, prev_world);

		next_gen(world, prev_world);
		is_optimal = cmp_world(world, prev_world) == 0;
		live_cells = count_live_cell(world);

		if (is_optimal) {
			std::cout << "Optimal cnfiguration reached." << std::endl;
			create_world(world);
		}

		if (live_cells == 0) {
			std::cout << "All cells died." << std::endl;
			create_world(world);
		}

		std::this_thread::sleep_for(std::chrono::seconds(5));
	} while (true);
	system("pause");
}