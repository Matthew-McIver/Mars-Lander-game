#include "controller.h"

void Update(Controller *c, double time){
    c->Update(c->controller, time);
};
