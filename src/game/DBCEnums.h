/*
 * This file is part of the BlizzLikeCore Project.
 * See CREDITS and LICENSE files for Copyright information.
 */

#ifndef DBCENUMS_H
#define DBCENUMS_H

// Client expected level limitation, like as used in DBC item max levels for "until max player level"
// use as default max player level, must be fit max level for used client
// also see MAX_LEVEL and STRONG_MAX_LEVEL define
#define DEFAULT_MAX_LEVEL 70

// client supported max level for player/pets/etc. Avoid overflow or client stability affected.
// also see GT_MAX_LEVEL define
#define MAX_LEVEL    100

// Server side limitation. Base at used code requirements.
// also see MAX_LEVEL and GT_MAX_LEVEL define
#define STRONG_MAX_LEVEL 255

enum AreaTeams
{
    AREATEAM_NONE  = 0,
    AREATEAM_ALLY  = 2,
    AREATEAM_HORDE = 4
};

enum AreaFlags
{
    AREA_FLAG_SNOW             = 0x00000001,                // snow (only Dun Morogh, Naxxramas, Razorfen Downs and Winterspring)
    AREA_FLAG_UNK1             = 0x00000002,                // may be necropolis?
    AREA_FLAG_UNK2             = 0x00000004,                // Only used for areas on map 571 (development before)
    AREA_FLAG_SLAVE_CAPITAL    = 0x00000008,                // city and city subsones
    AREA_FLAG_UNK3             = 0x00000010,                // can't find common meaning
    AREA_FLAG_SLAVE_CAPITAL2   = 0x00000020,                // slave capital city flag?
    AREA_FLAG_UNK4             = 0x00000040,                // many zones have this flag
    AREA_FLAG_ARENA            = 0x00000080,                // arena, both instanced and world arenas
    AREA_FLAG_CAPITAL          = 0x00000100,                // main capital city flag
    AREA_FLAG_CITY             = 0x00000200,                // only for one zone named "City" (where it located?)
    AREA_FLAG_OUTLAND          = 0x00000400,                // expansion zones? (only Eye of the Storm not have this flag, but have 0x00004000 flag)
    AREA_FLAG_SANCTUARY        = 0x00000800,                // sanctuary area (PvP disabled)
    AREA_FLAG_NEED_FLY         = 0x00001000,                // only Netherwing Ledge, Socrethar's Seat, Tempest Keep, The Arcatraz, The Botanica, The Mechanar, Sorrow Wing Point, Dragonspine Ridge, Netherwing Mines, Dragonmaw Base Camp, Dragonmaw Skyway
    AREA_FLAG_UNUSED1          = 0x00002000,                // not used now (no area/zones with this flag set in 3.0.3)
    AREA_FLAG_OUTLAND2         = 0x00004000,                // expansion zones? (only Circle of Blood Arena not have this flag, but have 0x00000400 flag)
    AREA_FLAG_PVP              = 0x00008000,                // pvp objective area? (Death's Door also has this flag although it's no pvp object area)
    AREA_FLAG_ARENA_INSTANCE   = 0x00010000,                // used by instanced arenas only
    AREA_FLAG_UNUSED2          = 0x00020000,                // not used now (no area/zones with this flag set in 3.0.3)
    AREA_FLAG_UNK5             = 0x00040000,                // only used for Amani Pass, Hatchet Hills
    AREA_FLAG_LOWLEVEL         = 0x00100000,                // used for some starting areas with area_level <= 15
    AREA_FLAG_INSIDE           = 0x02000000,                // used for determinating spell related inside/outside questions in Map::IsOutdoors
    AREA_FLAG_OUTSIDE          = 0x04000000,                // used for determinating spell related inside/outside questions in Map::IsOutdoors
};

enum FactionTemplateFlags
{
    FACTION_TEMPLATE_FLAG_CONTESTED_GUARD   =   0x00001000, // faction will attack players that were involved in PvP combats
};

enum FactionMasks
{
    FACTION_MASK_PLAYER   = 1,                              // any player
    FACTION_MASK_ALLIANCE = 2,                              // player or creature from alliance team
    FACTION_MASK_HORDE    = 4,                              // player or creature from horde team
    FACTION_MASK_MONSTER  = 8                               // aggressive creature from monster team
    // if none flags set then non-aggressive creature
};

enum MapTypes
{
    MAP_COMMON          = 0,
    MAP_INSTANCE        = 1,
    MAP_RAID            = 2,
    MAP_BATTLEGROUND    = 3,
    MAP_ARENA           = 4
};

enum AbilytyLearnType
{
    ABILITY_LEARNED_ON_GET_PROFESSION_SKILL     = 1,
    ABILITY_LEARNED_ON_GET_RACE_OR_CLASS_SKILL  = 2
};

enum ItemEnchantmentType
{
    ITEM_ENCHANTMENT_TYPE_NONE         = 0,
    ITEM_ENCHANTMENT_TYPE_COMBAT_SPELL = 1,
    ITEM_ENCHANTMENT_TYPE_DAMAGE       = 2,
    ITEM_ENCHANTMENT_TYPE_EQUIP_SPELL  = 3,
    ITEM_ENCHANTMENT_TYPE_RESISTANCE   = 4,
    ITEM_ENCHANTMENT_TYPE_STAT         = 5,
    ITEM_ENCHANTMENT_TYPE_TOTEM        = 6
};

enum ItemEnchantmentAuraId
{
    ITEM_ENCHANTMENT_AURAID_POISON     = 26,
    ITEM_ENCHANTMENT_AURAID_NORMAL     = 28,
    ITEM_ENCHANTMENT_AURAID_FIRE       = 32,
    ITEM_ENCHANTMENT_AURAID_FROST      = 33,
    ITEM_ENCHANTMENT_AURAID_NATURE     = 81,
    ITEM_ENCHANTMENT_AURAID_SHADOW     = 107
};

enum TotemCategoryType
{
    TOTEM_CATEGORY_TYPE_KNIFE   = 1,
    TOTEM_CATEGORY_TYPE_TOTEM   = 2,
    TOTEM_CATEGORY_TYPE_ROD     = 3,
    TOTEM_CATEGORY_TYPE_PICK    = 21,
    TOTEM_CATEGORY_TYPE_STONE   = 22,
    TOTEM_CATEGORY_TYPE_HAMMER  = 23,
    TOTEM_CATEGORY_TYPE_SPANNER = 24
};

#endif

