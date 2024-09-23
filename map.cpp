//=================================================================
// The map class file.
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================

#include "map.h"
#include "globals.h"
#include "graphics.h"
#include "hash_table.h"

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items; // Hashtables for all items of the map
    int w, h;         // Map dimensions
    int index;        // Index of map (tells if its the first map or second map)
};

///////////////////////
//Important Definitions
///////////////////////

#define MHF_NBUCKETS 97     //  Hashing value
#define NUM_MAPS 2          //  You may add more maps here
static Map maps[NUM_MAPS];  //  Array of maps
static int active_map;      //  Current active map on screen


//To erase a MapItem, we can simply replace it 
//with a clear type item called clear sentinel
static const MapItem CLEAR_SENTINEL = { 
    .type = CLEAR,
    .draw = draw_nothing
};


/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y) {

    //****************
    // TODO: Implement
    //****************

    // 1. Return the 1-D XY key
    unsigned map = Y * map_width() + X;
    return map;

}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    //****************
    // TODO: Implement
    //****************

    // Hint: what math operator can be used as an easy way to hash a key?
    // 1. Use MHF_NBUCKETS defined at the top as the value to hash for your hash function
    // 2. Return the hashed key

    return key % MHF_NBUCKETS;
}

/**
 * Initializes the map, using a hash_table, setting the width and height.
 */
void maps_init()
{
    //****************
    // TODO: Implement
    //****************

    // 1. Loop through all possible maps, where for each map's items, create a hashtable 
    // 2. Set width & height for any maps 
    // 3. Set the first map to be active

    for (int i = 0; i < NUM_MAPS; i++) {
        
        maps[i].items = createHashTable(map_hash, MHF_NBUCKETS);
    }
    maps[0].w = 55;
    maps[0].h = 55;
    maps[1].w = 15;
    maps[1].h = 15;
    active_map = 0;
}


Map* get_active_map()
{
    //****************
    // TODO: Implement
    //****************

    // 1. Return a pointer to the current map based on which map is active (active_map)
    //    Hint: What operator do we use for returning addresses?
    //    Note: active_map is set as a Global Variable 
    return &maps[active_map];

}

int get_active_map_index()
{
    //****************
    // TODO: Implement
    //****************
    
    // 1. Return the index to the current map based on which map is active (active_map)
    return active_map;
}

Map* set_active_map(int m)
{
    //****************
    // TODO: Implement
    //****************

    // 1. Set the Global Variable for active map to the map index passed in
    // 2. Return a pointer to the current map based on which map is active (active_map)
 
    active_map = m;
    return &maps[active_map];
   
}

/**
 *  Prints out the map for debugging on the terminal
 */

void print_map()
{
    // NOTE: As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'D', 'P', 'A', 'K', 'C', 'N',' ','S'};
    Map* map = get_active_map();
    for(int j = 0; j < map->h; j++)
    {
        for (int i = 0; i < map->w; i++)
        {
            MapItem* item = (MapItem*)getItem(map->items, XY_KEY(i, j));
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}


/**
 * Returns width of active map
 */
int map_width()
{
    //****************
    // TODO: Implement 
    //****************
    // Hint 1 for this and below functions: use another function to GET the current active map
    // Hint 2: check the struct of a map item
    return get_active_map()->w;
}

/**
 * Returns height of active map
 */
int map_height()
{
    //****************
    // TODO: Implement  
    //****************
    return get_active_map()->h;
}

/**
 * Returns the area of the active map
 */
int map_area()
{
    //****************
    // TODO: Implement  
    //****************
    // HINT: You have the width and height to compute area
    return get_active_map()->w * get_active_map()->h;
}

/**
 * Returns the MapItem immediately above the given location.
 */
MapItem* get_north(int x, int y)
{
//CHECK___________________________________________________________________________________________
    //****************
    // TODO: Implement
    //****************
    // 1. Get map item 
    // 2. If the item exist and is a clear type, remove item
    // 3. Return the item 
    MapItem * item = (MapItem *) getItem(get_active_map()->items, XY_KEY(x,y - 1));
    if (item != NULL && item->type == CLEAR_SENTINEL.type) {
        removeItem(get_active_map()->items, XY_KEY(x,y - 1));
    }
    return item;
}

/**
 * Returns the MapItem immediately below the given location.
 */
MapItem* get_south(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    // 1. Get map item 
    // 2. If the item exist and is a clear type, remove item
    // 3. Return the item 
    MapItem * item = (MapItem *) getItem(get_active_map()->items, XY_KEY(x,y + 1));
    if (item != NULL && item->type == CLEAR_SENTINEL.type) {
        removeItem(get_active_map()->items, XY_KEY(x,y + 1));
    }
    return item;
}

/**
 * Returns the MapItem immediately right the given location.
 */
MapItem* get_east(int x, int y)
{

    // TODO: Implement
    //**
    // 1. Get map item 
    // 2. If the item exist and is a clear type, remove item
    // 3. Return the item 
    MapItem * item = (MapItem *) getItem(get_active_map()->items, XY_KEY(x + 1,y));
    if (item != NULL && item->type == CLEAR_SENTINEL.type) {
        removeItem(get_active_map()->items, XY_KEY(x + 1,y));
    }
    return item;
}

/**
 * Returns the MapItem immediately left the given location.
 */
MapItem* get_west(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    // 1. Get map item 
    // 2. If the item exist and is a clear type, remove item
    // 3. Return the item 
    MapItem * item = (MapItem *) getItem(get_active_map()->items, XY_KEY(x - 1,y));
    if (item != NULL && item->type == CLEAR_SENTINEL.type) {
        removeItem(get_active_map()->items, XY_KEY(x - 1,y));
    }
    return item;
}

/**
 * Returns the MapItem at current coordinate location
 */
 MapItem* get_here(int x, int y)
 {
    //****************
    // TODO: Implement
    //****************
    // 1. Get map item 
    // 2. If the item exist and is a clear type, remove item
    // 3. Return the item 
    if(x > -1 && x < get_active_map()->w && y > -1 && y < get_active_map()->h)
        return (MapItem*) getItem(get_active_map()->items, XY_KEY(x, y));
    else
        return NULL;
 }

 

/**
 * Erases item on a location by replacing it with a clear sentinel
 */
void map_erase(int x, int y)
{
    MapItem* item = (MapItem*)insertItem(get_active_map()->items, XY_KEY(x, y), (void*)&CLEAR_SENTINEL);
    if(item) free(item);
}


////////////////////////////////////
// Adding specific items to the map
////////////////////////////////////


void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_npc(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    // 1. Implement the same way as how we add plant
    //     *Make the NPC NOT walkable
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = NPC;
    w1->draw = draw_npc;
    w1->walkable = false;
    w1->data = NULL;
    pc.printf("NPC created with data %u\r\n", *((int*)w1->data));
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it

}


void add_water(int x, int y)
{

   //****************
    // TODO: Implement
    //****************
    // 1. Implement the same way as how we add plant
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = WATER;
    w1->draw = draw_water;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val);  // If something is already there, free it

}

void add_fire(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    // 1. Implement the same way as how we add plant
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = FIRE;
    w1->draw = draw_fire;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val);  // If something is already there, free it

}

void add_earth(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    // 1. Implement the same way as how we add plant
        MapItem* w1 = (MapItem*)malloc(sizeof(MapItem));
    w1->type = EARTH;
    w1->draw = draw_earth;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val);  // If something is already there, free it

}


void add_slain_enemy(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    // 1. Implement the same way as how we add plant
    // Note: This function is to ovewrite enemy when it is defeated
    //      You can do the following:
    //      -   Overwrite enemy with any other item (say plant, mud)
    //      -   Make a new drawing for a defeated enemy
    //      -   Erase enemy instead 
    add_fire(x, y);
}



////////////////////////////////////
// Adding environment to the map
////////////////////////////////////


void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_door(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = DOOR;
        w1->draw = draw_door;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}


void add_stairs(int x, int y, int tm, int tx, int ty)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = STAIRS;
    w1->draw = draw_stairs;
    w1->walkable = true;
    StairsData* data = (StairsData*) malloc(sizeof(StairsData));
    data->tm = tm;
    data->tx = tx;
    data->ty = ty;
    w1->data = data;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it    
}


void add_cave(int x, int y, int n, int tm, int tx, int ty)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = CAVE;
    if (n==1){
        w1->draw = draw_cave1;
    }
    if (n==2){
        w1->draw = draw_cave2;
    }
    if (n==3){
        w1->draw = draw_cave3;
    }
    if (n==4){
        w1->draw = draw_cave4;
    }
    w1->walkable = true;
    StairsData* data = (StairsData*) malloc(sizeof(StairsData));
    data->tm = tm;
    data->tx = tx;
    data->ty = ty;
    w1->data = data;
    
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it    
}


void add_mud(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = MUD;
        w1->draw = draw_mud;
        w1->walkable = true;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_cow(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = COW;
    w1->draw = draw_cow;
    w1->walkable = false;
    w1->data = NULL;
    pc.printf("COW created with data %u\r\n", *((int*)w1->data));
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it

}

void add_pig(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PIG;
    w1->draw = draw_pig;
    w1->walkable = false;
    w1->data = NULL;
    pc.printf("COW created with data %u\r\n", *((int*)w1->data));
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it

}

void add_creeper(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = CREEPER;
    w1->draw = draw_creeper;
    w1->walkable = false;
    w1->data = NULL;
    pc.printf("COW created with data %u\r\n", *((int*)w1->data));
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it

}

void add_tnt(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = TNT;
    w1->draw = draw_tnt;
    w1->walkable = false;
    w1->data = NULL;
    pc.printf("COW created with data %u\r\n", *((int*)w1->data));
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it

}

void add_sugar_cane(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SUGAR;
    w1->draw = draw_sugar;
    w1->walkable = false;
    w1->data = NULL;
    pc.printf("COW created with data %u\r\n", *((int*)w1->data));
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it 
}

void add_chicken(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = CHICKEN;
    w1->draw = draw_chicken;
    w1->walkable = false;
    w1->data = NULL;
    pc.printf("COW created with data %u\r\n", *((int*)w1->data));
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it 
}

void add_villager(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = VILLAGER;
    w1->draw = draw_villager;
    w1->walkable = false;
    w1->data = NULL;
    pc.printf("COW created with data %u\r\n", *((int*)w1->data));
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it 
}
