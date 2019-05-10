#include "scenes.h"
#include "objects.h"
#include "../headers/Globals.hpp"
#include <string>

Scene *track() {
    Scene *track_scene = new Scene(1200, 600);
    background *bg = new background(1200, 500, 0);

    track_scene->addObject(bg);
    player *runner = new player(50,50,0,PLAYER,false);
    track_scene ->getView(0)->setFollowing(runner, 100, 500);
    track_scene->addObject(runner);
    track_scene->addObject(bg);



    return track_scene;
}
