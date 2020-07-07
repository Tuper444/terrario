#include <gint/gray.h>
#include <gint/std/stdio.h>
#include <gint/std/stdlib.h>

#include "syscalls.h"
#include "map.h"
#include "entity.h"
#include "render.h"

// Syscalls
const unsigned int sc003B[] = { SCA, SCB, SCE, 0x003B };
const unsigned int sc003C[] = { SCA, SCB, SCE, 0x003C };
const unsigned int sc0236[] = { SCA, SCB, SCE, 0x0236 };

int main(void)
{
	struct Map map;
	struct Player player = {
		{0, 0, 0.0, 0.0, false, 12, 21},
		100,
		{0, 0},
		{0, 0},
		&updatePlayer,
		&handleCollisions
	};
	int ticks;
	char buf[10];

	srand(RTC_GetTicks());

	generateMap(&map);

	gray_delays(920, 1740);
	gray_start();

	while(1)
	{
		ticks = RTC_GetTicks();
		player.update(&map, &player);
		render(&map, &player);
		sprintf(buf, "%d", RTC_GetTicks() - ticks);
		gtext(0, 0, buf, C_BLACK, C_WHITE);
		gupdate();
//		30FPS
		while(!RTC_Elapsed_ms(ticks, 33)){}
	}

	return 1;
}
