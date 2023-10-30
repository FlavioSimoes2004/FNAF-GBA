#include <gb/gb.h>
#include <stdint.h>
#include "gbdk-rocks.h"


void main(void)
{
    SHOW_BKG;
    set_bkg_data(0, gbdk_rocks_TILE_COUNT,gbdk_rocks_tiles);
    set_bkg_tiles(0, 0, 20, 18, gbdk_rocks_map);
    // Loop forever
    while(1) {
		// Game main loop processing goes here
        scroll_bkg(1,0);
		// Done processing, yield CPU and wait for start of next frame
        vsync();
    }
}