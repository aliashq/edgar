#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define MAX_MAP_X 1200
#define MAX_MAP_Y 600

#define TILE_SIZE 32

#define PI 3.14159265

#define GRAVITY_SPEED 0.75

#define MAX_AIR_SPEED 15

#define MAX_WATER_SPEED 0.5

#define JUMP_HEIGHT 11

#define TRANS_R 127
#define TRANS_G 0
#define TRANS_B 127

#define MAX_ANIMATIONS 255

#define MAX_ENTITIES 512

#define BLANK_TILE 0

#define SOLID_TILE_START 1

#define SOLID_TILE_END 99

#define SLOPE_UP_START 100

#define SLOPE_UP_END 104

#define SLOPE_DOWN_START 105

#define SLOPE_DOWN_END 109

#define JUMP_THROUGH_TILE_START 110

#define JUMP_THROUGH_TILE_END 119

#define BACKGROUND_TILE_START 120

#define BACKGROUND_TILE_END 150

#define FOREGROUND_TILE_START 151

#define WATER_TILE_START 200

#define WATER_TILE_END 205

#define MAX_TILES 255

#define MAX_LINE_LENGTH 1024

#define MAX_PATH_LENGTH 1024

#define PI 3.14159265

#define MAX_MESSAGE_LENGTH 256

#define MAX_INVENTORY_ITEMS 24

#define MAX_DROPS 240

#define MAX_SPRITES 4096

#define MAX_PROPS_ENTRIES 20

#define MAX_PROPS_FILES 30

#define MAX_CUSTOM_ACTIONS 4

#define MAX_AMBIENT_SOUNDS 10

#define MAX_DECORATIONS 100

#define MAX_TARGETS 60

#define MAX_HUD_MESSAGES 5

#define MAX_VALUE_LENGTH 60

#define MAX_TRIGGERS 10

#define MAX_OBJECTIVES 5

#define MAX_INPUTS 256

#define MAX_ITEMS_IN_SLOT 10

#ifdef WIN32
	#define strcmpignorecase(x, y) stricmp(x, y)
#else
	#define strcmpignorecase(x, y) strcasecmp(x, y)
#endif

#if DEV < 1

#else
	#ifdef INSTALL_PATH
		#undef INSTALL_PATH
	#endif

	#define INSTALL_PATH ""
#endif

#define MAX_SOUNDS 256

#define ITEM_JUMP_HEIGHT -6

enum
{
	LEFT,
	RIGHT
};

enum
{
	FALSE,
	TRUE
};

enum
{
	ON_GROUND = 1,
	NO_DRAW = 2,
	PUSHABLE = 4,
	HELPLESS = 8,
	INVULNERABLE = 16,
	FLY = 32,
	ATTACKING = 64,
	BLOCKING = 128,
	ALWAYS_ON_TOP = 256,
	GRABBING = 512,
	ATTACK_SUCCESS = 1024,
	STACKABLE = 2048,
	OBSTACLE = 4096,
	FLOATS = 8192,
	FLASH = 16384
};

enum
{
	PLAYER,
	WEAPON,
	ITEM,
	KEY_ITEM,
	ENEMY,
	HEALTH,
	SHIELD,
	AUTO_LIFT,
	MANUAL_LIFT,
	TARGET,
	SPAWNER,
	PRESSURE_PLATE,
	MANUAL_DOOR,
	AUTO_DOOR,
	WEAK_WALL,
	SWITCH,
	LINE_DEF,
	LEVEL_EXIT,
	PROJECTILE,
	SAVE_POINT
};

enum
{
	TILES,
	ENTITIES
};

enum
{
	STAND,
	WALK,
	JUMP,
	PAIN,
	DIE,
	ATTACK_1,
	ATTACK_2,
	ATTACK_3,
	ATTACK_4,
	ATTACK_5,
	MAX_ANIMATION_TYPES
};

enum
{
	NO_WEATHER,
	LIGHT_RAIN,
	HEAVY_RAIN,
	STORMY,
	SNOW,
	MAX_WEATHER_TYPES
};

enum
{
	EDGAR_CHANNEL,
	AMBIENCE_CHANNEL,
	ENEMY_CHANNEL_1,
	ENEMY_CHANNEL_2,
	BOSS_CHANNEL,
	LIFT_CHANNEL,
	OBJECT_CHANNEL_1,
	OBJECT_CHANNEL_2
};

enum
{
	LIGHT = 1,
	MEDIUM,
	STRONG
};

enum
{
	UPDATE_OBJECTIVE = 1,
	ACTIVATE_ENTITY,
	UPDATE_BOTH
};

enum
{
	NORMAL,
	RECORDING,
	REPLAYING
};

enum
{
	STANDARD_MESSAGE,
	GOOD_MESSAGE,
	BAD_MESSAGE
};

enum
{
	WIPE_OUT_LEFT_TO_RIGHT,
	WIPE_OUT_RIGHT_TO_LEFT,
	WIPE_OUT_CIRCLE_TO_LARGE,
	WIPE_OUT_CIRCLE_TO_SMALL,
	MAX_OUT_TRANSITIONS
};

enum
{
	WIPE_IN_LEFT_TO_RIGHT,
	WIPE_IN_RIGHT_TO_LEFT,
	WIPE_IN_CIRCLE_TO_LARGE,
	WIPE_IN_CIRCLE_TO_SMALL,
	MAX_IN_TRANSITIONS
};

enum
{
	TRANSITION_IN,
	TRANSITION_OUT
};

enum
{
	AIR,
	WATER
};
