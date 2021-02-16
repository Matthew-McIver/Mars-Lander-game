#include <math.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "level.h"
#include "audio.h"

#include "graphics_lib.h"

#define WIDTH 640
#define HEIGHT 480

#define NUM_OBSTACLES 10

#define SCALE 0.5

struct Game
{
    ALLEGRO_FONT *myfont; /* Our font. */
    ALLEGRO_DISPLAY *display; /* Our display */
    ALLEGRO_EVENT_QUEUE *queue; /* Our events queue. */
    ALLEGRO_TIMER *timer; /* Our physics timer. */

    double FPS; /* How often to update per second. */

    bool first_tick;
    bool redraw;
    double this_time, prev_time, accum_time;
    double timer_events;
} game;

// define the lander struct
struct lander {
    double x,y;
    double speedX, speedY;
    double angle;
    double dryMass, fuel;
    double maxFuel;
    bool engineOn;
} lander;

// define the obstacle struct (asteroid, space debris, ect.)
struct obstacle {
    bool active;
    double x,y;
    double speedX, speedY;
    double angle;
    double radius;
} obstacle[NUM_OBSTACLES];

//Background & tile bitmaps.
BITMAP tiles;
BITMAP bkg;

//Game space render bitmap.
BITMAP scroll;

//Lander bitmaps.
BITMAP landerImg[2];

//Obstacle bitmaps.
BITMAP obstacleImg[6];

//Space background bitmaps.
BITMAP background;
BITMAP stars;

//Status bar bitmaps.
BITMAP fuelBar[3];
BITMAP timeBar[3];
BITMAP emptyBar[3];

//Coordinates of the viewport.
int mx = WIDTH/2, my = HEIGHT/2;

//Tile in every coordinate of map, unimplemented.
int map[75][100];

//Sets lives value as integer.
int lives;

//Takes tiles sprites out of a spritesheet, unused.
BITMAP grabFrame(BITMAP source, int width, int height, int startX, int startY, int columns, int frame)
{
    BITMAP temp = al_create_bitmap(width, height);

    int x = startX + (frame % columns) * width;
    int y = startY + (frame / columns) * height;

    al_set_target_bitmap(temp);
    al_draw_bitmap_region(source, x, y, width, height, 0, 0, 0);

    return temp;
}

/************************************
 * drawLander (void)

 * draws the lander in position with
   fire if engine on.
************************************/

void drawLander() {
    double x = lander.x;
    double y = lander.y;
    double angle = lander.angle;

    int i = (lander.engineOn && lander.fuel != 0) ? 1 : 0;
    BITMAP bitmap = landerImg[i];
    int h = al_get_bitmap_height(bitmap);
    int w = al_get_bitmap_width(bitmap);
    double L = sqrt(w*w + h*h)/2;
    double X = sin(angle + M_PI/4) * L * SCALE;
    double Y = cos(angle + M_PI/4) * L * SCALE;
    al_draw_scaled_rotated_bitmap(landerImg[i], 0, 0, x - X, y - Y, SCALE, SCALE, -angle, 0);
}

/************************************
 * drawObstacle (int)

 * draws the obstacle in position
************************************/
void drawObstacle(int n) {
    if (!obstacle[n].active)
        return;

    double x = obstacle[n].x;
    double y = obstacle[n].y;
    double angle = obstacle[n].angle;

    al_draw_scaled_rotated_bitmap(obstacleImg[n], 0, 0, x, y, 1, 1, angle, 0);
}
/************************************
 * drawUI (void)

 * draws the UI to the display.
************************************/
void drawUI() {
    double fuel = lander.fuel / lander.maxFuel;

    double barHeight = HEIGHT/4-6;
    al_draw_scaled_bitmap(emptyBar[1], 0, 0, 26, 6, WIDTH/16, HEIGHT/2 - barHeight, 13, barHeight, 0);
    al_draw_scaled_bitmap(emptyBar[2], 0, 0, 26, 6, WIDTH/16, HEIGHT/2 - barHeight - 6, 13, 6, 0);
    double fuelHeight = barHeight*fuel;
    al_draw_scaled_bitmap(fuelBar[0], 0, 0, 26, 6, WIDTH/16, HEIGHT/2, 13, 6, 0);
    al_draw_scaled_bitmap(fuelBar[1], 0, 0, 26, 6, WIDTH/16, HEIGHT/2 - fuelHeight, 13, fuelHeight, 0);
    al_draw_scaled_bitmap(fuelBar[2], 0, 0, 26, 6, WIDTH/16, HEIGHT/2 - fuelHeight - 6, 13, 6, 0);

    double time = (2*60 - game.accum_time) / (2*60);

    al_draw_scaled_bitmap(emptyBar[1], 0, 0, 26, 6, WIDTH/16 + 20, HEIGHT/2 - barHeight, 13, barHeight, 0);
    al_draw_scaled_bitmap(emptyBar[2], 0, 0, 26, 6, WIDTH/16 + 20, HEIGHT/2 - barHeight - 6, 13, 6, 0);
    double timeHeight = barHeight*time;
    al_draw_scaled_bitmap(timeBar[0], 0, 0, 26, 6, WIDTH/16 + 20, HEIGHT/2, 13, 6, 0);
    al_draw_scaled_bitmap(timeBar[1], 0, 0, 26, 6, WIDTH/16 + 20, HEIGHT/2 - timeHeight, 13, timeHeight, 0);
    al_draw_scaled_bitmap(timeBar[2], 0, 0, 26, 6, WIDTH/16 + 20, HEIGHT/2 - timeHeight - 6, 13, 6, 0);

    al_draw_textf(game.myfont, al_map_rgb_f(1, 1, 1), WIDTH/2, HEIGHT * 7/8, ALLEGRO_ALIGN_CENTRE,
                  "Altitude: %.0f", HEIGHT  * 10 - lander.y - 400);
    al_draw_textf(game.myfont, al_map_rgb_f(1, 1, 1), WIDTH/4, HEIGHT * 7/8, ALLEGRO_ALIGN_CENTRE,
                  "Lives: %d/5", lives);
}

/************************************
 * respawnObstacle (int)

 * respawns an obstacle near the
   lander heading somewhat towards
   it.
************************************/
void respawnObstacle(int n) {
    int side = 2*(rand()%2) - 1;
    int up = rand()%10 + 10;

    obstacle[n].x = lander.x + WIDTH * side;
    obstacle[n].x = lander.y + (HEIGHT * up)/20;

    obstacle[n].speedX = -side * 10;
    obstacle[n].speedY = -5;
};

/************************************
 * loadLevel (int)

 * loads a level into the world.
************************************/
void loadLevel(int n) {
    printf("LoadLevel.");
    lander.x = level[n].startX;
    lander.y = level[n].startY;
    lander.speedX = 0;
    lander.speedY = 0;
    lander.fuel = level[n].startFuel * lander.maxFuel;
    lander.engineOn = false;
    game.accum_time = 0;
    printf("Obstacles");
    int i, j;
    for (i = 0; i < NUM_OBSTACLES; i++) {
        obstacle[i].active = (i < level[n].obstacles);
    }
    //Supposed to render background image of different levels using tile system,
    // Due to time constraints only use static image now.
    /*
    al_set_target_bitmap(bkg);
    #define COLUMNS 3
    printf("Draw to bkg");
    for (i = 0; i < WIDTH * 10 / 64; i++){
        for (j = 0; j < HEIGHT * 10 / 64; j++){
            //BITMAP tile = grabFrame(tiles, 64, 64, 0, 0, COLUMNS, level[0].map[j][i]);
            //al_draw_bitmap(tile, i * 64, j * 64, 0);
            BITMAP tile = grabFrame(tiles, 64, 64, 0, 0, COLUMNS, 2);
            al_draw_bitmap(tile, 0, 0, 0);
        }
    }
    al_flip_display();
    al_set_target_bitmap(scroll);*/

    missionStatement(n, "Hello, and welcome to Mars Lander. Your goal as head spacetronaut, is to navigate the dangerous atmosphere of Mars using the mouse, and get our lander safely to its destination. We only have so much time and fuel to get there, so use both of these wisely! The two bars to the left show you how much you have left of each. Watch out for asteroids! They’re being pulled in by Mars’ gravity and may hit you. See if you can complete all 10 stages. Good luck!");
};

//Sets variables for physics.
double g = 3.711E1;
double force = 1000000;
double fuelUsage = 100;

/****************************************
 * updateLander (double)

 * Updates speed and position of lander.
****************************************/
void updateLander(double time) {
    lander.speedY += g * time;

    double fuel = fuelUsage * time;
    if (lander.engineOn && lander.fuel != 0) {
        fuel = (fuel < lander.fuel) ? fuel : lander.fuel;
        double mass = lander.dryMass + lander.fuel;
        double dv = (force / mass) * fuel / fuelUsage;
        lander.speedX -= dv * sin(lander.angle);
        lander.speedY -= dv * cos(lander.angle);
        lander.fuel -= fuel;
    }

    lander.x += lander.speedX * time;
    lander.y += lander.speedY * time;
    mx = lander.x - WIDTH/2;
    my = lander.y - HEIGHT/2;
}

/****************************************
 * updateObstacle (int, double)

 * Updates an obstacle's speed and
   position.
****************************************/
void updateObstacle(int n, double time) {
    if (!obstacle[n].active)
        return;

    obstacle[n].speedY += g * time;

    obstacle[n].x += obstacle[n].speedX * time;
    obstacle[n].y += obstacle[n].speedY * time;
}

/****************************************
 * setUpLander ()

 * Sets up the Lander's initial position.
****************************************/
void setUpLander(){
    lander.x = WIDTH;
    lander.y = HEIGHT;
    lander.speedX = 0;
    lander.speedY = 0;
    lander.angle = 0;
    lander.dryMass = 2445;
    lander.fuel = 2376;
    lander.maxFuel = 2376;
    lander.engineOn = false;
};

/****************************************
 * setUpObstacle (int)

 * Sets up the Obstacle's initial positions.
****************************************/
void setUpObstacle(int n){
    obstacle[n].active = false;
    obstacle[n].angle = 0;
    obstacle[n].radius = (n/(NUM_OBSTACLES-1) + 1)*4;
    obstacle[n].speedX = 0;
    obstacle[n].speedY = 0;
    obstacle[n].x = 0;
    obstacle[n].y = 0;
};

/****************************************
 * setLanderAngle (double)

 * Sets Lander's angle.
****************************************/
void rotateLander(double angle){
    while (angle > 2 * M_PI){
        angle -= 2 * M_PI;
    }
    while (angle < 0){
        angle += 2 * M_PI;
    }
    lander.angle += angle;
};

double rotationSpeed = M_PI/4;
double mouseX, mouseY;

/****************************************
 * getMousePosition (ALLEGRO_EVENT)

 * Sets Lander's angle.
****************************************/
void getMousePosition(ALLEGRO_EVENT event){
    mouseX = 2.0 * event.mouse.x;
    mouseY = 2.0 * event.mouse.y;
};

/****************************************
 * aimLander (double)

 * Gets the Lander to face the mouse.
****************************************/
void aimLander(double time) {
    double dy = -(my + mouseY - lander.y - HEIGHT/2);
    double dx = mx + mouseX - lander.x - WIDTH/2;
    if (dx * dy == 0) {
        return;
    }
    double targetAngle = atan(dy/dx) + M_PI/2;
    if (dx > 0 || (dx == 0 && dy > 0)) {
        targetAngle += M_PI;
    }
    double direction;
    double a = targetAngle - lander.angle;
    if (a > M_PI)
        direction = -1;
    else if (a > 0)
        direction = 1;
    else if (a > -M_PI)
        direction = -1;
    else
        direction = 1;
    double rotation = direction * rotationSpeed * time;
    double A = fabs(a);
    if (true || abs(rotation) > A) {
        lander.angle = targetAngle;
    } else {
        rotateLander(rotation);
    }
};

//Boolean shortcut to check if you've flown too far out of map or hit ground.
bool outOfBounds() {
    if (lander.x < WIDTH / 2)
        return true;
    if (lander.y < HEIGHT / 2)
        return true;
    if (lander.x > WIDTH * 19/2)
        return true;
    if (lander.y > HEIGHT * 19/2 - 150)
        return true;
    return false;
}

/* Called a fixed amount of times per second. */
static void tick(ALLEGRO_TIMER_EVENT* timer_event){
    game.prev_time = game.this_time;
    game.this_time = al_get_time();

    if (game.first_tick) {
        game.first_tick = false;
        return;
    }

    double duration = game.this_time - game.prev_time;

    aimLander(duration);
    updateLander(duration);

    int i;

    for (i = 0; i < NUM_OBSTACLES; i++) {
        updateObstacle(i, duration);
    }

    game.accum_time += duration;
    game.timer_events++;

    if (outOfBounds()) {
        printf("OOB");
        lives--;
        endAudioLoop();
        loadLevel(0);
    }

    if (game.accum_time > 2 * 60) {
        printf("OOT");
        lives--;
        endAudioLoop();
        loadLevel(0);
    }

    game.redraw = true;
}

//Draws one frame.
static void Draw() {
    al_set_target_bitmap(scroll);
    al_clear_to_color(al_map_rgb_f(0, 0, 0));
    al_draw_bitmap(stars, 0, 0, 0);
    al_draw_bitmap(bkg, 0, 0, 0);
    int i;
    drawLander();
    for (i = 0; i < NUM_OBSTACLES; i++){
        //drawObstacle(i);
    }

    al_flip_display();

    al_set_target_backbuffer(game.display);
    al_draw_bitmap_region(scroll, mx, my, WIDTH, HEIGHT, 0, 0, 0);
    drawUI();
    al_flip_display();
}

//Main game loop.
static void run(void) {
    ALLEGRO_EVENT event;
    while(lives > 0) {
        if (game.redraw && al_is_event_queue_empty(game.queue)) {
            Draw();
            game.redraw = false;
        }
        al_wait_for_event(game.queue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                return;
            case ALLEGRO_EVENT_MOUSE_AXES:
                getMousePosition(event);
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    return;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (event.mouse.button == 1){
                    lander.engineOn = true;
                    startAudioLoop();
                };
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if (event.mouse.button == 1){
                    lander.engineOn = false;
                    endAudioLoop();
                };
                break;
            case ALLEGRO_EVENT_TIMER:
                tick(&event.timer);
            break;
        }
    }
    char *statement;
    //int score = 4 * lander.fuel/lander.maxFuel +
    sprintf("Game over! You scored %d", score);
    missionStatement(0, "Game Over!");
}

/* Initialize the game. */
static void init(void) {
    game.FPS = 60;
    game.first_tick = true;
    game.redraw = false;

    setUpLander();

    int i;
    for (i = 0; i < NUM_OBSTACLES; i++){
        setUpObstacle(i);
    }

    setupLevels();

    landerImg[0] = al_load_bitmap("data/mars_game/lander_01.png");
    landerImg[1] = al_load_bitmap("data/mars_game/lander_02.png");

    fuelBar[0] = al_load_bitmap("data/mars_game/bar_fuel_bottom.png");
    fuelBar[1] = al_load_bitmap("data/mars_game/bar_fuel_mid.png");
    fuelBar[2] = al_load_bitmap("data/mars_game/bar_fuel_top.png");

    timeBar[0] = al_load_bitmap("data/mars_game/bar_time_bottom.png");
    timeBar[1] = al_load_bitmap("data/mars_game/bar_time_mid.png");
    timeBar[2] = al_load_bitmap("data/mars_game/bar_time_top.png");

    emptyBar[0] = al_load_bitmap("data/mars_game/bar_empty_bottom.png");
    emptyBar[1] = al_load_bitmap("data/mars_game/bar_empty_mid.png");
    emptyBar[2] = al_load_bitmap("data/mars_game/bar_empty_top.png");

    scroll = al_create_bitmap(WIDTH * 10, HEIGHT * 10);
    if (!scroll){
        printf("Error creating virtual background.");
        return;
    }

    bkg = al_load_bitmap("data/mars_game/bkg.png");
    al_save_bitmap("bkg.png", bkg);
    //bkg = al_create_bitmap(WIDTH * 10, HEIGHT * 10);
    if (!bkg){
        printf("Error creating virtual background.");
        return;
    }

    tiles = al_load_bitmap("data/mars_game/tile_map.bmp");
    if (!tiles){
        printf("Error loading tile map.");
        return;
    }

    stars = al_load_bitmap("data/mars_game/stars_background.png");

    game.myfont = al_load_font("data/fixed_font.tga", 0, 0);
    if (!game.myfont) {
        printf("data/fixed_font.tga not found\n");
        exit(1);
    }
    lives = 5;

    initAudio();
}

/* Cleanup. Always a good idea. */
static void cleanup(void){
    endAudioLoop();

    al_destroy_font(game.myfont);
    al_destroy_event_queue(game.queue);
    al_destroy_display(game.display);
    game.myfont = NULL;
}

//Sets up title screen.
static bool splashScreen() {
    startAudioLoop();
    const char *filename;
    filename = "data/mars_game/mars_background.png";
    background = al_load_bitmap(filename);
    if (!background){
        printf("background not loaded");
        return -1;
    }
    al_set_target_backbuffer(game.display);
    al_clear_to_color(al_map_rgb_f(0, 0, 0));
    al_draw_bitmap(background, 0, 0, 0);
    al_draw_filled_rectangle(WIDTH/2 - 100, HEIGHT/2 - 5, WIDTH/2 + 100, HEIGHT/2 + 20,
                             al_map_rgb_f(0.8, 0, 1));
    al_draw_textf(game.myfont, al_map_rgb_f(1, 1, 1), WIDTH/2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE,
                  "Welcome to Mars Lander!");
    al_draw_textf(game.myfont, al_map_rgb_f(1, 1, 1), WIDTH/2, 7*HEIGHT/8, ALLEGRO_ALIGN_CENTRE,
                  "Press any key to continue.");
    al_flip_display();

    ALLEGRO_EVENT event;
    while(1) {
        al_wait_for_event(game.queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                endAudioLoop();
                return false;
            case ALLEGRO_EVENT_KEY_DOWN:
                printf("Game On,");
                endAudioLoop();
                return true;
            case ALLEGRO_EVENT_MOUSE_AXES:
                getMousePosition(event);
            break;
        }
        al_flip_display();
    }
}

//Text pop up to inform the player.
void missionStatement(int n, char *statement) {
    al_stop_timer(game.timer);
    Draw();
    al_draw_textf(game.myfont, al_map_rgb_f(1, 1, 1), WIDTH/2, HEIGHT/3, ALLEGRO_ALIGN_CENTRE,
                  "MISSION %d\n\n%s", n + 1, statement);
    al_flip_display();
    ALLEGRO_EVENT event;
    while(1) {
        al_wait_for_event(game.queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                close(0);
            case ALLEGRO_EVENT_KEY_DOWN:
                al_start_timer(game.timer);
                return;
            case ALLEGRO_EVENT_MOUSE_AXES:
                getMousePosition(event);
            break;
        }
    }
}

//Main loop.
int main() {
    srand(time(NULL));

    if (!al_init()) {
        printf("Could not init Allegro.\n");
        return 1;
    }

    al_init_primitives_addon();
    al_init_font_addon();
    al_init_image_addon();
    al_install_mouse();
    al_install_keyboard();

    al_set_new_display_flags(ALLEGRO_WINDOWED);
    game.display = al_create_display(WIDTH, HEIGHT);
    if (!game.display) {
        printf("Could not create display.\n");
        return 1;
    }
    al_set_window_title(game.display, "Mars Game");

    init();

    game.timer = al_create_timer(1.000 / game.FPS);

    game.queue = al_create_event_queue();
    al_register_event_source(game.queue, al_get_display_event_source(game.display));
    al_register_event_source(game.queue, al_get_mouse_event_source());
    al_register_event_source(game.queue, al_get_keyboard_event_source());
    al_register_event_source(game.queue, al_get_timer_event_source(game.timer));

    al_start_timer(game.timer);

    if (splashScreen()) {
        printf(" gamer!\n");
        loadLevel(0);
        readAudioLoop("data/mars_game/thrusterFire_000.wav");
        //startAudioLoop();
        run();
    }
    cleanup();
    return;
}
