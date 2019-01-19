#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#define RAD2DEG 57.2958f
#define DEG2RAD 0.0174533f

enum eBehavior {
	B_Idle       = 1,
	B_EnemyClose = 2,
	B_Attack     = 3,
	B_Pursue     = 4,
	B_GoTo       = 5,
	B_EntityDead = 6
};

const int MAX_VIEWPORT_WIDTH_HALF  = 512;
const int MAX_VIEWPORT_HEIGHT_HALF = 384;

constexpr const char* ROOT_NODE_NAME     = "root";
constexpr const char* BEHAVIOR_NODE_NAME = "behavior";
constexpr const char* SELECTOR_NODE_NAME = "selector";
constexpr const char* SEQUENCE_NODE_NAME = "sequence";

constexpr const char* ID_ATTR            = "id";
constexpr const char* NAME_ATTR          = "name";
constexpr const char* IMAGE_INDEX_ATTR   = "image_index";
constexpr const char* RADIUS_ATTR        = "radius";
constexpr const char* REVERSE_ATTR       = "reverse";
constexpr const char* SPEED_ATTR         = "speed";
constexpr const char* MIN_DISTANCE_ATTR  = "min_distance";
constexpr const char* DAMAGE_POINTS_ATTR = "damage_points";

#endif