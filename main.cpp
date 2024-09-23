//=================================================================
// The main program file.
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


// Projet includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
//#include "mbed2/299/drivers/LocalFileSystem.h"
#include "speech.h"
#include <cstdio>
#include <math.h>
#include <time.h>

#define CITY_HIT_MARGIN 1
#define CITY_UPPER_BOUND (SIZE_Y-(LANDSCAPE_HEIGHT+MAX_BUILDING_HEIGHT))

// Helper function declarations
void playSound(char* wav);

bool menu;
/////////////////////////
// Struct of Player 
/////////////////////////

/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;            // Current locations
    int px, py;         // Previous locations
    bool has_key;       // flag when obtained the key
    bool game_solved;   // flag when game is complete
    bool talked_to_npc; // flag when you've talked to npc
    bool talked_to_enterman2;
    bool has_magic_milk;
    bool bacon_strip;
    bool has_tnt;
    int lives;
    bool jumping;
    int powders;
    bool feather;
    int talked_to_villager; //0 first time 
                            //1 already talked
                            //2 done with him
    int xp;
    int level;
    bool talked_about_ultimate_attack;
    bool red;
    

    //You will need to add more flags as needed

} Player;

int chicken_count;

/////////////////////////
// Get Action
/////////////////////////

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possible return values are defined below.
 * Get Actions from User (pushbuttons, and nav_switch)
 * Based on push button and navigation switch inputs, determine which action
 * needs to be performed (may be no action).
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define SPECIAL_BUTTON_2 2
#define ATTACK_BUTTON 3
#define GO_LEFT 4
#define GO_RIGHT 5
#define GO_UP 6
#define GO_DOWN 7
#define SPECIAL_BUTTON 8
#define JUMP 9
# define MENU_BUTTON 10

int get_action(GameInputs inputs)
{
    //******************
    // TODO: Implement
    //******************
    
    // 1. Check your action and menu button inputs and return the corresponding action value
    
    // 2. Check for your navigation switch inputs and return the corresponding action value
    
    // If no button is pressed, just return no action value
        // Check for button presses first
    
    if (inputs.b1 && inputs.b3 && inputs.b4) {
        return MENU_BUTTON;
    }
    if (inputs.b1) {
        return ACTION_BUTTON;
    } 
    if (inputs.b2) {
        return SPECIAL_BUTTON_2;
    } 
    if (inputs.b3) {
        return ATTACK_BUTTON;
    } 
    if (inputs.b4) {
        return SPECIAL_BUTTON;
    }

    if (inputs.ns_center) {
        return JUMP;
    } 
    if (inputs.ns_up) {
        return GO_UP;
    } 
    if (inputs.ns_down) {
        return GO_DOWN;
    } 
    if (inputs.ns_left) {
        return GO_LEFT;
    } 
    if (inputs.ns_right) {
        return GO_RIGHT;
    }
        // If no button is pressed, just return no action value
    return NO_ACTION;

}



/////////////////////////
// Helper Functions:
/////////////////////////
// Feel free to define any helper functions here for update game





/////////////////////////
// Update Game
/////////////////////////

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
int update_game(int action)
{
    
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    
    MapItem* item = NULL;

    MapItem* north = get_north(Player.x, Player.y);
    MapItem* south = get_south(Player.x, Player.y);
    MapItem* west = get_west(Player.x, Player.y);
    MapItem* east = get_east(Player.x, Player.y);
    

    uLCD.locate(0,15);
    char livesString[20]; // Allocate enough space for the formatted string
    sprintf(livesString, "Lives: %d Level: %d", Player.lives, Player.level);
    uLCD.puts(livesString);



    

    //******************
    // TODO: Implement
    //******************

    
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.


    switch(action)
    {
        case GO_UP:
            //TODO: Implement
            //1. Check the item north of the player
            //2. Make sure to not walk through walls
            //3. If it is not a wall, the walk up by updating player's coordinates
            if(north->walkable) {
                Player.red = false;
                if(north->type == FIRE && !Player.jumping) {
                    Player.lives--;
                    speech("life lost", "you burned");
                    Player.red = true;
                }
            Player.y -= 1;
            }
            return FULL_DRAW;
            
        case GO_LEFT:
            //TODO: Implement
            if(west->walkable) {
                Player.red = false;
                if(west->type == FIRE && !Player.jumping) {
                    Player.lives--;
                    speech("life lost", "you burned");
                    Player.red = true;
                }
            Player.x -= 1;
            }
            return FULL_DRAW;
            
        case GO_DOWN:
            if(south->walkable) {
                Player.red = false;
                if(south->type == FIRE && !Player.jumping) {
                    Player.lives--;
                    speech("life lost", "you burned");
                    Player.red = true;
                }
            Player.y += 1;
            }
            return FULL_DRAW;
            
        case GO_RIGHT:
            if(east->walkable) {
                Player.red = false;
                if(east->type == FIRE && !Player.jumping) {
                    Player.lives--;
                    speech("life lost", "you burned");
                    Player.red = true;
                }
            Player.x += 1;
            }
            return FULL_DRAW;

        case JUMP:
            if (Player.talked_to_villager == 2) {
                Player.jumping = !Player.jumping;
            } else {
                speech("You must", "do whatever");
                speech("the villager", "asks you");
                speech("to do,", "in order");
                speech("to get", "the ability");
                speech("to JUMP", "!!!");
            }
            return FULL_DRAW;
            


        case ACTION_BUTTON:

            //******************
            // TODO: Implement
            //******************

            // 1. Check if near NPC, 
            //     - if so, mark the player has talked and give instructions on what to do
            //     - if the game is solved (defeated Buzz), give the player the key
            //     - return FULL_DRAW to redraw the scene
            if (south->type == TNT || west->type == TNT
                || north->type == TNT || east->type == TNT) {
                    if (Player.has_key && get_active_map_index() == 0) {
                        return GAME_OVER;
                    }
            }
            //villager
            //0 first time 
            //1 already talked
            //2 done with him and have the ability to jump
            if (south->type == VILLAGER || west->type == VILLAGER 
                || north->type == VILLAGER || east->type == VILLAGER) {
                if (Player.talked_to_villager == 0) {
                    speech("Hello,", "visitor!");
                    speech("I am the.", "villager");
                    speech("I can,", "give you!");
                    speech("the power", "to jump");
                    speech("but first", "you have");
                    speech("to kill a", "chicken");
                    speech("and get", "3 powders");
                    speech("from attacking", "the TNTs!");
                    Player.talked_to_villager = 1;
                } else if (Player.talked_to_villager == 1 && (Player.powders < 3 || !Player.feather)) {
                    speech("Go kill", "a chicken");
                    speech("and get", "3 powders!");
                } else if (Player.powders == 3 || Player.feather) {
                    speech("You succeded", "bravo!");
                    speech("Here you go,", "I give you");
                    speech("the ability", "to JUMP!");
                    speech("You can now", "jump over");
                    speech("fire!!!", "");
                    speech("press center", "on joystick");
                    Player.talked_to_villager = 2;
                }
                }

            if (south->type == NPC || west->type == NPC 
                || north->type == NPC || east->type == NPC) {
                if (!Player.talked_to_npc) {
                    speech("Greetings,", "adventurer!");
                    speech("I am the", "Enterman.");
                    speech("The creeper and", "the cow from");
                    speech("McDonald's has", "invaded us.");
                    speech("To defeat them", "...You");
                    speech("must get", "the magic milk");
                    speech("by killing", "the cow and");
                    speech("and then give", "it to me.");
                    speech("After that", "you must");
                    speech("kill the pig", "and give me");
                    speech("the bacon", "strip!");
                    Player.talked_to_npc = true;
                } else if (!Player.has_magic_milk) {
                    speech("You must defeat", "the cow and");
                    speech("bring me the", "magic milk");
                    speech("from this", "creature.");
                } else if (!Player.game_solved && !Player.talked_to_enterman2) {
                    speech("You've brought", "the magic milk.");
                    speech("Now, I can", "grant you ");
                    speech("the power", "needed to");
                    speech("vanquish the", "creeper. You");
                    speech("can use the", "special attack");
                    speech("button", "!");
                    Player.talked_to_enterman2 = true;
                } else if (!Player.game_solved && Player.talked_to_enterman2) {
                    speech("Go to cave", "and face ");
                    speech("the", "CREEPER!");
                } else if (!Player.bacon_strip) {
                    speech("Thank you for", "defeating the");
                    speech("CREEPER!!!", "");
                    speech("Go kill", "the pig!");
                    speech("Then", "our realm ");
                    speech("could be", "safe again!");
                } else if (!Player.has_key) {
                    speech("Thank you for", "defeating the");
                    speech("creeper", "and the pig!");
                    speech("With the", "bacon and milk");
                    speech("I will make", "the key...");
                    speech("AKWARD", "SILENCE...");
                    speech("CHING...", "take this key");
                    speech("It unlocks", "the special");
                    speech("door to", "your right!");
                    Player.has_key = true;
                } else {
                    speech("Go to your", "right to ");
                    speech("claim your", "ultimate");
                    speech("reward and", "restore peace.");
                }
                return FULL_DRAW;

            }


            // 2. Check if near a door
            //    - if the player has the key, you win the game
            //    - if not, show speech bubbles that the play needs to get the key 
            //     -return FULL_DRAW to redraw the scene

             if (south->type == DOOR || west->type == DOOR
                || north->type == DOOR || east->type == DOOR) {
                    if (Player.has_key) {
                        map_erase(33, 10);
                        map_erase(34, 10);
                        map_erase(35, 10);
                        map_erase(36, 10);  
                    } else {
                        speech("You need key", "to enter.");
                    }
                    return FULL_DRAW;
                }
            


            // 3. Check if on Pete's cave
            //    - if the player has talked to the npc, then start the speech bubble to fight buzz
            //    - set the players coordinates for the small map
            //    - and set the map to the small map
            //     -return FULL_DRAW to redraw the scene

            if (south->type == CAVE || west->type == CAVE
                || north->type == CAVE || east->type == CAVE) {
                    if (!Player.talked_to_npc) {
                        speech("You must","talk to Enterman");
                        return FULL_DRAW;
                    } else if (!Player.has_magic_milk) {
                        speech("You must first","get magic milk");
                        speech("from the crazy cow","crazy cow");
                        return FULL_DRAW;
                    }
                    Player.x = 1;
                    Player.y = 1;
                    set_active_map(1);
                    return FULL_DRAW;
            }


            // 4. Check if on a stairs
            //    - if so, move the player the correct coordinates
            //    - and set the map back to the main big map
            //     -return FULL_DRAW to redraw the scene

            if (south->type == STAIRS || west->type == STAIRS
                || north->type == STAIRS || east->type == STAIRS) {
                    Player.x = 5;
                    Player.y = 20;
                    set_active_map(0);
                    return FULL_DRAW;
            }


            // Feel free to add more functions as you make the game!

    
            break;
        
        case ATTACK_BUTTON:

            //******************
            // TODO: Implement
            //******************

            // 1. Check if near enemy, 
            //     - if so, mark enemy as defeated
            //      use speech bubbled to show what item was dropped
            //      update the player struct as needed
            //      if enemy is Pete, make sure that the right attack is being used
            //      If pete is defeated, update game as nescessary
            if (Player.xp < 10) {
                Player.level = 0;
            } else if (Player.xp < 20){
                Player.level = 2;
            } else if (Player.xp < 30){
                Player.level = 3;
                if (!Player.talked_about_ultimate_attack) {
                speech("Special move","unlocked!");
                speech("Now you","can kill");
                speech("the PIG!!!","");
                Player.talked_about_ultimate_attack = true;
                }
            } else if (Player.xp < 40){
                Player.level = 4;
            } else if (Player.xp < 50){
                Player.level = 5;
            } else if (Player.xp < 60){
                Player.level = 6;
            }

            if (east->type == COW) {
                add_slain_enemy(Player.x + 1, Player.y);
                speech("You defeated","the cow!");
                speech("MAGIC MILK","ACQUIRED");
                Player.has_magic_milk = true;
                Player.xp += 10;
                return FULL_DRAW;
            } 
            else if (west->type == COW) {
                add_slain_enemy(Player.x - 1, Player.y);
                speech("MAGIC MILK","ACQUIRED");
                speech("You defeated","the cow!");
                Player.has_magic_milk = true;
                Player.xp += 10;
                return FULL_DRAW;
            }
            else if (north->type == COW) {
                add_slain_enemy(Player.x, Player.y - 1);
                speech("MAGIC MILK","ACQUIRED");
                speech("You defeated","the cow!");
                Player.has_magic_milk = true;
                Player.xp += 10;
                return FULL_DRAW;
            } 
            else if (south->type == COW) {
                add_slain_enemy(Player.x, Player.y + 1);
                speech("MAGIC MILK","ACQUIRED");
                speech("You defeated","the cow!");
                Player.has_magic_milk = true;
                Player.xp += 10;
                return FULL_DRAW;
            }

            if (east->type == PIG) {
                speech("The pig boss","is immune");
                speech("to this","attack!");
                return FULL_DRAW;
            } 
            else if (west->type == PIG) {
                speech("The pig boss","is immune");
                speech("to this","attack!");
                return FULL_DRAW;
            }
            else if (north->type == PIG) {
                speech("The pig boss","is immune");
                speech("to this","attack!");
                return FULL_DRAW;
            } 
            else if (south->type == PIG) {
                speech("The pig boss","is immune");
                speech("to this","attack!");
                return FULL_DRAW;
            }
            if (east->type == CREEPER) {
                speech("The creeper boss","is immune");
                speech("to this","attack!");
                Player.xp += 10;
                return FULL_DRAW;
            } 
            else if (west->type == CREEPER) {
                speech("The creeper boss","is immune");
                speech("to this","attack!");
                Player.xp += 10;
                return FULL_DRAW;
            }
            else if (north->type == CREEPER) {
                speech("The creeper boss","is immune");
                speech("to this","attack!");
                Player.xp += 10;
                return FULL_DRAW;
            } 
            else if (south->type == CREEPER) {
                speech("The creeper boss","is immune");
                speech("to this","attack!");
                Player.xp += 10;
                return FULL_DRAW;
            }

            if (east->type == TNT) {
                speech("Powder","ACQUIRED");
                Player.powders++;
                Player.xp += 5;
                return FULL_DRAW;
            } 
            else if (west->type == TNT) {
                speech("Powder","ACQUIRED");
                Player.powders++;
                Player.xp += 5;
                return FULL_DRAW;
            }
            else if (north->type == TNT) {
                speech("Powder","ACQUIRED");
                Player.powders++;
                Player.xp += 5;
                return FULL_DRAW;
            } 
            else if (south->type == TNT) {
                speech("Powder","ACQUIRED");
                Player.xp += 5;
                Player.powders++;
                return FULL_DRAW;
            }

            if (east->type == CHICKEN) {
                add_slain_enemy(Player.x + 1, Player.y);
                speech("FEATHER","ACQUIRED");
                speech("You defeated","the chicken!");
                Player.feather = true; 
                Player.xp += 5;
                return FULL_DRAW;
            } 
            else if (west->type == CHICKEN) {
                add_slain_enemy(Player.x - 1, Player.y);
                speech("FEATHER","ACQUIRED");
                speech("You defeated","the chicken!");
                Player.feather = true;
                Player.xp += 5;
                return FULL_DRAW;
            }
            else if (north->type == CHICKEN) {
                add_slain_enemy(Player.x, Player.y - 1);
                speech("FEATHER","ACQUIRED");
                speech("You defeated","the chicken!");
                Player.feather = true;
                Player.xp += 5;
                return FULL_DRAW;
            } 
            else if (south->type == CHICKEN) {
                add_slain_enemy(Player.x, Player.y + 1);
                speech("FEATHER","ACQUIRED");
                speech("You defeated","the chicken!");
                Player.feather = true;
                Player.xp += 5;
                return FULL_DRAW;
            }
            break;


        //***********
        // Add more cases as needed
        //***********

        case SPECIAL_BUTTON:
            if (!Player.talked_to_enterman2) {
                speech("Haven't","unlocked");
                speech("this attack","yet!");
                return FULL_DRAW;
            }
            if (east->type == CREEPER) {
                add_slain_enemy(Player.x + 1, Player.y);
                speech("You defeated","the creeper!");
                speech("TNT","ACQUIRED");
                Player.has_tnt = true;
                Player.game_solved = true;
                return FULL_DRAW;
            } 
            else if (west->type == CREEPER) {
                add_slain_enemy(Player.x - 1, Player.y);
                speech("You defeated","the creeper!");
                speech("TNT","ACQUIRED");
                Player.has_tnt = true;
                Player.game_solved = true;
                return FULL_DRAW;
            }
            else if (north->type == CREEPER) {
                add_slain_enemy(Player.x, Player.y - 1);
                speech("You defeated","the creeper!");
                speech("TNT","ACQUIRED");
                Player.has_tnt = true;
                Player.game_solved = true;
                return FULL_DRAW;
            } 
            else if (south->type == CREEPER) {
                add_slain_enemy(Player.x, Player.y + 1);
                speech("You defeated","the creeper!");
                speech("TNT","ACQUIRED");
                Player.has_tnt = true;
                Player.game_solved = true;
                return FULL_DRAW;
            }

            if (east->type == PIG) {
                speech("The pig boss","is immune");
                speech("to this","attack!");
                return FULL_DRAW;
            } 
            else if (west->type == PIG) {
                speech("The pig boss","is immune");
                speech("to this","attack!");
                return FULL_DRAW;
            }
            else if (north->type == PIG) {
                speech("The pig boss","is immune");
                speech("to this","attack!");
                return FULL_DRAW;
            } 
            else if (south->type == PIG) {
                speech("The pig boss","is immune");
                speech("to this","attack!");
                return FULL_DRAW;
            }
            break;

        case SPECIAL_BUTTON_2:
            if (Player.level < 3) {
                speech("You haven't","unlocked");
                speech("this attack","yet!");
                speech("you need","to be");
                speech("at least","level 3!");
            } else {
                if (east->type == PIG) {
                    add_slain_enemy(Player.x + 1, Player.y);
                    speech("BACON STRIP","ACQUIRED");
                    speech("You defeated","the pig!");
                    Player.bacon_strip = true;
                    Player.xp += 10;
                    return FULL_DRAW;
                } 
                else if (west->type == PIG) {
                    add_slain_enemy(Player.x - 1, Player.y);
                    speech("BACON STRIP","ACQUIRED");
                    speech("You defeated","the pig!");
                    Player.bacon_strip = true;
                    Player.xp += 10;
                    return FULL_DRAW;
                }
                else if (north->type == PIG) {
                    add_slain_enemy(Player.x, Player.y - 1);
                    speech("BACON STRIP","ACQUIRED");
                    speech("You defeated","the pig!");
                    Player.bacon_strip = true;
                    Player.xp += 10;
                    return FULL_DRAW;
                } 
                else if (south->type == PIG) {
                    add_slain_enemy(Player.x, Player.y + 1);
                    speech("BACON STRIP","ACQUIRED");
                    speech("You defeated","the pig!");
                    Player.bacon_strip = true;
                    Player.xp += 10;
                    return FULL_DRAW;
                }
            }
            break;

        case MENU_BUTTON:
            menu = true;
            break;
    }
    
    
    return NO_RESULT;
}




/////////////////////////
// Draw Game
/////////////////////////

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int init)
{
    // Draw game border first
    if(init) draw_border();
    
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
//            if (init && i == 0 && j == 0) // Only draw the player on init
            if ( i == 0 && j == 0) // always draw the player
            {
              draw_player(u, v, Player.has_key, Player.jumping, Player.red);
              continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                }
                else if (curr_item && curr_item->type == CLEAR)
                {
                    // This is a special case for erasing things like doors.
                    draw = curr_item->draw; // i.e. draw_nothing
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars    
    draw_upper_status();
    draw_lower_status();
}







/////////////////////////
// Map Intialization
/////////////////////////

// Important locations for all maps
int cb_loc[2] = {5,20}; //Location of the center of the cave


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    //Initialize and sets current map to the first map
    Map* map = set_active_map(0);

    /////////////////////////
    //Initial Environmnet
    /////////////////////////

    for(int i = map_width() + 3; i < map_area(); i += 104)
    {
        add_sugar_cane(i % map_width(), i / map_width());
        add_sugar_cane((i % map_width()) + 1, i / map_width());
        add_sugar_cane(i % map_width(), (i / map_width()) + 1);
        add_sugar_cane((i % map_width()) + 1, (i / map_width()) + 1);
    }

    for(int i = map_width() + 3; i < map_area(); i += 76)
    {
        add_fire(i % map_width(), i / map_width());
    }

    //Adding random plants
    pc.printf("Adding Plants!\r\n");
    for(int i = map_width() + 3; i < map_area(); i += 39)
    {
        add_plant(i % map_width(), i / map_width());
    }

    //Adding wall borders 
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    
    //Adding extra chamber borders 
    pc.printf("Add extra chamber\r\n");
    add_wall(30, 0, VERTICAL, 10);
    add_wall(30, 10, HORIZONTAL, 10);
    add_wall(39, 0, VERTICAL, 10);
    add_door(33, 10, HORIZONTAL, 4);
    add_tnt(35, 8);

    //Adding extra cave to Buzz's evil lair
    pc.printf("Add cave\r\n");
    add_cave(cb_loc[0],cb_loc[1],1,1,5,5);      //Cave is set as a 4x4 block to be bigger
    add_cave(cb_loc[0]+1,cb_loc[1],2,1,5,5);
    add_cave(cb_loc[0],cb_loc[1]+1,3,1,5,5);
    add_cave(cb_loc[0]+1,cb_loc[1]+1,4,1,5,5);

    pc.printf("Initial environment completed\r\n");

    /////////////////////////////////
    // Characters and Items for the map
    /////////////////////////////////

    // Add NPC
    add_npc(12, 10);  //NPC is initialized to (x,y) = 10, 5. Feel free to move him around
    
    //***********************************
    // TODO: Implement As Needed
    //***********************************

    //Add any extra characters/items here for your project
    add_cow(14, 15);
    add_villager(22, 17);

    add_chicken(15, 20);

    //Prints out map
    print_map();
}







void init_small_map()
{
    //Sets current map to the second map
    set_active_map(1);


    //***********************************
    // TODO: Implement 
    //***********************************

    // 1. Add walls to the smaller map.
    //    Set the dimensions to be 16x16  <-- you may change to your liking, but must be smaller than the main map
    //    Hint: See how walls are initialized in the main map
    //
    // 2. Add a way to access your specail attacks either here or in update_game() or anywhere you feel would be the best
    //
    // 3. Add Boss in the map


    // You may add any extra characters/items here for your project


    // Add stairs back to main (map 0)
    add_stairs(4, 6, 0, cb_loc[0], cb_loc[1]);

    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    
    add_tnt(2, 2);
    add_tnt(3, 2);
    add_tnt(8, 7);
    add_tnt(3, 7);
    add_tnt(12, 13);
    add_tnt(4, 8);

    add_creeper(10, 10);
    add_pig(5, 13);
    add_fire(4, 13);
    add_fire(6, 13);
    add_fire(5, 12);
    
}


/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");


    //uLCD.filled_rectangle(64, 64, 74, 74, RED); //DELETE OR COMMENT THIS LINE  <-- It is a temporary indicator that your LCD is working before you implement your code


    // Initialize the maps
    maps_init();
    init_main_map();
    init_small_map();
    menu = false;
    
    // Initialize game state
    set_active_map(0);
    Player.x = Player.y = 6;
    Player.has_key = false;
    Player.game_solved = false;
    Player.talked_to_npc = false;
    Player.talked_to_enterman2 = false;
    Player.has_magic_milk = false;
    Player.has_tnt = false;
    Player.lives = 3;
    Player.jumping = false;
    Player.talked_to_villager = 0;
    Player.xp = 0;
    Player.level = 0;
    Player.talked_about_ultimate_attack = false;
    int chicken_count = 0;
    Player.red = false;
    menu = false;

    // Draw start page
    draw_start_page();


    // Initial drawing
    draw_game(true);

    Timer e; e.start();
    Timer c; c.start();

    // Main game loop
    while(1)
    {

        ////////////////////////////////
        // TODO: Implement 
        ////////////////////////////////

        // Timer to measure game update speed
        Timer t; t.start();
        
        // Actually do the game update:
        // 1. Read inputs        

        // 2. Determine action (get_action)       

        // 3. Update game (update_game)
        char coords[24];
        sprintf(coords, "x:%d y:%d XP:%d-",Player.x, Player.y, Player.xp);
        uLCD.locate(0, 0);
        uLCD.puts(coords);
        bool full_draw = false;

        
        int result = update_game(get_action(read_inputs()));  // Set this variable "result" for the resulting state after update game

        // 3b. Check for game over based on update game result
        if (result == GAME_OVER) {
            uLCD.filled_rectangle(0, 0, 127, 127, 0x000080);
            uLCD.locate(5, 7);
            uLCD.set_font_size(5, 5);
            uLCD.puts("Game Over!");
            while(1) {
            }
        }
        if (Player.lives <= 0) {
            uLCD.filled_rectangle(0, 0, 127, 127, 0x000080);
            uLCD.locate(5, 7);
            uLCD.set_font_size(5, 5);
            uLCD.puts("Game Over!");
            

            uLCD.locate(5, 40);
            uLCD.set_font_size(3, 3);
            uLCD.puts("No lives remaining!");
            
            while(1) {
            }
        }
        if (menu) {
            draw_border();

            // Cover map
            uLCD.filled_rectangle(3, 15, 126, 113, BLACK);

            // Write message
            
            char time[15];
            int timeNow = e.read();
            uLCD.text_string("MENU PAGE" , 1, 2, FONT_12X16, BLUE);
            sprintf(time, "Time: %d seconds", timeNow);
            uLCD.text_string(time , 1, 2, FONT_12X16, BLUE);
            if (Player.has_magic_milk) {
                uLCD.text_string("COW: Dead", 1, 4, FONT_5X7, GREEN);
            } else {
                uLCD.text_string("COW: Alive", 1, 4, FONT_5X7, GREEN);
            }
            if (Player.has_tnt) {
                uLCD.text_string("CREEPER: Dead", 1, 5, FONT_5X7, GREEN);
            } else {
                uLCD.text_string("CREEPER: Alive", 1, 5, FONT_5X7, GREEN);
            }
            if (Player.bacon_strip) {
                uLCD.text_string("PIG: Dead", 1, 6, FONT_5X7, GREEN);
            } else {
                uLCD.text_string("PIG: Alive", 1, 6, FONT_5X7, GREEN);
            }
            if (Player.feather) {
                uLCD.text_string("Chicken: Dead", 1, 7, FONT_5X7, GREEN);
            } else {
                uLCD.text_string("Chicken: Alive", 1, 7, FONT_5X7, GREEN);
            }

            GameInputs in;
            in = read_inputs();

            while(!in.b1) {
                Timer t; t.start();

                in = read_inputs();

                t.stop();
                int dt = t.read_ms();
                if (dt < 100) wait_ms(100 - dt);
            }
            menu = false;
            full_draw = true;
        }

        // if (c.read() > 3) {
        //     add_chicken(16, 20);
        //     //map_erase(16, 20);
        //     add_chicken(15, 20);
        //     //c.reset();
        //     full_draw = true;

        // } else if (c.read() > 2) {
        //     add_chicken(16, 20);
        //     map_erase(16, 20);
        //     add_chicken(15, 20);
        //     //c.reset();
        //     full_draw = true;

        // } else if (c.read() > 1) {
            
        //     try {
        //         map_erase(15, 20);
        //     }
        //     add_chicken(16, 20);
        //     full_draw = true;

        // }
        

        // 4. Draw screen to uLCD
        
        if (result == FULL_DRAW) full_draw = true;
        draw_game(full_draw);
        
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
    

}




/////////////////////////////
//Advanced Features
/////////////////////////////

LocalFileSystem local ("local");

// Plays a wavfile
void playSound(char* wav)
{
    //open wav file
    FILE *wave_file;
    wave_file=fopen(wav,"r");
    
    if(wave_file != NULL) 
    {
        printf("File opened successfully\n");

        //play wav file
        printf("Sound playing...\n");
        waver.play(wave_file);
    
        //close wav file
        printf("Sound stopped...\n");
        fclose(wave_file);
        return;
    }
    
    printf("Could not open file for reading - %s\n", wav);
    return;
}
