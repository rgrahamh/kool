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
    player *runner = new player(5,(512 - 16),0,PLAYER,true);

    ground *gr = new ground(0, (512-16), 0, GROUND, false);

    track_scene ->getView(0)->setFollowing(runner, 256, 512);
    track_scene->addObject(bg);
    track_scene->addObject(gr);
    track_scene->addObject(runner);

    return track_scene;
}
