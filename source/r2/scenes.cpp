#include "scenes.h"
#include "objects.h"
#include "../headers/Globals.hpp"
#include <string>

Scene *track() {
    Scene *track_scene = new Scene(8192,512);
    background *bg = new background(0, 0, 0);
    bg->sprite_width = 8192;
    bg->sprite_height = 512;

    track_scene->addObject(bg);
    player *runner = new player(16,(512 - 64),1,PLAYER,true);

    float ground_height = 512.0 - 32.0;
    ground *gr = new ground(0, ground_height, 1, GROUND, false);
	
	int hurdle_height = 512 - 64;
    float hurdles[][2] = {
        {64, hurdle_height},
    };

    track_scene ->getView(0)->setFollowing(runner, -256, 512);
    track_scene->addObject(bg);
    track_scene->addObject(gr);
    track_scene->addObject(runner);
    for(int i = 0; i < 1; i++) {
        track_scene->addObject(new hurdle(hurdles[i][0], hurdles[i][1]));
    }

    return track_scene;
}
