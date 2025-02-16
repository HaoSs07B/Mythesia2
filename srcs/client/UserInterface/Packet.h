#pragma once

#include "Locale.h"
#include "../gamelib/RaceData.h"
#include "../gamelib/ItemData.h"

#if defined(ENABLE_ULTIMATE_REGEN)
typedef struct SNewRegen {
	long x, y;
	uint8_t day, hour, minute, second;
	long safeRange;
	uint32_t mob_vnum;
	uint8_t hours_range;
	uint8_t minute_range;
	int32_t leftTime;
} TNewRegen;
#endif

typedef BYTE TPacketHeader;

enum
{
	HEADER_CG_LOGIN = 0x20,
	HEADER_CG_ATTACK = 49,
	HEADER_CG_CHAT = 3,
	HEADER_CG_PLAYER_CREATE = 0x19,
	HEADER_CG_PLAYER_DESTROY					= 5,
	HEADER_CG_PLAYER_SELECT						= 6,
	HEADER_CG_CHARACTER_MOVE					= 7,
	HEADER_CG_SYNC_POSITION  					= 8,
	HEADER_CG_DIRECT_ENTER						= 9,
	HEADER_CG_ENTERGAME							= 10,
	HEADER_CG_ITEM_USE							= 11,
	HEADER_CG_ITEM_DROP							= 12,
	HEADER_CG_ITEM_MOVE							= 13,
	HEADER_CG_ITEM_PICKUP						= 15,
	HEADER_CG_QUICKSLOT_ADD = 16,
	HEADER_CG_QUICKSLOT_DEL = 17,
	HEADER_CG_QUICKSLOT_SWAP = 18,
	HEADER_CG_WHISPER							= 19,
	HEADER_CG_ITEM_DROP2                        = 20,
	HEADER_CG_ITEM_DESTROY = 21,
	HEADER_CG_ITEM_DIVISION = 22,
	HEADER_CG_REQ_MAP_BOSS_INFO = 23,
#if defined(ENABLE_INGAME_CHCHANGE)
	HEADER_CG_CHANGE_CHANNEL = 24,
#endif

	HEADER_CG_ON_CLICK							= 26,
	HEADER_CG_EXCHANGE							= 27,
    HEADER_CG_CHARACTER_POSITION                = 28,
    HEADER_CG_SCRIPT_ANSWER						= 29,
	HEADER_CG_QUEST_INPUT_STRING				= 30,
    HEADER_CG_QUEST_CONFIRM                     = 31,
	//HEADER_BLANK35								= 35,
	//HEADER_BLANK36								= 36,
	//HEADER_BLANK37								= 37,
	//HEADER_BLANK38								= 38,
	//HEADER_BLANK39								= 39,
	//HEADER_BLANK40								= 40,
	//HEADER_BLANK42								= 42,
	//HEADER_BLANK43								= 43,
	//HEADER_BLANK44								= 44,
	//HEADER_BLANK45								= 45,
	//HEADER_BLANK47								= 47,
	//HEADER_BLANK48								= 48,
	//HEADER_BLANK49								= 49,
	HEADER_CG_LOGIN3 = 33,
	HEADER_CG_USE_SKILL = 42,
#if defined(USE_BATTLEPASS)
	HEADER_CG_EXT_BATTLE_PASS_ACTION = 43,
	HEADER_CG_EXT_SEND_BP_PREMIUM_ITEM = 44,
#endif
#ifdef USE_CAPTCHA_SYSTEM
    HEADER_CG_CAPTCHA                          = 47,
#endif
#if defined(USE_ATTR_6TH_7TH)
	HEADER_CG_ATTR67_ADD = 48,
#endif
	HEADER_CG_SHOP								= 50,
	HEADER_CG_FLY_TARGETING						= 51,
	HEADER_CG_ADD_FLY_TARGETING                 = 53,
	HEADER_CG_SHOOT								= 54,
	HEADER_CG_MYSHOP                            = 55,
#ifdef ENABLE_OPENSHOP_PACKET
	HEADER_CG_OPENSHOP = 57,
#endif
#if defined(ENABLE_GAYA_RENEWAL)
	HEADER_CG_GEM_SHOP = 58,
#endif

	//HEADER_BLANK56								= 56,
	//HEADER_BLANK59								= 59,
	HEADER_CG_ITEM_USE_TO_ITEM					= 60,
    HEADER_CG_TARGET                            = 61,
	//HEADER_BLANK62								= 62,
	//HEADER_BLANK63								= 63,
	//HEADER_BLANK64								= 64,
	HEADER_CG_WARP								= 65,
    HEADER_CG_SCRIPT_BUTTON						= 66,
    HEADER_CG_MESSENGER                         = 67,
	//HEADER_BLANK68								= 68,
    HEADER_CG_MALL_CHECKOUT                     = 69,
    HEADER_CG_SAFEBOX_CHECKIN                   = 70,   // 아이템을 창고에 넣는다.
    HEADER_CG_SAFEBOX_CHECKOUT                  = 71,   // 아이템을 창고로 부터 빼온다.
    HEADER_CG_PARTY_INVITE                      = 72,
    HEADER_CG_PARTY_INVITE_ANSWER               = 73,
    HEADER_CG_PARTY_REMOVE                      = 74,
    HEADER_CG_PARTY_SET_STATE                   = 75,
    HEADER_CG_PARTY_USE_SKILL                   = 76,
    HEADER_CG_SAFEBOX_ITEM_MOVE                 = 77,
	HEADER_CG_PARTY_PARAMETER                   = 78,
#if defined(ENABLE_AURA_SYSTEM)
	HEADER_CG_AURA = 79,
#endif
	//HEADER_BLANK68								= 79,
	HEADER_CG_GUILD								= 80,
	HEADER_CG_ANSWER_MAKE_GUILD					= 81,
	HEADER_CG_FISHING                           = 82,
	HEADER_CG_GIVE_ITEM                         = 83,
#ifdef ENABLE_NEW_FISHING_SYSTEM
	HEADER_CG_FISHING_NEW = 216, 
#endif
#if defined(ENABLE_NEW_FISH_EVENT)
	HEADER_CG_FISH_EVENT_SEND = 219,
#endif
	//HEADER_BLANK84								= 84,
	//HEADER_BLANK85								= 85,
	//HEADER_BLANK86								= 86,
	//HEADER_BLANK87								= 87,
	//HEADER_BLANK88								= 88,
	//HEADER_BLANK89								= 89,
    HEADER_CG_EMPIRE                            = 90,
	//HEADER_BLANK91								= 91,
	//HEADER_BLANK92								= 92,
	//HEADER_BLANK93								= 93,
	//HEADER_BLANK94								= 94,
	//HEADER_BLANK95								= 95,
	HEADER_CG_REFINE = 96,
	//HEADER_BLANK97								= 97,
	//HEADER_BLANK98								= 98,

	HEADER_CG_MARK_LOGIN						= 100,
	HEADER_CG_MARK_CRCLIST						= 101,
	HEADER_CG_MARK_UPLOAD						= 102,
	HEADER_CG_MARK_IDXLIST						= 104,

	//HEADER_CG_CRC_REPORT						= 103,

	HEADER_CG_HACK								= 105,
    HEADER_CG_CHANGE_NAME                       = 106,
	HEADER_CG_CHANGE_COUNTRY_FLAG = 107,
	HEADER_CG_LOGIN2 = 109,
	HEADER_CG_DUNGEON							= 110,
	HEADER_CG_GUILD_SYMBOL_UPLOAD				= 112,
	HEADER_CG_GUILD_SYMBOL_CRC					= 113,
	HEADER_CG_SCRIPT_SELECT_ITEM				= 114,
	//HEADER_CG_LOGIN4							= 115,
#ifdef __ENABLE_NEW_OFFLINESHOP__
	HEADER_CG_NEW_OFFLINESHOP					= 119,
#endif
	HEADER_CG_DRAGON_SOUL_REFINE			= 205,
	HEADER_CG_STATE_CHECKER					= 206,
#ifdef ENABLE_DS_REFINE_ALL
	HEADER_CG_DRAGON_SOUL_REFINE_ALL = 207,
#endif
#ifdef ENABLE_WHISPER_ADMIN_SYSTEM
	HEADER_CG_WHISPER_ADMIN			= 220,
#endif


#ifdef __AUCTION__
	HEADER_CG_AUCTION_CMD							= 205,
#endif


#ifdef ENABLE_CUBE_RENEWAL_WORLDARD
	HEADER_CG_CUBE_RENEWAL 						= 215,
#endif
#if defined(ENABLE_LETTERS_EVENT)
	HEADER_CG_TAKE_LETTERS_REWARD = 212,
#endif
#if defined(ENABLE_CHANGELOOK)
	HEADER_CG_CHANGE_LOOK = 213,
#endif
	HEADER_CG_WHISPER_INFO = 214,
	HEADER_CG_KEY_AGREEMENT = 0xec,
	HEADER_CG_TIME_SYNC = 0xed,
	HEADER_CG_CLIENT_VERSION = 0xfd,
	HEADER_CG_CLIENT_VERSION2 = 0xf1,
	HEADER_CG_PONG = 0xef,
	HEADER_CG_HANDSHAKE = 0xf0,
	/////////////////////////////////////////////////
	// From Server

	HEADER_GC_CHARACTER_ADD						= 1,
#ifdef ENABLE_SWITCHBOT_WORLDARD
	HEADER_CG_SWITCHBOT					= 171,
#endif
	HEADER_GC_CHARACTER_DEL						= 2,
	HEADER_GC_CHARACTER_MOVE					= 3,
	HEADER_GC_CHAT								= 4,
	HEADER_GC_SYNC_POSITION 					= 5,
	HEADER_GC_LOGIN_SUCCESS3					= 6,
	HEADER_GC_LOGIN_FAILURE						= 7,
	HEADER_GC_PLAYER_CREATE_SUCCESS				= 8,
	HEADER_GC_PLAYER_CREATE_FAILURE				= 9,
	HEADER_GC_PLAYER_DELETE_SUCCESS				= 10,
	HEADER_GC_PLAYER_DELETE_WRONG_SOCIAL_ID		= 11,
	// 12
	HEADER_GC_STUN								= 13,
	HEADER_GC_DEAD								= 14,

	HEADER_GC_PLAYER_POINTS						= 16,
	HEADER_GC_PLAYER_POINT_CHANGE				= 17,
	HEADER_GC_CHANGE_SPEED						= 18,
	HEADER_GC_CHARACTER_UPDATE                  = 19,
#if defined(GAIDEN)
	HEADER_GC_ITEM_DEL							= 20, // 아이템 창에 추가
	HEADER_GC_ITEM_SET							= 21, // 아이템 창에 추가
#else
	HEADER_GC_ITEM_SET							= 20, // 아이템 창에 추가
	HEADER_GC_ITEM_SET2							= 21, // 아이템 창에 추가
#endif
	HEADER_GC_ITEM_USE							= 22, // 아이템 사용 (주위 사람들에게 보여주기 위해)
	HEADER_GC_ITEM_DROP							= 23, // 아이템 버리기
	HEADER_GC_ITEM_UPDATE						= 25, // 아이템 수치 업데이트
	HEADER_GC_ITEM_GROUND_ADD					= 26, // 바닥에 아이템 추가
	HEADER_GC_ITEM_GROUND_DEL					= 27, // 바닥에서 아이템 삭제
	HEADER_GC_QUICKSLOT_ADD = 28,
	HEADER_GC_QUICKSLOT_DEL = 29,
	HEADER_GC_QUICKSLOT_SWAP = 30,
	HEADER_GC_ITEM_OWNERSHIP					= 31,
	HEADER_GC_LOGIN_SUCCESS4					= 32,
#ifdef USE_CAPTCHA_SYSTEM
    HEADER_GC_CAPTCHA                           = 33,
#endif
	HEADER_GC_WHISPER							= 34,
#if defined(ENABLE_CLOSE_GAMECLIENT_CMD)
	HEADER_GC_CLOSECLIENT = 35,
#endif
	HEADER_GC_MOTION							= 36,

	HEADER_GC_SHOP							    = 38,
	HEADER_GC_SHOP_SIGN							= 39,

	// 39 ~ 41 Balnk
	HEADER_GC_DUEL_START						= 40,
	HEADER_GC_PVP								= 41,
	HEADER_GC_EXCHANGE							= 42,
    HEADER_GC_CHARACTER_POSITION                = 43,

	HEADER_GC_PING								= 44,

	HEADER_GC_SCRIPT							= 45,
	HEADER_GC_QUEST_CONFIRM                     = 46,
#if defined(ENABLE_EVENT_MANAGER)
	HEADER_GC_EVENT_MANAGER = 47,
#endif
#if defined(ENABLE_NEW_ANTICHEAT_RULES)
	HEADER_GC_ANTICHEAT = 48,
#endif
#ifdef NEW_PET_SYSTEM
	HEADER_CG_PetSetName						= 146,
#endif
	HEADER_GC_MOUNT								= 61,
	HEADER_GC_OWNERSHIP                         = 62,
    HEADER_GC_TARGET                            = 63,
	HEADER_GC_WARP								= 65,
	HEADER_GC_ADD_FLY_TARGETING                 = 69,

	HEADER_GC_CREATE_FLY						= 70,
	HEADER_GC_FLY_TARGETING						= 71,
	HEADER_GC_SKILL_LEVEL						= 72,
	HEADER_GC_SKILL_COOLTIME_END				= 73,
    HEADER_GC_MESSENGER                         = 74,
	HEADER_GC_GUILD								= 75,
	HEADER_GC_SKILL_LEVEL_NEW					= 76,

    HEADER_GC_PARTY_INVITE                      = 77,
    HEADER_GC_PARTY_ADD                         = 78,
    HEADER_GC_PARTY_UPDATE                      = 79,
    HEADER_GC_PARTY_REMOVE                      = 80,

    HEADER_GC_QUEST_INFO                        = 81,
    HEADER_GC_REQUEST_MAKE_GUILD                = 82,
	HEADER_GC_PARTY_PARAMETER                   = 83,

    HEADER_GC_SAFEBOX_MONEY_CHANGE              = 84,
    HEADER_GC_SAFEBOX_SET                       = 85,
    HEADER_GC_SAFEBOX_DEL                       = 86,
    HEADER_GC_SAFEBOX_WRONG_PASSWORD            = 87,
    HEADER_GC_SAFEBOX_SIZE                      = 88,

    HEADER_GC_FISHING                           = 89,

    HEADER_GC_EMPIRE                            = 90,

    HEADER_GC_PARTY_LINK                        = 91,
    HEADER_GC_PARTY_UNLINK                      = 92,
#if defined(ENABLE_INGAME_ITEMSHOP)
	HEADER_GC_ITEMSHOP = 93,
#endif
#ifdef ENABLE_NEW_FISHING_SYSTEM
	HEADER_GC_FISHING_NEW = 223, 
#endif
#if defined(ENABLE_NEW_FISH_EVENT)
	HEADER_GC_FISH_EVENT_INFO = 224,
#endif
	HEADER_GC_OBSERVER_ADD						= 96,
	HEADER_GC_OBSERVER_REMOVE					= 97,
	HEADER_GC_OBSERVER_MOVE						= 98,
	HEADER_GC_VIEW_EQUIP = 99,

	HEADER_GC_MARK_BLOCK						= 100,
	HEADER_GC_MARK_DIFF_DATA                    = 101,
	HEADER_GC_MARK_IDXLIST						= 102,

	//HEADER_GC_SLOW_TIMER						= 105,
    HEADER_GC_TIME                              = 106,
    HEADER_GC_CHANGE_NAME                       = 107,
	HEADER_GC_CHANGE_COUNTRY_FLAG				= 109,
	HEADER_GC_DUNGEON							= 110,
	HEADER_GC_WALK_MODE							= 111,
	HEADER_GC_CHANGE_SKILL_GROUP				= 112,
	HEADER_GC_MAIN_CHARACTER					= 113,
	HEADER_GC_MAIN_CHARACTER3_BGM				= 137,
	HEADER_GC_MAIN_CHARACTER4_BGM_VOL			= 138,
    HEADER_GC_SEPCIAL_EFFECT                    = 114,
	HEADER_GC_NPC_POSITION						= 115,
    HEADER_GC_CHARACTER_UPDATE2                 = 117,
    HEADER_GC_LOGIN_KEY                         = 118,
#if defined(ENABLE_EXCHANGE_FRAGMENTS)
	HEADER_CG_EXCHANGE_FRAGMENTS = 118,
#endif
    HEADER_GC_REFINE_INFORMATION = 119,
    HEADER_GC_CHARACTER_ADD2                    = 120,
    HEADER_GC_CHANNEL                           = 121,

    HEADER_GC_MALL_OPEN                         = 122,
	HEADER_GC_TARGET_UPDATE                     = 123,
	HEADER_GC_TARGET_DELETE                     = 124,
	HEADER_GC_TARGET_CREATE_NEW                 = 125,

	HEADER_GC_AFFECT_ADD                        = 126,
	HEADER_GC_AFFECT_REMOVE                     = 127,

    HEADER_GC_MALL_SET                          = 128,
    HEADER_GC_MALL_DEL                          = 129,
	HEADER_GC_LAND_LIST                         = 130,
	HEADER_GC_LOVER_INFO						= 131,
	HEADER_GC_LOVE_POINT_UPDATE					= 132,
	HEADER_GC_GUILD_SYMBOL_DATA					= 133,
    HEADER_GC_DIG_MOTION                        = 134,

	HEADER_GC_DAMAGE_INFO						= 135,
	HEADER_GC_CHAR_ADDITIONAL_INFO				= 136,
    HEADER_GC_AUTH_SUCCESS                      = 150,
#if defined(ENABLE_TEXTS_RENEWAL)
	HEADER_GC_CHAT_NEW = 155,
#endif
#if defined(ENABLE_GAYA_RENEWAL)
	HEADER_GC_GEM_SHOP_OPEN = 156,
	HEADER_GC_GEM_SHOP_REFRESH = 157,
#endif
#ifdef ENABLE_SWITCHBOT_WORLDARD
	HEADER_GC_SWITCHBOT = 171,
#endif
#if defined(GAIDEN)
	HEADER_GC_ONTIME							= 204,
	HEADER_GC_RESET_ONTIME						= 205,

	// AUTOBAN
	HEADER_GC_AUTOBAN_QUIZ						= 206,
	// END_OF_AUTOBAN
#endif

#ifdef __AUCTION__
	HEADER_GC_AUCTOIN_ITEM_LIST					= 206,
#endif

	HEADER_GC_SPECIFIC_EFFECT					= 208,
	HEADER_GC_DRAGON_SOUL_REFINE						= 209,
	HEADER_GC_RESPOND_CHANNELSTATUS				= 210,
#if defined(ENABLE_NEW_GOLD_LIMIT)
	HEADER_GC_CHARACTER_GOLD = 213,
	HEADER_GC_CHARACTER_GOLD_CHANGE = 216,
#endif

#ifdef __ENABLE_NEW_OFFLINESHOP__
	HEADER_GC_NEW_OFFLINESHOP					= 214,
#endif


#ifdef ENABLE_CUBE_RENEWAL_WORLDARD
	HEADER_GC_CUBE_RENEWAL = 217,
#endif

#if defined(ENABLE_CHANGELOOK)
	HEADER_GC_CHANGE_LOOK = 219,
#endif
#if defined(ENABLE_AURA_SYSTEM)
	HEADER_GC_AURA = 221,
#endif
#ifdef ENABLE_ATLAS_BOSS
	HEADER_GC_BOSS_POSITION = 222,
#endif

#if defined(USE_BATTLEPASS)
	HEADER_GC_EXT_BATTLE_PASS_OPEN = 225,
	HEADER_GC_EXT_BATTLE_PASS_GENERAL_INFO = 226,
	HEADER_GC_EXT_BATTLE_PASS_MISSION_INFO = 227,
	HEADER_GC_EXT_BATTLE_PASS_MISSION_UPDATE = 228,
	HEADER_GC_EXT_BATTLE_PASS_SEND_RANKING = 229,
#endif
	HEADER_GC_BOSS_POSITION = 230,
	HEADER_GC_WHISPER_INFO = 231,


	/////////////////////////////////////////////////
	HEADER_GC_KEY_AGREEMENT_COMPLETED = 0xeb,
	HEADER_GC_KEY_AGREEMENT = 0xec,
	HEADER_GC_HANDSHAKE_OK = 0xed,
	HEADER_GC_PHASE = 0xee,
	HEADER_GC_BINDUDP = 0xef,
	HEADER_GC_HANDSHAKE = 0xf0,
};

enum
{
	CHAT_MAX_NUM = 128,
	PATH_NODE_MAX_NUM = 64,
	SHOP_SIGN_MAX_LEN = 32,

	PLAYER_PER_ACCOUNT3 = 3,
#ifndef ENABLE_PLAYER_PER_ACCOUNT5
	PLAYER_PER_ACCOUNT4 = 4,
#else
	PLAYER_PER_ACCOUNT4 = 5,
	PLAYER_PER_ACCOUNT5 = 5,
#endif

	PLAYER_ITEM_SLOT_MAX_NUM = 20,		// 플래이어의 슬롯당 들어가는 갯수.

	QUICKSLOT_MAX_LINE = 4,
	QUICKSLOT_MAX_COUNT_PER_LINE = 8,
	QUICKSLOT_MAX_COUNT = QUICKSLOT_MAX_LINE * QUICKSLOT_MAX_COUNT_PER_LINE,
	QUICKSLOT_MAX_NUM = 36,

	SHOP_HOST_ITEM_MAX_NUM = 40,

	METIN_SOCKET_COUNT = 6,

	PARTY_AFFECT_SLOT_MAX_NUM = 7,

	GUILD_GRADE_NAME_MAX_LEN = 8,
	GUILD_NAME_MAX_LEN = 12,
	GUILD_GRADE_COUNT = 15,
	GULID_COMMENT_MAX_LEN = 50,

	MARK_CRC_NUM = 8*8,
	MARK_DATA_SIZE = 16*12,
	SYMBOL_DATA_SIZE = 128*256,
	QUEST_INPUT_STRING_MAX_NUM = 64,

	PRIVATE_CODE_LENGTH = 8,
	REFINE_MATERIAL_MAX_NUM = 5,

	WEAR_MAX_NUM = CItemData::WEAR_MAX_NUM,

	SHOP_TAB_NAME_MAX = 32,
	SHOP_TAB_COUNT_MAX = 3,
#ifdef ENABLE_HWID
	HWID_LENGTH = 64,
#endif
};

#pragma pack(push)
#pragma pack(1)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Mark
typedef struct command_mark_login
{
    BYTE    header;
    DWORD   handle;
    DWORD   random_key;
	DWORD dwHandshake;
} TPacketCGMarkLogin;

typedef struct command_mark_upload
{
    BYTE    header;
    DWORD   gid, pid;
    BYTE    image[16*12*4];
} TPacketCGMarkUpload;

typedef struct command_mark_idxlist
{
    BYTE    header;
} TPacketCGMarkIDXList;

typedef struct command_mark_crclist
{
    BYTE    header;
    BYTE    imgIdx;
    DWORD   crclist[80];
} TPacketCGMarkCRCList;

typedef struct packet_mark_idxlist
{
    BYTE    header;
	DWORD	bufSize;
    WORD    count;
    //뒤에 size * (WORD + WORD)만큼 데이터 붙음
} TPacketGCMarkIDXList;

typedef struct packet_mark_block
{
    BYTE    header;
    DWORD   bufSize;
	BYTE	imgIdx;
    DWORD   count;
    // 뒤에 64 x 48 x 픽셀크기(4바이트) = 12288만큼 데이터 붙음
} TPacketGCMarkBlock;

typedef struct command_symbol_upload
{
	BYTE	header;
	WORD	size;
	DWORD	handle;
} TPacketCGSymbolUpload;

typedef struct command_symbol_crc
{
	BYTE	header;
	DWORD	dwGuildID;
	DWORD	dwCRC;
	DWORD	dwSize;
} TPacketCGSymbolCRC;

typedef struct packet_symbol_data
{
    BYTE header;
    WORD size;
    DWORD guild_id;
} TPacketGCGuildSymbolData;

//
//
//
typedef struct packet_observer_add
{
	BYTE	header;
	DWORD	vid;
	WORD	x;
	WORD	y;
} TPacketGCObserverAdd;

typedef struct packet_observer_move
{
	BYTE	header;
	DWORD	vid;
	WORD	x;
	WORD	y;
} TPacketGCObserverMove;


typedef struct packet_observer_remove
{
	BYTE	header;
	DWORD	vid;
} TPacketGCObserverRemove;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// To Server

typedef struct command_checkin
{
	BYTE header;
	char name[LOGIN_MAX_LEN+1];
	char pwd[PASSWD_MAX_LEN+1];
} TPacketCGCheckin;

typedef struct command_login
{
    BYTE header;
    char name[LOGIN_MAX_LEN + 1];
    char pwd[PASSWD_MAX_LEN + 1];
} TPacketCGLogin;

typedef struct command_login2
{
	BYTE	header;
	char	name[LOGIN_MAX_LEN + 1];
	DWORD	login_key;
    DWORD	adwClientKey[4];
} TPacketCGLogin2;

typedef struct command_login3 {
	uint8_t header;
	char name[LOGIN_MAX_LEN + 1];
	char pwd[PASSWD_MAX_LEN + 1];
	int32_t adwClientKey[4];
#ifdef ENABLE_HWID
	char hwid[HWID_LENGTH + 1];
#endif
#if defined(ENABLE_NEW_ANTICHEAT_RULES)
	uint32_t loginHash;
#endif
#ifdef ENABLE_MULTI_LANGUAGE
    uint8_t lang;
#endif
} TPacketCGLogin3;

#ifdef NEW_PET_SYSTEM
typedef struct packet_RequestPetName
{
	BYTE byHeader;
	char petname[13];
} TPacketCGRequestPetName;
#endif

typedef struct command_direct_enter
{
    BYTE        bHeader;
    char        login[LOGIN_MAX_LEN + 1];
    char        passwd[PASSWD_MAX_LEN + 1];
    BYTE        index;
} TPacketCGDirectEnter;

typedef struct command_player_select
{
	BYTE	header;
	BYTE	player_index;
} TPacketCGSelectCharacter;

typedef struct SPacketCGAttack
{
	uint8_t bHeader;
	uint8_t bType;
	uint32_t dwVID;
	uint8_t bCRCMagicCubeProcPiece;
	uint8_t bCRCMagicCubeFilePiece;
#if defined(ENABLE_NEW_ANTICHEAT_RULES)
	uint32_t dwVictimVIDVerify;
#endif
} TPacketCGAttack;

typedef struct command_chat
{
	BYTE	header;
	WORD	length;
	BYTE	type;
} TPacketCGChat;

typedef struct command_whisper
{
    BYTE        bHeader;
    WORD        wSize;
    char        szNameTo[CHARACTER_NAME_MAX_LEN + 1];
} TPacketCGWhisper;

typedef struct command_sms
{
    BYTE        bHeader;
    WORD        wSize;
    char        szNameTo[CHARACTER_NAME_MAX_LEN + 1];
} TPacketCGSMS;

enum EBattleMode
{
	BATTLEMODE_ATTACK = 0,
	BATTLEMODE_DEFENSE = 1,
};

typedef struct command_EnterFrontGame
{
	BYTE header;
} TPacketCGEnterFrontGame;

typedef struct command_item_use
{
	BYTE header;
	TItemPos pos;
} TPacketCGItemUse;

typedef struct command_item_use_to_item
{
	BYTE header;
	TItemPos source_pos;
	TItemPos target_pos;
} TPacketCGItemUseToItem;

typedef struct command_item_drop
{
	BYTE  header;
	TItemPos pos;
} TPacketCGItemDrop;

typedef struct command_item_drop2
{
	BYTE		header;
	TItemPos	pos;
	WORD count;
} TPacketCGItemDrop2;

typedef struct command_item_destroy
{
	BYTE		header;
	TItemPos	pos;
} TPacketCGItemDestroy;

typedef struct command_item_division
{
	BYTE		header;
	TItemPos	pos;
} TPacketCGItemDivision;

typedef struct command_item_move
{
	BYTE		header;
	TItemPos	pos;
	TItemPos	change_pos;
	WORD count;
} TPacketCGItemMove;

typedef struct command_item_pickup
{
	BYTE header;
	DWORD vid;
} TPacketCGItemPickUp;

#if defined(ENABLE_GAYA_RENEWAL)
typedef struct command_gem_shop
{
	BYTE	header;
	BYTE	subheader;
} TPacketCGGemShop;

typedef struct command_gem_shop_open
{
	BYTE	header;
	int		nextRefreshTime;
	TGemShopItem shopItems[9];
} TPacketGCGemShopOpen;

typedef struct command_gem_shop_refresh
{
	BYTE	header;
	int		nextRefreshTime;
	TGemShopItem shopItems[9];
} TPacketGCGemShopRefresh;

enum
{
	GEM_SHOP_SUBHEADER_CG_BUY,
	GEM_SHOP_SUBHEADER_CG_ADD,
	GEM_SHOP_SUBHEADER_CG_REFRESH,
};
#endif

typedef struct command_on_click
{
	BYTE		header;
	DWORD		vid;
} TPacketCGOnClick;

enum
{
	SHOP_SUBHEADER_CG_END,
	SHOP_SUBHEADER_CG_BUY,
	SHOP_SUBHEADER_CG_SELL,
	SHOP_SUBHEADER_CG_SELL2
#ifdef ENABLE_BUY_STACK_FROM_SHOP
	,SHOP_SUBHEADER_CG_BUY2
#endif
};

typedef struct command_shop
{
	BYTE	header;
	BYTE	subheader;
} TPacketCGShop;

enum
{
	EXCHANGE_SUBHEADER_CG_START,			// arg1 == vid of target character
	EXCHANGE_SUBHEADER_CG_ITEM_ADD,		// arg1 == position of item
	EXCHANGE_SUBHEADER_CG_ITEM_DEL,		// arg1 == position of item
	EXCHANGE_SUBHEADER_CG_ELK_ADD,			// arg1 == amount of elk
	EXCHANGE_SUBHEADER_CG_ACCEPT,			// arg1 == not used
	EXCHANGE_SUBHEADER_CG_CANCEL,			// arg1 == not used
};

typedef struct command_exchange
{
	BYTE		header;
	BYTE		subheader;
#if defined(ENABLE_NEW_GOLD_LIMIT)
	uint64_t arg1;
#else
	uint32_t arg1;
#endif
	BYTE		arg2;
	TItemPos	Pos;
#if defined(ITEM_CHECKINOUT_UPDATE)
	bool		SelectPosAuto;
#endif
} TPacketCGExchange;

typedef struct command_position
{
    BYTE        header;
    BYTE        position;
} TPacketCGPosition;

typedef struct command_script_answer
{
    BYTE        header;
	BYTE		answer;
} TPacketCGScriptAnswer;

typedef struct command_script_button
{
    BYTE        header;
	unsigned int			idx;
} TPacketCGScriptButton;

typedef struct command_target
{
    BYTE        header;
    DWORD       dwVID;
} TPacketCGTarget;

typedef struct command_move
{
	BYTE		bHeader;
	BYTE		bFunc;
	BYTE		bArg;
	BYTE		bRot;
	LONG		lX;
	LONG		lY;
	DWORD		dwTime;
#if defined(ENABLE_NEW_ANTICHEAT_RULES)
	long uX;
	long uY;
#endif
} TPacketCGMove;

typedef struct command_sync_position_element
{
    DWORD       dwVID;
    long        lX;
    long        lY;
} TPacketCGSyncPositionElement;

typedef struct command_sync_position
{
    BYTE        bHeader;
	WORD		wSize;
} TPacketCGSyncPosition;

typedef struct command_fly_targeting
{
	BYTE		bHeader;
	DWORD		dwTargetVID;
	long		lX;
	long		lY;
} TPacketCGFlyTargeting;

typedef struct packet_fly_targeting
{
    BYTE        bHeader;
	DWORD		dwShooterVID;
	DWORD		dwTargetVID;
	long		lX;
	long		lY;
} TPacketGCFlyTargeting;

typedef struct packet_shoot
{
    BYTE		bHeader;
    BYTE		bType;
} TPacketCGShoot;

typedef struct command_warp
{
	BYTE			bHeader;
} TPacketCGWarp;

enum
{
#if defined(ENABLE_MESSENGER_TEAM)
	MESSENGER_SUBHEADER_GC_TEAM,
	MESSENGER_SUBHEADER_GC_TEAM_UPDATE,
#endif
	MESSENGER_SUBHEADER_GC_LIST,
	MESSENGER_SUBHEADER_GC_LOGIN,
	MESSENGER_SUBHEADER_GC_LOGOUT,
	MESSENGER_SUBHEADER_GC_INVITE,
	MESSENGER_SUBHEADER_GC_MOBILE,
	MESSENGER_SUBHEADER_GC_REMOVE_FRIEND,
#if defined(ENABLE_MESSENGER_BLOCK)
	MESSENGER_SUBHEADER_GC_BLOCK_LIST,
	MESSENGER_SUBHEADER_GC_BLOCK_LOGIN,
	MESSENGER_SUBHEADER_GC_BLOCK_LOGOUT,
	MESSENGER_SUBHEADER_GC_BLOCK_INVITE,
#endif
};

typedef struct packet_messenger
{
    BYTE header;
    WORD size;
    BYTE subheader;
} TPacketGCMessenger;

#if defined(ENABLE_MESSENGER_TEAM)
typedef struct STeamMessenger
{
	char szName[CHARACTER_NAME_MAX_LEN + 1];
	bool isConnected;
} TTeamMessenger;
#endif

enum
{
	MESSENGER_CONNECTED_STATE_OFFLINE,
	MESSENGER_CONNECTED_STATE_ONLINE,
	MESSENGER_CONNECTED_STATE_MOBILE,
};

typedef struct packet_messenger_list_offline
{
	BYTE connected; // always 0
	BYTE length;
} TPacketGCMessengerListOffline;

typedef struct packet_messenger_list_online
{
	BYTE connected;
	BYTE length;
	//BYTE length_char_name;
} TPacketGCMessengerListOnline;

typedef struct packet_messenger_login
{
	//BYTE length_login;
	//BYTE length_char_name;
	BYTE length;
} TPacketGCMessengerLogin;

typedef struct packet_messenger_logout
{
	BYTE length;
} TPacketGCMessengerLogout;

enum {
	MESSENGER_SUBHEADER_CG_ADD_BY_VID,
	MESSENGER_SUBHEADER_CG_ADD_BY_NAME,
	MESSENGER_SUBHEADER_CG_REMOVE,
	MESSENGER_SUBHEADER_CG_INVITE_ANSWER,
#if defined(ENABLE_MESSENGER_BLOCK)
	MESSENGER_SUBHEADER_CG_ADD_BLOCK_BY_VID,
	MESSENGER_SUBHEADER_CG_ADD_BLOCK_BY_NAME,
	MESSENGER_SUBHEADER_CG_REMOVE_BLOCK,
#endif
};

typedef struct command_messenger
{
    BYTE header;
    BYTE subheader;
} TPacketCGMessenger;

typedef struct command_messenger_remove
{
	BYTE length;
} TPacketCGMessengerRemove;

enum
{
	SAFEBOX_MONEY_STATE_SAVE,
	SAFEBOX_MONEY_STATE_WITHDRAW,
};

typedef struct command_safebox_money
{
    BYTE        bHeader;
    BYTE        bState;
    DWORD       dwMoney;
} TPacketCGSafeboxMoney;

typedef struct command_safebox_checkout
{
    BYTE        bHeader;
    BYTE        bSafePos;
    TItemPos	ItemPos;
#if defined(ITEM_CHECKINOUT_UPDATE)
	bool		SelectPosAuto;
#endif
} TPacketCGSafeboxCheckout;

typedef struct command_safebox_checkin
{
    BYTE        bHeader;
    BYTE        bSafePos;
    TItemPos	ItemPos;
#if defined(ITEM_CHECKINOUT_UPDATE)
	bool		SelectPosAuto;
#endif
} TPacketCGSafeboxCheckin;

typedef struct command_mall_checkout
{
    BYTE        bHeader;
    BYTE        bMallPos;
    TItemPos	ItemPos;
#if defined(ITEM_CHECKINOUT_UPDATE)
	bool		SelectPosAuto;
#endif
} TPacketCGMallCheckout;

///////////////////////////////////////////////////////////////////////////////////
// Party

typedef struct command_use_skill
{
    BYTE                bHeader;
    DWORD               dwVnum;
	DWORD				dwTargetVID;
} TPacketCGUseSkill;

typedef struct command_party_invite
{
    BYTE header;
    DWORD vid;
} TPacketCGPartyInvite;

typedef struct command_party_invite_answer
{
    BYTE header;
    DWORD leader_pid;
    BYTE accept;
} TPacketCGPartyInviteAnswer;

typedef struct command_party_remove
{
    BYTE header;
    DWORD pid;
} TPacketCGPartyRemove;

typedef struct command_party_set_state
{
    BYTE byHeader;
    DWORD dwVID;
	BYTE byState;
    BYTE byFlag;
} TPacketCGPartySetState;

typedef struct packet_party_link
{
    BYTE header;
    DWORD pid;
    DWORD vid;
} TPacketGCPartyLink;

typedef struct packet_party_unlink
{
    BYTE header;
    DWORD pid;
	DWORD vid;
} TPacketGCPartyUnlink;

typedef struct command_party_use_skill
{
    BYTE byHeader;
	BYTE bySkillIndex;
    DWORD dwTargetVID;
} TPacketCGPartyUseSkill;

enum
{
	GUILD_SUBHEADER_CG_ADD_MEMBER,
	GUILD_SUBHEADER_CG_REMOVE_MEMBER,
	GUILD_SUBHEADER_CG_CHANGE_GRADE_NAME,
	GUILD_SUBHEADER_CG_CHANGE_GRADE_AUTHORITY,
	GUILD_SUBHEADER_CG_OFFER,
	GUILD_SUBHEADER_CG_POST_COMMENT,
	GUILD_SUBHEADER_CG_DELETE_COMMENT,
	GUILD_SUBHEADER_CG_REFRESH_COMMENT,
	GUILD_SUBHEADER_CG_CHANGE_MEMBER_GRADE,
	GUILD_SUBHEADER_CG_USE_SKILL,
	GUILD_SUBHEADER_CG_CHANGE_MEMBER_GENERAL,
	GUILD_SUBHEADER_CG_GUILD_INVITE_ANSWER,
	GUILD_SUBHEADER_CG_CHARGE_GSP,
	GUILD_SUBHEADER_CG_DEPOSIT_MONEY,
	GUILD_SUBHEADER_CG_WITHDRAW_MONEY,
	GUILD_SUBHEADER_CG_CHANGE_SYMBOL,
};

typedef struct command_guild
{
    BYTE byHeader;
	BYTE bySubHeader;
} TPacketCGGuild;

typedef struct command_guild_answer_make_guild
{
	BYTE header;
	char guild_name[GUILD_NAME_MAX_LEN+1];
} TPacketCGAnswerMakeGuild;

typedef struct command_give_item
{
	BYTE		byHeader;
	DWORD		dwTargetVID;
	TItemPos	ItemPos;
	WORD byItemCount;
} TPacketCGGiveItem;

typedef struct SPacketCGHack
{
    BYTE        bHeader;
    char        szBuf[255 + 1];
} TPacketCGHack;

typedef struct command_dungeon
{
	BYTE		bHeader;
	WORD		size;
} TPacketCGDungeon;

// Private Shop
#ifdef ENABLE_BUY_WITH_ITEM
typedef struct SShopItemPrice
{
	DWORD		vnum;
	DWORD		count;
} TShopItemPrice;
#endif

typedef struct SShopItemTable
{
	DWORD		vnum;
	WORD count;
#ifdef ENABLE_BUY_WITH_ITEM
	TShopItemPrice	itemprice[MAX_SHOP_PRICES];
#endif
	TItemPos	pos;
#if defined(ENABLE_NEW_GOLD_LIMIT)
	uint64_t price;
#else
	uint32_t price;
#endif
	BYTE		display_pos;
} TShopItemTable;

typedef struct SPacketCGMyShop
{
	BYTE	bHeader;
	char	szSign[SHOP_SIGN_MAX_LEN + 1];
	BYTE	bCount;
} TPacketCGMyShop;

typedef struct SPacketCGRefine
{
	uint8_t header;
	uint8_t pos;
	uint8_t type;
#ifdef ENABLE_FEATURES_REFINE_SYSTEM
	uint8_t lLow;
	uint8_t lMedium;
	uint8_t lExtra;
	uint8_t lTotal;
#endif
} TPacketCGRefine;

typedef struct SPacketCGChangeName
{
    BYTE header;
    BYTE index;
    char name[CHARACTER_NAME_MAX_LEN+1];
} TPacketCGChangeName;

typedef struct command_client_version
{
	BYTE header;
	char filename[32+1];
	char timestamp[32+1];
} TPacketCGClientVersion;

typedef struct command_client_version2
{
	BYTE header;
	char filename[32+1];
	char timestamp[32+1];
} TPacketCGClientVersion2;

typedef struct command_crc_report
{
	BYTE header;
	BYTE byPackMode;
	DWORD dwBinaryCRC32;
	DWORD dwProcessCRC32;
	DWORD dwRootPackCRC32;
} TPacketCGCRCReport;

enum EPartyExpDistributionType
{
    PARTY_EXP_DISTRIBUTION_NON_PARITY,
    PARTY_EXP_DISTRIBUTION_PARITY,
};

typedef struct command_party_parameter
{
    BYTE        bHeader;
    BYTE        bDistributeMode;
} TPacketCGPartyParameter;

typedef struct command_quest_input_string
{
    BYTE        bHeader;
    char		szString[QUEST_INPUT_STRING_MAX_NUM+1];
} TPacketCGQuestInputString;

typedef struct command_quest_confirm
{
    BYTE header;
    BYTE answer;
    DWORD requestPID;
} TPacketCGQuestConfirm;

typedef struct command_script_select_item
{
    BYTE header;
    DWORD selection;
} TPacketCGScriptSelectItem;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// From Server
enum EPhase
{
    PHASE_CLOSE,				// 끊기는 상태 (또는 끊기 전 상태)
    PHASE_HANDSHAKE,			// 악수..;;
    PHASE_LOGIN,				// 로그인 중
    PHASE_SELECT,				// 캐릭터 선택 화면
    PHASE_LOADING,				// 선택 후 로딩 화면
    PHASE_GAME,					// 게임 화면
    PHASE_DEAD,					// 죽었을 때.. (게임 안에 있는 것일 수도..)

	PHASE_DBCLIENT_CONNECTING,	// 서버용
    PHASE_DBCLIENT,				// 서버용
    PHASE_P2P,					// 서버용
    PHASE_AUTH,					// 로그인 인증 용
	PHASE_GUILD_MARK,
};

typedef struct packet_phase
{
    BYTE        header;
    BYTE        phase;
} TPacketGCPhase;

typedef struct packet_blank		// 공백패킷.
{
	BYTE		header;
} TPacketGCBlank;

typedef struct packet_blank_dynamic
{
	BYTE		header;
	WORD		size;
} TPacketGCBlankDynamic;

typedef struct packet_header_handshake
{
	BYTE		header;
	DWORD		dwHandshake;
	DWORD		dwTime;
	LONG		lDelta;
} TPacketGCHandshake;

typedef struct packet_header_bindudp
{
	BYTE		header;
	DWORD		addr;
	WORD		port;
} TPacketGCBindUDP;

typedef struct packet_header_dynamic_size
{
	uint8_t header;
	uint16_t size;
} TDynamicSizePacketHeader;

typedef struct packet_header_large_dynamic_size
{
	uint8_t header;
	int32_t size;
} TLargeDynamicSizePacketHeader;

typedef struct SSimplePlayerInformation
{
	DWORD				dwID;
	char				szName[CHARACTER_NAME_MAX_LEN + 1];
	BYTE				byJob;
	BYTE				byLevel;
	DWORD				dwPlayMinutes;
	BYTE				byST, byHT, byDX, byIQ;
	// uint32_t wParts[CRaceData::PART_MAX_NUM];
	uint32_t wMainPart;
	BYTE				bChangeName;
	uint32_t wHairPart;
#ifdef ENABLE_ACCE_SYSTEM
	uint32_t wAccePart;
#endif
	BYTE				bDummy[4];
	long				x, y;
	LONG				lAddr;
	WORD				wPort;
	BYTE				bySkillGroup;
	bool is_selected;
	char country_flag[3 + 1];
} TSimplePlayerInformation;

typedef struct packet_login_success3
{
	BYTE						header;
	TSimplePlayerInformation	akSimplePlayerInformation[PLAYER_PER_ACCOUNT3];
    DWORD						guild_id[PLAYER_PER_ACCOUNT3];
    char						guild_name[PLAYER_PER_ACCOUNT3][GUILD_NAME_MAX_LEN+1];
	DWORD handle;
	DWORD random_key;
} TPacketGCLoginSuccess3;

typedef struct packet_login_success4
{
	BYTE						header;
	TSimplePlayerInformation	akSimplePlayerInformation[PLAYER_PER_ACCOUNT4];
    DWORD						guild_id[PLAYER_PER_ACCOUNT4];
    char						guild_name[PLAYER_PER_ACCOUNT4][GUILD_NAME_MAX_LEN+1];
	DWORD handle;
	DWORD random_key;
} TPacketGCLoginSuccess4;

#ifdef ENABLE_PLAYER_PER_ACCOUNT5
typedef struct packet_login_success5
{
	BYTE						header;
	TSimplePlayerInformation	akSimplePlayerInformation[PLAYER_PER_ACCOUNT5];
    DWORD						guild_id[PLAYER_PER_ACCOUNT5];
    char						guild_name[PLAYER_PER_ACCOUNT5][GUILD_NAME_MAX_LEN+1];
	DWORD handle;
	DWORD random_key;
} TPacketGCLoginSuccess5;
#endif

enum { LOGIN_STATUS_MAX_LEN = 8 };
typedef struct packet_login_failure
{
	BYTE	header;
	char	szStatus[LOGIN_STATUS_MAX_LEN + 1];
} TPacketGCLoginFailure;

typedef struct command_player_create
{
	BYTE		header;
	BYTE		index;
	char		name[CHARACTER_NAME_MAX_LEN + 1];
	WORD		job;
	BYTE		shape;
	BYTE		CON;
	BYTE		INT;
	BYTE		STR;
	BYTE		DEX;
	char country_flag[3 + 1];
} TPacketCGCreateCharacter;

typedef struct command_player_create_success
{
    BYTE						header;
    BYTE						bAccountCharacterSlot;
    TSimplePlayerInformation	kSimplePlayerInfomation;
} TPacketGCPlayerCreateSuccess;

typedef struct command_create_failure
{
	BYTE	header;
	BYTE	bType;
} TPacketGCCreateFailure;

typedef struct command_player_delete
{
	BYTE        header;
	BYTE        index;
	char		szPrivateCode[PRIVATE_CODE_LENGTH];
} TPacketCGDestroyCharacter;

typedef struct packet_player_delete_success
{
	BYTE        header;
	BYTE        account_index;
} TPacketGCDestroyCharacterSuccess;

enum
{
	ADD_CHARACTER_STATE_DEAD   = (1 << 0),
	ADD_CHARACTER_STATE_SPAWN  = (1 << 1),
	ADD_CHARACTER_STATE_GUNGON = (1 << 2),
	ADD_CHARACTER_STATE_KILLER = (1 << 3),
	ADD_CHARACTER_STATE_PARTY  = (1 << 4),
};

enum EPKModes
{
	PK_MODE_PEACE,
	PK_MODE_REVENGE,
	PK_MODE_FREE,
	PK_MODE_PROTECT,
	PK_MODE_GUILD,
	PK_MODE_MAX_NUM,
};

// 2004.11.20.myevan.CRaceData::PART_MAX_NUM 사용안하게 수정 - 서버에서 사용하는것과 일치하지 않음
enum ECharacterEquipmentPart
{
	CHR_EQUIPPART_ARMOR,
	CHR_EQUIPPART_WEAPON,
	CHR_EQUIPPART_HEAD,
	CHR_EQUIPPART_HAIR,
#ifdef ENABLE_ACCE_SYSTEM
	CHR_EQUIPPART_ACCE,
#endif
#ifdef ENABLE_COSTUME_EFFECT
	CHR_EQUIPPART_EFFECT_BODY,
	CHR_EQUIPPART_EFFECT_WEAPON,
#endif
#if defined(ENABLE_AURA_SYSTEM)
	CHR_EQUIPPART_AURA,
#endif
	CHR_EQUIPPART_NUM,
};

typedef struct packet_char_additional_info
{
	BYTE    header;
	DWORD   dwVID;
	char    name[CHARACTER_NAME_MAX_LEN + 1];
	uint32_t awPart[CHR_EQUIPPART_NUM];
	BYTE	bEmpire;
	DWORD   dwGuildID;
	DWORD   dwLevel;
	short   sAlignment; //선악치
	BYTE    bPKMode;
	DWORD   dwMountVnum;
	
#ifdef ENABLE_PREMIUM_PLAYERS
    BYTE 	byPremium;
    long int iPremiumTime;
#endif
	char country_flag[3 + 1];
	BYTE bGuildLeaderGrade;
} TPacketGCCharacterAdditionalInfo;

typedef struct packet_add_char
{
	BYTE	header;
	DWORD	dwVID;
	float	angle;
	long	x;
	long	y;
	long	z;
	BYTE	bType;
	WORD	wRaceNum;
	WORD	bMovingSpeed;
	WORD	bAttackSpeed;
	BYTE	bStateFlag;
	DWORD	dwAffectFlag[2];
#ifdef ENABLE_MULTI_NAMES
	bool transname;
#endif
} TPacketGCCharacterAdd;

typedef struct packet_add_char2
{
    BYTE        header;

    DWORD       dwVID;

    char        name[CHARACTER_NAME_MAX_LEN + 1];

    float       angle;
    long        x;
    long        y;
    long        z;

	BYTE		bType;
    WORD        wRaceNum;
    uint32_t awPart[CHR_EQUIPPART_NUM];
    WORD        bMovingSpeed;
    WORD        bAttackSpeed;

    BYTE        bStateFlag;
    DWORD       dwAffectFlag[2];        // ??
    BYTE        bEmpire;

    DWORD       dwGuild;
    short       sAlignment;
	BYTE		bPKMode;
	DWORD		dwMountVnum;
	BYTE bGuildLeaderGrade;
} TPacketGCCharacterAdd2;

typedef struct packet_update_char
{
    BYTE        header;
    DWORD       dwVID;

    uint32_t awPart[CHR_EQUIPPART_NUM];
    WORD        bMovingSpeed;
	WORD		bAttackSpeed;

    BYTE        bStateFlag;
    DWORD       dwAffectFlag[2];

	DWORD		dwGuildID;
    short       sAlignment;
	BYTE		bPKMode;
	DWORD		dwMountVnum;
	
#ifdef ENABLE_PREMIUM_PLAYERS
    BYTE 		byPremium;
    long int 	iPremiumTime;
#endif
	BYTE bGuildLeaderGrade;
} TPacketGCCharacterUpdate;

typedef struct packet_update_char2
{
    BYTE        header;
    DWORD       dwVID;

    uint32_t awPart[CHR_EQUIPPART_NUM];
    WORD        bMovingSpeed;
	WORD		bAttackSpeed;

    BYTE        bStateFlag;
    DWORD       dwAffectFlag[2];

	DWORD		dwGuildID;
    short       sAlignment;
	BYTE		bPKMode;
	DWORD		dwMountVnum;
	BYTE bGuildLeaderGrade;
} TPacketGCCharacterUpdate2;

typedef struct packet_del_char
{
	BYTE	header;
    DWORD	dwVID;
} TPacketGCCharacterDelete;

typedef struct packet_GlobalTime
{
	BYTE	header;
	float	GlobalTime;
} TPacketGCGlobalTime;

enum EChatType
{
	CHAT_TYPE_TALKING,  /* 그냥 채팅 */
	CHAT_TYPE_INFO,     /* 정보 (아이템을 집었다, 경험치를 얻었다. 등) */
	CHAT_TYPE_NOTICE,   /* 공지사항 */
	CHAT_TYPE_PARTY,    /* 파티말 */
	CHAT_TYPE_GUILD,    /* 길드말 */
	CHAT_TYPE_COMMAND,	/* 명령 */
	CHAT_TYPE_SHOUT,	/* 외치기 */
	CHAT_TYPE_WHISPER,	// 서버와는 연동되지 않는 Only Client Enum
	CHAT_TYPE_BIG_NOTICE,
#ifdef ENABLE_DICE_SYSTEM
	CHAT_TYPE_DICE_INFO, //11
#endif
#ifdef ENABLE_NEW_CHAT
	CHAT_TYPE_INFO_EXP,
	CHAT_TYPE_INFO_ITEM,
	CHAT_TYPE_INFO_VALUE,
#endif
	CHAT_TYPE_DIALOG,
	CHAT_TYPE_MAX_NUM,
};

typedef struct packet_chatting
{
	BYTE	header;
	WORD	size;
	BYTE	type;
	DWORD	dwVID;
	BYTE	bEmpire;
} TPacketGCChat;

typedef struct packet_whisper   // 가변 패킷
{
	BYTE	bHeader;
	WORD	wSize;
	BYTE	bType;
	char	szNameFrom[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGCWhisper;

typedef struct packet_stun
{
	BYTE		header;
	DWORD		vid;
} TPacketGCStun;

typedef struct packet_dead
{
	BYTE		header;
	DWORD		vid;
} TPacketGCDead;

typedef struct packet_main_character
{
    BYTE        header;
    DWORD       dwVID;
	WORD		wRaceNum;
    char        szName[CHARACTER_NAME_MAX_LEN + 1];
    long        lX, lY, lZ;
	BYTE	empire;
	BYTE		bySkillGroup;
} TPacketGCMainCharacter;

typedef struct packet_main_character3_bgm
{
	enum
	{
		MUSIC_NAME_MAX_LEN = 24,
	};
    BYTE        header;
    DWORD       dwVID;
	WORD		wRaceNum;
    char        szUserName[CHARACTER_NAME_MAX_LEN + 1];
	char        szBGMName[MUSIC_NAME_MAX_LEN + 1];
    long        lX, lY, lZ;
	BYTE		byEmpire;
	BYTE		bySkillGroup;
} TPacketGCMainCharacter3_BGM;

typedef struct packet_main_character4_bgm_vol
{
	enum
	{
		MUSIC_NAME_MAX_LEN = 24,
	};
    BYTE        header;
    DWORD       dwVID;
	WORD		wRaceNum;
    char        szUserName[CHARACTER_NAME_MAX_LEN + 1];
	char        szBGMName[MUSIC_NAME_MAX_LEN + 1];
	float		fBGMVol;
    long        lX, lY, lZ;
	BYTE		byEmpire;
	BYTE		bySkillGroup;
} TPacketGCMainCharacter4_BGM_VOL;
// END_OF_SUPPORT_BGM

enum EPointTypes
{
	POINT_NONE,
	POINT_LEVEL,
	POINT_VOICE,
	POINT_EXP,
	POINT_NEXT_EXP,
	POINT_HP,
	POINT_MAX_HP,
	POINT_SP,
	POINT_MAX_SP,
	POINT_STAMINA,
	POINT_MAX_STAMINA,
	POINT_GOLD,
	POINT_ST,
	POINT_HT,
	POINT_DX,
	POINT_IQ,
	POINT_ATT_POWER,
	POINT_ATT_SPEED,
	POINT_EVADE_RATE,
	POINT_MOV_SPEED,
	POINT_DEF_GRADE,
	POINT_CASTING_SPEED,
	POINT_MAGIC_ATT_GRADE,
	POINT_MAGIC_DEF_GRADE,
	POINT_EMPIRE_POINT,
	POINT_LEVEL_STEP,
	POINT_STAT,
	POINT_SUB_SKILL,
	POINT_SKILL,
	POINT_MIN_ATK,
	POINT_MAX_ATK,
	POINT_PLAYTIME,
	POINT_HP_REGEN,
	POINT_SP_REGEN,
	POINT_BOW_DISTANCE,
	POINT_HP_RECOVERY,
	POINT_SP_RECOVERY,
	POINT_POISON_PCT,
	POINT_STUN_PCT,
	POINT_SLOW_PCT,
	POINT_CRITICAL_PCT,
	POINT_PENETRATE_PCT,
	POINT_CURSE_PCT,
	POINT_ATTBONUS_HUMAN,
	POINT_ATTBONUS_ANIMAL,
	POINT_ATTBONUS_ORC,
	POINT_ATTBONUS_MILGYO,
	POINT_ATTBONUS_UNDEAD,
	POINT_ATTBONUS_DEVIL,
	POINT_ATTBONUS_INSECT,
	POINT_ATTBONUS_FIRE,
	POINT_ATTBONUS_ICE,
	POINT_ATTBONUS_DESERT,
	POINT_ATTBONUS_MONSTER,
	POINT_ATTBONUS_WARRIOR,
	POINT_ATTBONUS_ASSASSIN,
	POINT_ATTBONUS_SURA,
	POINT_ATTBONUS_SHAMAN,
	POINT_ATTBONUS_UNUSED5,
	POINT_RESIST_WARRIOR,
	POINT_RESIST_ASSASSIN,
	POINT_RESIST_SURA,
	POINT_RESIST_SHAMAN,
	POINT_STEAL_HP,
	POINT_STEAL_SP,
	POINT_MANA_BURN_PCT,
	POINT_DAMAGE_SP_RECOVER,
	POINT_BLOCK,
	POINT_DODGE,
	POINT_RESIST_SWORD,
	POINT_RESIST_TWOHAND,
	POINT_RESIST_DAGGER,
	POINT_RESIST_BELL,
	POINT_RESIST_FAN,
	POINT_RESIST_BOW,
	POINT_RESIST_FIRE,
	POINT_RESIST_ELEC,
	POINT_RESIST_MAGIC,
	POINT_RESIST_WIND,
	POINT_REFLECT_MELEE,
	POINT_REFLECT_CURSE,
	POINT_POISON_REDUCE,
	POINT_KILL_SP_RECOVER,
	POINT_EXP_DOUBLE_BONUS,
	POINT_GOLD_DOUBLE_BONUS,
	POINT_ITEM_DROP_BONUS,
	POINT_POTION_BONUS,
	POINT_KILL_HP_RECOVER,
	POINT_IMMUNE_STUN,
	POINT_IMMUNE_SLOW,
	POINT_IMMUNE_FALL,
	POINT_PARTY_ATT_GRADE,
	POINT_PARTY_DEF_GRADE,
	POINT_ATT_BONUS,
	POINT_DEF_BONUS,
	POINT_ATT_GRADE_BONUS,
	POINT_DEF_GRADE_BONUS,
	POINT_MAGIC_ATT_GRADE_BONUS,
	POINT_MAGIC_DEF_GRADE_BONUS,
	POINT_RESIST_NORMAL_DAMAGE,
	POINT_STAT_RESET_COUNT = 112,
	POINT_HORSE_SKILL = 113,
	POINT_MALL_ATTBONUS,
	POINT_MALL_DEFBONUS,
	POINT_MALL_EXPBONUS,
	POINT_MALL_ITEMBONUS,
	POINT_MALL_GOLDBONUS,
	POINT_MAX_HP_PCT,
	POINT_MAX_SP_PCT,
	POINT_SKILL_DAMAGE_BONUS,
	POINT_NORMAL_HIT_DAMAGE_BONUS,
	POINT_SKILL_DEFEND_BONUS,
	POINT_NORMAL_HIT_DEFEND_BONUS,
	POINT_PC_UNUSED01,
	POINT_PC_UNUSED02,
	POINT_ENERGY = 128,
	POINT_ENERGY_END_TIME = 129,
	POINT_COSTUME_ATTR_BONUS = 130,
	POINT_MAGIC_ATT_BONUS_PER = 131,
	POINT_MELEE_MAGIC_ATT_BONUS_PER = 132,
	POINT_RESIST_ICE = 133,
	POINT_RESIST_EARTH = 134,
	POINT_RESIST_DARK = 135,
	POINT_RESIST_CRITICAL = 136,
	POINT_RESIST_PENETRATE = 137,
#if defined(ENABLE_APPLY_MAGICRES_REDUCTION)
	POINT_RESIST_MAGIC_REDUCTION = 144,
#endif
#ifdef ELEMENT_NEW_BONUSES
	POINT_ATTBONUS_ELEC = 146,	// 146
	POINT_ATTBONUS_WIND,	// 147
	POINT_ATTBONUS_EARTH,	// 148
	POINT_ATTBONUS_DARK,	// 149
#endif
#ifdef ENABLE_NEW_BONUS_TALISMAN
	POINT_ATTBONUS_IRR_SPADA = 150,
	POINT_ATTBONUS_IRR_SPADONE = 151,
	POINT_ATTBONUS_IRR_PUGNALE = 152,
	POINT_ATTBONUS_IRR_FRECCIA = 153,
	POINT_ATTBONUS_IRR_VENTAGLIO = 154,
	POINT_ATTBONUS_IRR_CAMPANA = 155,
	POINT_RESIST_MEZZIUOMINI = 156,
	POINT_DEF_TALISMAN = 157,
	POINT_ATTBONUS_FORT_ZODIAC = 158,
#endif
#ifdef ENABLE_STRONG_METIN
	POINT_ATTBONUS_METIN = 159,
#endif
#ifdef ENABLE_STRONG_BOSS
	POINT_ATTBONUS_BOSS	= 160,
#endif
#ifdef ENABLE_RESIST_MONSTER
	POINT_RESIST_MONSTER = 161,
#endif
#ifdef ENABLE_MEDI_PVM
	POINT_ATTBONUS_MEDI_PVM	= 162,
#endif
#if defined(ENABLE_GAYA_RENEWAL)
	POINT_GEM = 163,
#endif
	POINT_PVM_CRITICAL_PCT = 170,
#ifdef ENABLE_NEW_COMMON_BONUSES
	POINT_DOUBLE_DROP_ITEM = 172,
	POINT_IRR_WEAPON_DEFENSE = 173,
#endif
	POINT_FISHING_RARE = 174,
#ifdef ENABLE_NEW_USE_POTION
	POINT_PARTY_DROPEXP = 175,
#endif
#if defined(USE_BATTLEPASS)
	POINT_BATTLE_PASS_ID = 176,
#endif
#if defined(USE_MOUNT_COSTUME_SYSTEM)
	POINT_MOUNT = 183,
#endif
#ifdef ENABLE_HALLOWEEN_EVENT_2022
#ifndef USE_NO_HALLOWEEN_EVENT_2022_BONUSES
    POINT_FEAR                      = 188,
    POINT_RESISTANCE_FEAR           = 189,
#endif
    POINT_SKULL                     = 190,
#endif
	POINT_ATT_RACES = 184,
	POINT_RES_RACES = 185,
#if defined(ENABLE_WORLDBOSS)
	POINT_WB_POINTS = 191,
#endif
	POINT_MIN_WEP = 200,
	POINT_MAX_WEP,
	POINT_MIN_MAGIC_WEP,
	POINT_MAX_MAGIC_WEP,
	POINT_HIT_RATE,
};

typedef struct packet_points
{
	uint8_t header;
	int32_t points[POINT_MAX_NUM];
} TPacketGCPoints;

typedef struct packet_point_change
{
	uint8_t header;
	uint32_t dwVID;
	uint8_t Type;
	long amount;
	long value;
} TPacketGCPointChange;

typedef struct packet_motion
{
	BYTE		header;
	DWORD		vid;
	DWORD		victim_vid;
	WORD		motion;
} TPacketGCMotion;

#if defined(GAIDEN)
struct TPacketGCItemDelDeprecate
{
	TPacketGCItemDelDeprecate() :
		header(HEADER_GC_ITEM_DEL),
		pos(0),
		vnum(0),
		count(0)
	{
		memset(&alSockets, 0, sizeof(alSockets));
		memset(&aAttr, 0, sizeof(aAttr));
	}
	
	BYTE					header;
	BYTE					pos;
	DWORD					vnum;
	WORD count;
	long					alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
	TPlayerItemAttribute	aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
};

typedef struct packet_set_item
{
	BYTE		header;
	BYTE		pos;
	DWORD		vnum;
	WORD count;
	DWORD		flags;
	long		alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
	TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
} TPacketGCItemSet;

typedef struct packet_item_del
{
    BYTE        header;
    BYTE        pos;
} TPacketGCItemDel;
#else
typedef struct packet_set_item
{
	BYTE		header;
	TItemPos	Cell;
	DWORD		vnum;
	WORD			count;
	long		alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
	TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
#if defined(ENABLE_CHANGELOOK)
	uint32_t transmutation;
#endif
#ifdef ATTR_LOCK
	short	lockedattr;
#endif
} TPacketGCItemSet;

typedef struct packet_set_item2
{
	BYTE		header;
	TItemPos	Cell;
	DWORD		vnum;
	WORD			count;
	DWORD		flags;
	DWORD		anti_flags;
	bool		highlight;
	long		alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
	TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
#if defined(ENABLE_CHANGELOOK)
	uint32_t transmutation;
#endif
#ifdef ATTR_LOCK
	short	lockedattr;
#endif
} TPacketGCItemSet2;
#endif

typedef struct packet_item_del
{
    BYTE        header;
    BYTE        pos;
} TPacketGCItemDel;

typedef struct packet_use_item
{
	BYTE		header;
	TItemPos	Cell;
	DWORD		ch_vid;
	DWORD		victim_vid;

	DWORD		vnum;
} TPacketGCItemUse;

typedef struct packet_update_item
{
	BYTE		header;
	TItemPos	Cell;
	WORD			count;
	long		alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
	TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
#if defined(ENABLE_CHANGELOOK)
	uint32_t transmutation;
#endif
#ifdef ATTR_LOCK
	short	lockedattr;
#endif
} TPacketGCItemUpdate;

typedef struct packet_ground_add_item
{
    BYTE        bHeader;
    long        lX;
	long		lY;
	long		lZ;

    DWORD       dwVID;
    DWORD       dwVnum;
} TPacketGCItemGroundAdd;

typedef struct packet_ground_del_item
{
	BYTE		header;
	DWORD		vid;
} TPacketGCItemGroundDel;

typedef struct packet_item_ownership
{
    BYTE        bHeader;
    DWORD       dwVID;
    char        szName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGCItemOwnership;

typedef struct packet_shop_start
{
	struct packet_shop_item		items[SHOP_HOST_ITEM_MAX_NUM];
} TPacketGCShopStart;

typedef struct packet_shop_start_ex // 다음에 TSubPacketShopTab* shop_tabs 이 따라옴.
{
	typedef struct sub_packet_shop_tab
	{
		char name[SHOP_TAB_NAME_MAX];
		BYTE coin_type;
		packet_shop_item items[SHOP_HOST_ITEM_MAX_NUM];
	} TSubPacketShopTab;
	DWORD owner_vid;
	BYTE shop_tab_count;
} TPacketGCShopStartEx;


typedef struct packet_shop_update_item
{
	BYTE						pos;
	struct packet_shop_item		item;
} TPacketGCShopUpdateItem;

typedef struct packet_shop_update_price
{
#if defined(ENABLE_NEW_GOLD_LIMIT)
	uint64_t iElkAmount;
#else
	uint32_t iElkAmount;
#endif
} TPacketGCShopUpdatePrice;

enum EPacketShopSubHeaders
{
	SHOP_SUBHEADER_GC_START,
	SHOP_SUBHEADER_GC_END,
	SHOP_SUBHEADER_GC_UPDATE_ITEM,
	SHOP_SUBHEADER_GC_UPDATE_PRICE,
	SHOP_SUBHEADER_GC_OK,
	SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY,
#ifdef ENABLE_BUY_WITH_ITEM
	SHOP_SUBHEADER_GC_NOT_ENOUGH_ITEM,
#endif
#if defined(ENABLE_WORLDBOSS)
	SHOP_SUBHEADER_GC_NOT_ENOUGH_WB_POINTS,
#endif
#if defined(ENABLE_HALLOWEEN_EVENT_2022)
	SHOP_SUBHEADER_GC_NOT_ENOUGH_SKULLS,
#endif
	SHOP_SUBHEADER_GC_SOLDOUT,
	SHOP_SUBHEADER_GC_INVENTORY_FULL,
	SHOP_SUBHEADER_GC_INVALID_POS,
	SHOP_SUBHEADER_GC_SOLD_OUT,
	SHOP_SUBHEADER_GC_START_EX,
	SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY_EX,
};

typedef struct packet_shop
{
	BYTE        header;
	WORD		size;
	BYTE        subheader;
} TPacketGCShop;

typedef struct packet_exchange
{
    BYTE        header;
    BYTE        subheader;
    BYTE        is_me;
#if defined(ENABLE_NEW_GOLD_LIMIT)
	uint64_t arg1;
#else
	uint32_t arg1;
#endif
    TItemPos       arg2;
    DWORD       arg3;
#ifdef WJ_ENABLE_TRADABLE_ICON
    TItemPos       arg4;
#endif
	long		alValues[ITEM_SOCKET_SLOT_MAX_NUM];
    TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
#if defined(ENABLE_CHANGELOOK)
	uint32_t transmutation;
#endif
#ifdef ATTR_LOCK
	short	lockedattr;
#endif
} TPacketGCExchange;

enum
{
    EXCHANGE_SUBHEADER_GC_START,			// arg1 == vid
    EXCHANGE_SUBHEADER_GC_ITEM_ADD,		// arg1 == vnum  arg2 == pos  arg3 == count
	EXCHANGE_SUBHEADER_GC_ITEM_DEL,		// arg1 == pos
    EXCHANGE_SUBHEADER_GC_ELK_ADD,			// arg1 == elk
    EXCHANGE_SUBHEADER_GC_ACCEPT,			// arg1 == accept
    EXCHANGE_SUBHEADER_GC_END,				// arg1 == not used
    EXCHANGE_SUBHEADER_GC_ALREADY,			// arg1 == not used
    EXCHANGE_SUBHEADER_GC_LESS_ELK,		// arg1 == not used
};

typedef struct packet_position
{
    BYTE        header;
	DWORD		vid;
    BYTE        position;
} TPacketGCPosition;

typedef struct packet_ping
{
	BYTE		header;
} TPacketGCPing;

typedef struct packet_pong
{
	BYTE		bHeader;
} TPacketCGPong;

typedef struct packet_script
{
    BYTE		header;
    WORD        size;
	BYTE		skin;
    WORD        src_size;
} TPacketGCScript;

typedef struct packet_target
{
    BYTE        header;
    DWORD       dwVID;
    BYTE        bHPPercent;
#ifdef ENABLE_VIEW_TARGET_DECIMAL_HP
	int		iMinHP;
	int		iMaxHP;
#endif
#ifdef ENABLE_VIEW_ELEMENT
	BYTE	bElement;
#endif
} TPacketGCTarget;

typedef struct packet_damage_info
{
	BYTE header;
	DWORD dwVID;
	BYTE flag;
	int  damage;
} TPacketGCDamageInfo;

typedef struct packet_mount
{
    BYTE        header;
    DWORD       vid;
    DWORD       mount_vid;
    BYTE        pos;
	DWORD		_x, _y;
} TPacketGCMount;

typedef struct packet_change_speed
{
	BYTE		header;
	DWORD		vid;
	WORD		moving_speed;
} TPacketGCChangeSpeed;

typedef struct packet_move
{
	BYTE		bHeader;
	BYTE		bFunc;
	BYTE		bArg;
	BYTE		bRot;
	DWORD		dwVID;
	LONG		lX;
	LONG		lY;
	DWORD		dwTime;
	DWORD		dwDuration;
} TPacketGCMove;

enum
{
	QUEST_SEND_IS_BEGIN         = 1 << 0,
    QUEST_SEND_TITLE            = 1 << 1,  // 28자 까지
    QUEST_SEND_CLOCK_NAME       = 1 << 2,  // 16자 까지
    QUEST_SEND_CLOCK_VALUE      = 1 << 3,
    QUEST_SEND_COUNTER_NAME     = 1 << 4,  // 16자 까지
    QUEST_SEND_COUNTER_VALUE    = 1 << 5,
	QUEST_SEND_ICON_FILE		= 1 << 6,  // 24자 까지
};

typedef struct packet_quest_info
{
	BYTE header;
	WORD size;
	WORD index;
	BYTE flag;
	char	szTitle[30 + 1];
	BYTE	isBegin;
	char	szClockName[16 + 1];
	int		iClockValue;
	char	szCounterName[16 + 1];
	int		iCounterValue;
	char	szIconFileName[24 + 1];
} TPacketGCQuestInfo;

typedef struct packet_quest_confirm
{
    BYTE header;
    char msg[64+1];
    long timeout;
    DWORD requestPID;
} TPacketGCQuestConfirm;

typedef struct packet_attack
{
    BYTE        header;
    DWORD       dwVID;
    DWORD       dwVictimVID;    // 적 VID
    BYTE        bType;          // 공격 유형
} TPacketGCAttack;
typedef struct packet_c2c
{
	BYTE		header;
	WORD		wSize;
} TPacketGCC2C;

typedef struct packetd_sync_position_element
{
    DWORD       dwVID;
    long        lX;
    long        lY;
} TPacketGCSyncPositionElement;

typedef struct packetd_sync_position
{
    BYTE        bHeader;
    WORD		wSize;
} TPacketGCSyncPosition;

typedef struct packet_ownership
{
    BYTE                bHeader;
    DWORD               dwOwnerVID;
    DWORD               dwVictimVID;
} TPacketGCOwnership;

#define	SKILL_MAX_NUM 255

typedef struct packet_skill_level
{
    BYTE        bHeader;
    BYTE        abSkillLevels[SKILL_MAX_NUM];
} TPacketGCSkillLevel;

typedef struct SPlayerSkill
{
	BYTE bMasterType;
	BYTE bLevel;
	time_t tNextRead;
} TPlayerSkill;

typedef struct packet_skill_level_new
{
	BYTE bHeader;
	TPlayerSkill skills[SKILL_MAX_NUM];
} TPacketGCSkillLevelNew;

// fly
typedef struct packet_fly
{
    BYTE        bHeader;
    BYTE        bType;
    DWORD       dwStartVID;
    DWORD       dwEndVID;
} TPacketGCCreateFly;

enum EPVPModes
{
	PVP_MODE_NONE,
    PVP_MODE_AGREE,
    PVP_MODE_FIGHT,
    PVP_MODE_REVENGE,
};

typedef struct packet_duel_start
{
    BYTE	header ;
    WORD	wSize ;	// DWORD가 몇개? 개수 = (wSize - sizeof(TPacketGCPVPList)) / 4
} TPacketGCDuelStart ;

typedef struct packet_pvp
{
	BYTE		header;
	DWORD		dwVIDSrc;
	DWORD		dwVIDDst;
	BYTE		bMode;
} TPacketGCPVP;

typedef struct packet_skill_cooltime_end
{
	BYTE		header;
	BYTE		bSkill;
} TPacketGCSkillCoolTimeEnd;

typedef struct packet_warp
{
	BYTE			bHeader;
	LONG			lX;
	LONG			lY;
	LONG			lAddr;
	WORD			wPort;
} TPacketGCWarp;

typedef struct packet_party_invite
{
    BYTE header;
    DWORD leader_pid;
} TPacketGCPartyInvite;

typedef struct packet_party_add
{
    BYTE header;
    DWORD pid;
    char name[CHARACTER_NAME_MAX_LEN+1];
} TPacketGCPartyAdd;

typedef struct packet_party_update
{
    BYTE header;
    DWORD pid;
    BYTE state;
    BYTE percent_hp;
    short affects[PARTY_AFFECT_SLOT_MAX_NUM];
} TPacketGCPartyUpdate;

typedef struct packet_party_remove
{
    BYTE header;
    DWORD pid;
} TPacketGCPartyRemove;

typedef TPacketCGSafeboxCheckout TPacketGCSafeboxCheckout;
typedef TPacketCGSafeboxCheckin TPacketGCSafeboxCheckin;

typedef struct packet_safebox_wrong_password
{
    BYTE        bHeader;
} TPacketGCSafeboxWrongPassword;

typedef struct packet_safebox_size
{
	BYTE bHeader;
	BYTE bSize;
} TPacketGCSafeboxSize;

typedef struct packet_safebox_money_change
{
    BYTE bHeader;
    DWORD dwMoney;
} TPacketGCSafeboxMoneyChange;

typedef struct command_empire
{
    BYTE        bHeader;
    BYTE        bEmpire;
} TPacketCGEmpire;

typedef struct packet_empire
{
    BYTE        bHeader;
    BYTE        bEmpire;
} TPacketGCEmpire;

enum
{
	FISHING_SUBHEADER_GC_START,
	FISHING_SUBHEADER_GC_STOP,
	FISHING_SUBHEADER_GC_REACT,
	FISHING_SUBHEADER_GC_SUCCESS,
	FISHING_SUBHEADER_GC_FAIL,
    FISHING_SUBHEADER_GC_FISH,
};

typedef struct packet_fishing
{
    BYTE header;
    BYTE subheader;
    DWORD info;
    BYTE dir;
} TPacketGCFishing;

typedef struct paryt_parameter
{
    BYTE        bHeader;
    BYTE        bDistributeMode;
} TPacketGCPartyParameter;

//////////////////////////////////////////////////////////////////////////
// Guild

enum
{
    GUILD_SUBHEADER_GC_LOGIN,
	GUILD_SUBHEADER_GC_LOGOUT,
	GUILD_SUBHEADER_GC_LIST,
	GUILD_SUBHEADER_GC_GRADE,
	GUILD_SUBHEADER_GC_ADD,
	GUILD_SUBHEADER_GC_REMOVE,
	GUILD_SUBHEADER_GC_GRADE_NAME,
	GUILD_SUBHEADER_GC_GRADE_AUTH,
	GUILD_SUBHEADER_GC_INFO,
	GUILD_SUBHEADER_GC_COMMENTS,
    GUILD_SUBHEADER_GC_CHANGE_EXP,
    GUILD_SUBHEADER_GC_CHANGE_MEMBER_GRADE,
	GUILD_SUBHEADER_GC_SKILL_INFO,
	GUILD_SUBHEADER_GC_CHANGE_MEMBER_GENERAL,
	GUILD_SUBHEADER_GC_GUILD_INVITE,
    GUILD_SUBHEADER_GC_WAR,
    GUILD_SUBHEADER_GC_GUILD_NAME,
    GUILD_SUBHEADER_GC_GUILD_WAR_LIST,
    GUILD_SUBHEADER_GC_GUILD_WAR_END_LIST,
    GUILD_SUBHEADER_GC_WAR_POINT,
	GUILD_SUBHEADER_GC_MONEY_CHANGE,
	GUILD_SUBHEADER_GC_SYMBOL_AUTH_DATA,
	GUILD_SUBHEADER_GC_SYMBOL_LOGIN,
};

typedef struct packet_guild
{
    BYTE header;
    WORD size;
    BYTE subheader;
} TPacketGCGuild;

// SubHeader - Grade
enum
{
    GUILD_AUTH_ADD_MEMBER       = (1 << 0),
    GUILD_AUTH_REMOVE_MEMBER    = (1 << 1),
    GUILD_AUTH_NOTICE           = (1 << 2),
    GUILD_AUTH_SKILL            = (1 << 3),
};

typedef struct packet_guild_sub_grade
{
	char grade_name[GUILD_GRADE_NAME_MAX_LEN+1]; // 8+1 길드장, 길드원 등의 이름
	BYTE auth_flag;
} TPacketGCGuildSubGrade;

typedef struct packet_guild_sub_member
{
	DWORD pid;
	BYTE byGrade;
	BYTE byIsGeneral;
	BYTE byJob;
	BYTE byLevel;
	DWORD dwOffer;
	BYTE byNameFlag;
// if NameFlag is TRUE, name is sent from server.
//	char szName[CHARACTER_ME_MAX_LEN+1];
} TPacketGCGuildSubMember;

typedef struct packet_guild_sub_info
{
    WORD member_count;
    WORD max_member_count;
	DWORD guild_id;
    DWORD master_pid;
    DWORD exp;
    BYTE level;
    char name[GUILD_NAME_MAX_LEN+1];
	DWORD gold;
	BYTE hasLand;
} TPacketGCGuildInfo;

enum EGuildWarState
{
    GUILD_WAR_NONE,
    GUILD_WAR_SEND_DECLARE,
    GUILD_WAR_REFUSE,
    GUILD_WAR_RECV_DECLARE,
    GUILD_WAR_WAIT_START,
    GUILD_WAR_CANCEL,
    GUILD_WAR_ON_WAR,
    GUILD_WAR_END,

    GUILD_WAR_DURATION = 2*60*60, // 2시간
};

typedef struct packet_guild_war
{
    DWORD       dwGuildSelf;
    DWORD       dwGuildOpp;
    BYTE        bType;
    BYTE        bWarState;
} TPacketGCGuildWar;

typedef struct SPacketGuildWarPoint
{
    DWORD dwGainGuildID;
    DWORD dwOpponentGuildID;
    long lPoint;
} TPacketGuildWarPoint;

typedef struct packet_guild_symbol_auth
{
	uint8_t nonce[24];
	uint8_t ciphertext[32];
} TPacketGuildSymbolAuth;

// SubHeader - Dungeon
enum
{
	DUNGEON_SUBHEADER_GC_TIME_ATTACK_START = 0,
	DUNGEON_SUBHEADER_GC_DESTINATION_POSITION = 1,
};

typedef struct packet_dungeon
{
	BYTE		bHeader;
    WORD		size;
    BYTE		subheader;
} TPacketGCDungeon;

// Private Shop
typedef struct SPacketGCShopSign
{
	BYTE	bHeader;
	DWORD	dwVID;
	char	szSign[SHOP_SIGN_MAX_LEN + 1];
} TPacketGCShopSign;

typedef struct SPacketGCTime
{
    BYTE        bHeader;
    time_t      time;
} TPacketGCTime;

enum
{
    WALKMODE_RUN,
    WALKMODE_WALK,
};

typedef struct SPacketGCWalkMode
{
    BYTE        header;
    DWORD       vid;
    BYTE        mode;
} TPacketGCWalkMode;

typedef struct SPacketGCChangeSkillGroup
{
    BYTE        header;
    BYTE        skill_group;
} TPacketGCChangeSkillGroup;

typedef struct SRefineMaterial
{
	uint32_t vnum;
	uint16_t count;
} TRefineMaterial;

typedef struct SRefineTable
{
	uint32_t src_vnum;
	uint32_t result_vnum;
	uint8_t material_count;
#if defined(ENABLE_NEW_GOLD_LIMIT)
	uint64_t cost;
#else
	uint32_t cost;
#endif
	uint8_t prob;
	TRefineMaterial materials[REFINE_MATERIAL_MAX_NUM];
} TRefineTable;

typedef struct SPacketGCRefineInformation
{
	uint8_t header;
	uint8_t type;
	uint8_t pos;
	TRefineTable refine_table;
} TPacketGCRefineInformation;

enum SPECIAL_EFFECT
{
	SE_NONE,
	SE_HPUP_RED,
	SE_SPUP_BLUE,
	SE_SPEEDUP_GREEN,
	SE_DXUP_PURPLE,
	SE_CRITICAL,
	SE_PENETRATE,
	SE_BLOCK,
	SE_DODGE,
	SE_CHINA_FIREWORK,
	SE_SPIN_TOP,
	SE_SUCCESS,
	SE_FAIL,
	SE_FR_SUCCESS,
    SE_LEVELUP_ON_14_FOR_GERMANY,	//레벨업 14일때 ( 독일전용 )
    SE_LEVELUP_UNDER_15_FOR_GERMANY,//레벨업 15일때 ( 독일전용 )
    SE_PERCENT_DAMAGE1,
    SE_PERCENT_DAMAGE2,
    SE_PERCENT_DAMAGE3,
	SE_AUTO_HPUP,
	SE_AUTO_SPUP,
	SE_EQUIP_RAMADAN_RING,			// 초승달의 반지를 착용하는 순간에 발동하는 이펙트
	SE_EQUIP_HALLOWEEN_CANDY,		// 할로윈 사탕을 착용(-_-;)한 순간에 발동하는 이펙트
	SE_EQUIP_HAPPINESS_RING,		// 크리스마스 행복의 반지를 착용하는 순간에 발동하는 이펙트
	SE_EQUIP_LOVE_PENDANT,		// 발렌타인 사랑의 팬던트(71145) 착용할 때 이펙트 (발동이펙트임, 지속이펙트 아님)
#ifdef ENABLE_ACCE_SYSTEM
	SE_EFFECT_ACCE_SUCCEDED,
	SE_EFFECT_ACCE_EQUIP,
#endif
#ifdef VERSION_162_ENABLED
	SE_EFFECT_HEALER,
#endif
#ifdef __EFFETTO_MANTELLO__
	SE_MANTELLO,
#endif
#if defined(USE_BATTLEPASS)
	SE_EFFECT_BP_MISSION_COMPLETED,
	SE_EFFECT_BP_COMPLETED,
#endif
};

typedef struct SPacketGCSpecialEffect
{
    BYTE header;
    BYTE type;
    DWORD vid;
} TPacketGCSpecialEffect;

typedef struct SPacketGCNPCPosition
{
    BYTE header;
	WORD size;
    WORD count;
} TPacketGCNPCPosition;

struct TNPCPosition
{
    BYTE bType;
#ifdef ENABLE_MULTI_NAMES
	DWORD	name;
#else
	char	name[CHARACTER_NAME_MAX_LEN+1];
#endif
    long x;
    long y;
};

typedef struct SPacketGCChangeName
{
    BYTE header;
    DWORD pid;
    char name[CHARACTER_NAME_MAX_LEN+1];
} TPacketGCChangeName;

enum EBlockAction
{
    BLOCK_EXCHANGE              = (1 << 0),
    BLOCK_PARTY_INVITE          = (1 << 1),
    BLOCK_GUILD_INVITE          = (1 << 2),
    BLOCK_WHISPER               = (1 << 3),
    BLOCK_MESSENGER_INVITE      = (1 << 4),
    BLOCK_PARTY_REQUEST         = (1 << 5),
};

typedef struct packet_login_key
{
	BYTE	bHeader;
	DWORD	dwLoginKey;
} TPacketGCLoginKey;

typedef struct packet_auth_success
{
	BYTE		bHeader;
	DWORD		dwLoginKey;
	BYTE		bResult;
} TPacketGCAuthSuccess;

typedef struct packet_channel
{
    BYTE header;
    BYTE channel;
} TPacketGCChannel;

typedef struct SEquipmentItemSet
{
	uint16_t				pos;
	uint32_t				vnum;
	uint16_t				count;
	long					alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
	TPlayerItemAttribute	aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
} TEquipmentItemSet;

typedef struct packet_view_equip
{
	uint8_t				bHeader;
	uint32_t			dwVid;
	TEquipmentItemSet	tEquip[23];
} TPacketViewEquip;

typedef struct
{
    DWORD       dwID;
    long        x, y;
    long        width, height;
    DWORD       dwGuildID;
} TLandPacketElement;

typedef struct packet_land_list
{
    BYTE        header;
    WORD        size;
} TPacketGCLandList;

typedef struct
{
    BYTE        bHeader;
    long        lID;
    char        szTargetName[32+1];
} TPacketGCTargetCreate;

enum
{
	CREATE_TARGET_TYPE_NONE,
	CREATE_TARGET_TYPE_LOCATION,
	CREATE_TARGET_TYPE_CHARACTER,
};

typedef struct
{
	BYTE		bHeader;
	long		lID;
	char		szTargetName[32+1];
	DWORD		dwVID;
	BYTE		byType;
} TPacketGCTargetCreateNew;

typedef struct
{
    BYTE        bHeader;
    long        lID;
    long        lX, lY;
} TPacketGCTargetUpdate;

typedef struct
{
    BYTE        bHeader;
    long        lID;
} TPacketGCTargetDelete;

typedef struct
{
    DWORD       dwType;
    BYTE        bPointIdxApplyOn;
    long        lApplyValue;
    DWORD       dwFlag;
    long        lDuration;
    long        lSPCost;
} TPacketAffectElement;

typedef struct
{
    BYTE bHeader;
    TPacketAffectElement elem;
} TPacketGCAffectAdd;

typedef struct
{
    BYTE bHeader;
    DWORD dwType;
    BYTE bApplyOn;
} TPacketGCAffectRemove;

typedef struct packet_mall_open
{
	BYTE bHeader;
	BYTE bSize;
} TPacketGCMallOpen;

typedef struct packet_lover_info
{
	BYTE bHeader;
	char szName[CHARACTER_NAME_MAX_LEN + 1];
	BYTE byLovePoint;
} TPacketGCLoverInfo;

typedef struct packet_love_point_update
{
	BYTE bHeader;
	BYTE byLovePoint;
} TPacketGCLovePointUpdate;

typedef struct packet_dig_motion
{
    BYTE header;
    DWORD vid;
    DWORD target_vid;
	BYTE count;
} TPacketGCDigMotion;

typedef struct SPacketGCOnTime
{
    BYTE header;
    int ontime;     // sec
} TPacketGCOnTime;

typedef struct SPacketGCResetOnTime
{
    BYTE header;
} TPacketGCResetOnTime;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Client To Client

typedef struct packet_state
{
	BYTE			bHeader;
	BYTE			bFunc;
	BYTE			bArg;
	BYTE			bRot;
	DWORD			dwVID;
	DWORD			dwTime;
	TPixelPosition	kPPos;
} TPacketCCState;

// AUTOBAN
typedef struct packet_autoban_quiz
{
    BYTE bHeader;
	BYTE bDuration;
    BYTE bCaptcha[64*32];
    char szQuiz[256];
} TPacketGCAutoBanQuiz;
// END_OF_AUTOBAN

#ifdef _IMPROVED_PACKET_ENCRYPTION_
struct TPacketKeyAgreement
{
	static const int MAX_DATA_LEN = 512;
	BYTE bHeader;
	WORD wAgreedLength;
	WORD wDataLength;
	BYTE data[MAX_DATA_LEN];
};

struct TPacketKeyAgreementCompleted
{
	BYTE bHeader;
	BYTE data[3]; // dummy (not used)
};
#endif // _IMPROVED_PACKET_ENCRYPTION_

#ifdef __AUCTION__
// Argument의 용도는 cmd에 따라 다르다.
typedef struct SPacketCGAuctionCmd
{
	BYTE bHeader;
	BYTE cmd;
	int arg1;
	int arg2;
	int arg3;
	int arg4;
} TPacketCGAuctionCmd;

typedef struct SPacketGCAuctionItemListPack
{
	BYTE bHeader;
	BYTE bNumbers;
} TPacketGCAuctionItemListPack;

#endif

typedef struct SPacketGCSpecificEffect
{
	BYTE header;
	DWORD vid;
	char effect_file[128];
} TPacketGCSpecificEffect;

// 용혼석
enum EDragonSoulRefineWindowRefineType
{
	DragonSoulRefineWindow_UPGRADE,
	DragonSoulRefineWindow_IMPROVEMENT,
	DragonSoulRefineWindow_REFINE,
};

enum EPacketCGDragonSoulSubHeaderType
{
	DS_SUB_HEADER_OPEN,
	DS_SUB_HEADER_CLOSE,
	DS_SUB_HEADER_DO_UPGRADE,
	DS_SUB_HEADER_DO_IMPROVEMENT,
	DS_SUB_HEADER_DO_REFINE,
	DS_SUB_HEADER_REFINE_FAIL,
	DS_SUB_HEADER_REFINE_FAIL_MAX_REFINE,
	DS_SUB_HEADER_REFINE_FAIL_INVALID_MATERIAL,
	DS_SUB_HEADER_REFINE_FAIL_NOT_ENOUGH_MONEY,
	DS_SUB_HEADER_REFINE_FAIL_NOT_ENOUGH_MATERIAL,
	DS_SUB_HEADER_REFINE_FAIL_TOO_MUCH_MATERIAL,
	DS_SUB_HEADER_REFINE_SUCCEED,
};

typedef struct SPacketCGDragonSoulRefine
{
	SPacketCGDragonSoulRefine() : header (HEADER_CG_DRAGON_SOUL_REFINE)
	{}
	BYTE header;
	BYTE bSubType;
	TItemPos ItemGrid[DS_REFINE_WINDOW_MAX_NUM];
} TPacketCGDragonSoulRefine;

#ifdef ENABLE_DS_REFINE_ALL
typedef struct SPacketDragonSoulRefineAll {
	uint8_t header, subheader, type, grade;
} TPacketDragonSoulRefineAll;
#endif

typedef struct SPacketGCDragonSoulRefine
{
	SPacketGCDragonSoulRefine() : header(HEADER_GC_DRAGON_SOUL_REFINE)
	{}
	BYTE header;
	BYTE bSubType;
	TItemPos Pos;
} TPacketGCDragonSoulRefine;

typedef struct SChannelStatus
{
	uint16_t port;
	uint8_t status;
} TChannelStatus;

#ifdef ENABLE_RANKING
enum
{
	MAX_RANKING_LIST = 51,
	HEADER_GC_RANKING_SEND = 218,
};

typedef struct SPacketGCList
{
	int		iPosition, iRealPosition, iLevel, iPoints;
	char	szName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGCList;

typedef struct SPacketGCRankingTable {
	SPacketGCRankingTable() : bHeader(HEADER_GC_RANKING_SEND)
	{}
	BYTE 			bHeader;
	TPacketGCList	list[MAX_RANKING_LIST];
} TPacketGCRankingTable;
#endif

#ifdef ENABLE_ACCE_SYSTEM
enum EAcceInfo
{
	ACCE_ABSORPTION_SOCKET = 0,
	ACCE_ABSORBED_SOCKET = 1,
	ACCE_CLEAN_ATTR_VALUE0 = 7,
	ACCE_WINDOW_MAX_MATERIALS = 2,
};

enum
{
	HEADER_CG_ACCE = 211,
	HEADER_GC_ACCE = 215,
	ACCE_SUBHEADER_GC_OPEN = 0,
	ACCE_SUBHEADER_GC_CLOSE,
	ACCE_SUBHEADER_GC_ADDED,
	ACCE_SUBHEADER_GC_REMOVED,
	ACCE_SUBHEADER_CG_REFINED,
	ACCE_SUBHEADER_CG_CLOSE = 0,
	ACCE_SUBHEADER_CG_ADD,
	ACCE_SUBHEADER_CG_REMOVE,
	ACCE_SUBHEADER_CG_REFINE,
};

typedef struct SPacketAcce
{
	BYTE	header;
	BYTE	subheader;
	bool	bWindow;
	DWORD	dwPrice;
	BYTE	bPos;
	TItemPos	tPos;
	DWORD	dwItemVnum;
	DWORD	dwMinAbs;
	DWORD	dwMaxAbs;
} TPacketAcce;

typedef struct SAcceMaterial
{
	BYTE	bHere;
	WORD	wCell;
} TAcceMaterial;

typedef struct SAcceResult
{
	DWORD	dwItemVnum;
	DWORD	dwMinAbs;
	DWORD	dwMaxAbs;
} TAcceResult;
#endif

#ifdef __ENABLE_NEW_OFFLINESHOP__

//ACTIONS PACKETS
typedef struct
{
	uint8_t bHeader;
	int32_t wSize;
	uint8_t bSubHeader;
} TPacketGCNewOfflineshop;

typedef struct {
	BYTE bHeader;
	WORD wSize;
	BYTE bSubHeader;
} TPacketCGNewOfflineShop;





namespace offlineshop
{
	//patch 08-03-2020
	enum class ExpirationType {
		EXPIRE_NONE,
		EXPIRE_REAL_TIME,
		EXPIRE_REAL_TIME_FIRST_USE,
	};

	typedef struct SPriceInfo
	{
		long long	illYang;
#ifdef ENABLE_CHEQUE_SYSTEM
		int			iCheque;
#endif

		SPriceInfo() : illYang(0)
#ifdef ENABLE_CHEQUE_SYSTEM
			,iCheque(0)
#endif
		{}

	} TPriceInfo;

	typedef struct
	{
		DWORD	dwVnum;
		DWORD	dwCount;
		long	alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
		TPlayerItemAttribute    aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];

#if defined(ENABLE_CHANGELOOK)
		DWORD	dwTransmutation;
#endif
#ifdef ATTR_LOCK
		int		iLockedAttr;
#endif

		//patch 08-03-2020
		ExpirationType expiration;
	} TItemInfoEx;

	typedef struct
	{
		DWORD		dwOwnerID,dwItemID;
		TPriceInfo	price;
		TItemInfoEx	item;
#if defined(ENABLE_OFFLINESHOP_REWORK)
		char szOwnerName[CHARACTER_NAME_MAX_LEN+1];
#endif
	} TItemInfo;

	typedef struct {
		DWORD		dwOfferID,dwOwnerID, dwItemID, dwOffererID;
		TPriceInfo	price;
		bool		bNoticed, bAccepted;

		//offlineshop-updated 03/08/19
		char		szBuyerName[CHARACTER_NAME_MAX_LEN+1];

	} TOfferInfo;



	//offlineshop-updated 03/08/19
	typedef struct {
		TItemInfo item;
		char szShopName[OFFLINE_SHOP_NAME_MAX_LEN];
	} TMyOfferExtraInfo;

	typedef struct SValutesInfoa
	{
		long long	illYang;
#ifdef ENABLE_CHEQUE_SYSTEM
		int			iCheque;
#endif


		void operator +=(const SValutesInfoa& r)
		{
			illYang += r.illYang;
#ifdef ENABLE_CHEQUE_SYSTEM
			iCheque += r.iCheque;
#endif
		}

		void operator -=(const SValutesInfoa& r)
		{
			illYang -= r.illYang;
#ifdef ENABLE_CHEQUE_SYSTEM
			iCheque -= r.iCheque;
#endif
		}

		SValutesInfoa() : illYang(0)
#ifdef ENABLE_CHEQUE_SYSTEM
			, iCheque(0)
#endif
		{}

	} TValutesInfo;



	typedef struct {
		DWORD	dwOwnerID;
		DWORD	dwDuration;
		char	szName[OFFLINE_SHOP_NAME_MAX_LEN];
		DWORD	dwCount;
	} TShopInfo;



	typedef struct SFilterInfo {
		BYTE		bType;
		BYTE		bSubType;

		char		szName[OFFLINE_SHOP_ITEM_MAX_LEN];
		TPriceInfo	priceStart, priceEnd;
		int			iLevelStart, iLevelEnd;

		DWORD		dwWearFlag;
		TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_NORM_NUM];
		int			iRarity = -1;
#if defined(ENABLE_OFFLINESHOP_REWORK)
		bool		bPlayerName;
#endif
	}TFilterInfo;


	typedef struct {
		TItemPos	pos;
		TPriceInfo	price;
	}TShopItemInfo;



	//AUCTION
	typedef struct {
		DWORD dwOwnerID;
		char  szOwnerName[CHARACTER_NAME_MAX_LEN + 1];
		DWORD dwDuration;

		TPriceInfo	init_price;
		TItemInfoEx item;
	} TAuctionInfo;



	typedef struct {
		TPriceInfo	price;
		DWORD		dwOwnerID;
		DWORD		dwBuyerID;

		char		szBuyerName[CHARACTER_NAME_MAX_LEN + 1];
		//bool		bIsRaised;

	} TAuctionOfferInfo;



	typedef struct {
		TAuctionInfo	auction;
		TPriceInfo		actual_best;
		DWORD			dwOfferCount;
	}TAuctionListElement;







	//GAME TO CLIENT
	enum eSubHeaderGC
	{
		SUBHEADER_GC_SHOP_LIST,
		SUBHEADER_GC_SHOP_OPEN,
		SUBHEADER_GC_SHOP_OPEN_OWNER,
		SUBHEADER_GC_SHOP_OPEN_OWNER_NO_SHOP,
		SUBHEADER_GC_SHOP_CLOSE,
		SUBHEADER_GC_SHOP_BUY_ITEM_FROM_SEARCH,

		SUBHEADER_GC_OFFER_LIST,

		SUBHEADER_GC_SHOP_FILTER_RESULT,
		SUBHEADER_GC_SHOP_SAFEBOX_REFRESH,

		//AUCTION
		SUBHEADER_GC_AUCTION_LIST,
		SUBHEADER_GC_OPEN_MY_AUCTION,
		SUBHEADER_GC_OPEN_MY_AUCTION_NO_AUCTION,
		SUBHEADER_GC_OPEN_AUCTION,
#ifdef ENABLE_NEW_SHOP_IN_CITIES
		SUBHEADER_GC_INSERT_SHOP_ENTITY,
		SUBHEADER_GC_REMOVE_SHOP_ENTITY,
#endif
#if defined(ENABLE_OFFLINESHOP_REWORK)
		SUBHEADER_GC_NOTIFICATION,
#endif
	};


	typedef struct {
		DWORD	dwShopCount;
	} TSubPacketGCShopList;


	typedef struct {
		TShopInfo	shop;

	} TSubPacketGCShopOpen;


	typedef struct {
		TShopInfo	shop;
		DWORD		dwSoldCount;
		DWORD		dwOfferCount;

	} TSubPacketGCShopOpenOwner;



	typedef struct {
		DWORD dwCount;
	} TSubPacketGCShopFilterResult;


	typedef struct {
		DWORD dwOfferCount;
		
	} TSubPacketGCShopOfferList;


	typedef struct {
		TValutesInfo	valute;
		DWORD			dwItemCount;

	}TSubPacketGCShopSafeboxRefresh;

	typedef struct {
		DWORD dwOwnerID;
		DWORD dwItemID;
	}TSubPacketGCShopBuyItemFromSearch;



	//AUCTION
	typedef struct {
		DWORD dwCount;
		bool bOwner;
	}TSubPacketGCAuctionList;



	typedef struct {
		TAuctionInfo auction;
		DWORD dwOfferCount;


	}TSubPacketGCAuctionOpen;



#ifdef ENABLE_NEW_SHOP_IN_CITIES
	typedef struct {
		DWORD	dwVID;
		char	szName[OFFLINE_SHOP_NAME_MAX_LEN];
		int		iType;

		long 	x, y, z;
	} TSubPacketGCInsertShopEntity;


	typedef struct {
		DWORD dwVID;
	} TSubPacketGCRemoveShopEntity;
#endif

#if defined(ENABLE_OFFLINESHOP_REWORK)
	typedef struct {
		DWORD dwItemID;
		long long dwItemPrice;
		WORD dwItemCount;
	} TSubPacketGCNotification;

	typedef struct
	{
		DWORD dwTime;
	}TSubPacketCGShopExtendTime;

#endif

	// CLIENT TO GAME
	enum eSubHeaderCG
	{
		SUBHEADER_CG_SHOP_CREATE_NEW,
		SUBHEADER_CG_SHOP_CHANGE_NAME,
#if defined(ENABLE_OFFLINESHOP_REWORK)
		SUBHEADER_CG_SHOP_EXTEND_TIME,
#endif
		SUBHEADER_CG_SHOP_FORCE_CLOSE,
		SUBHEADER_CG_SHOP_REQUEST_SHOPLIST,
		SUBHEADER_CG_SHOP_OPEN,
		SUBHEADER_CG_SHOP_OPEN_OWNER,
		SUBHEADER_CG_SHOP_BUY_ITEM,

		SUBHEADER_CG_SHOP_ADD_ITEM,
		SUBHEADER_CG_SHOP_REMOVE_ITEM,
		SUBHEADER_CG_SHOP_EDIT_ITEM,

		SUBHEADER_CG_SHOP_FILTER_REQUEST,

		SUBHEADER_CG_SHOP_OFFER_CREATE,
		SUBHEADER_CG_SHOP_OFFER_ACCEPT,
		SUBHEADER_CG_SHOP_OFFER_CANCEL,
		SUBHEADER_CG_SHOP_REQUEST_OFFER_LIST,

		SUBHEADER_CG_SHOP_SAFEBOX_OPEN,
		SUBHEADER_CG_SHOP_SAFEBOX_GET_ITEM,
		SUBHEADER_CG_SHOP_SAFEBOX_GET_VALUTES,
		SUBHEADER_CG_SHOP_SAFEBOX_CLOSE,


		//AUCTION
		SUBHEADER_CG_AUCTION_LIST_REQUEST,
		SUBHEADER_CG_AUCTION_OPEN_REQUEST,
		SUBHEADER_CG_MY_AUCTION_OPEN_REQUEST,
		SUBHEADER_CG_CREATE_AUCTION,
		SUBHEADER_CG_AUCTION_ADD_OFFER,
		SUBHEADER_CG_EXIT_FROM_AUCTION,


		SUBHEADER_CG_CLOSE_BOARD,

#ifdef ENABLE_NEW_SHOP_IN_CITIES
		SUBHEADER_CG_CLICK_ENTITY,
#endif
		SUBHEADER_CG_AUCTION_CLOSE,
	};




	typedef struct
	{
		TShopInfo shop;
	}TSubPacketCGShopCreate;


	typedef struct
	{
		char szName[OFFLINE_SHOP_NAME_MAX_LEN];
	}TSubPacketCGShopChangeName;



	typedef struct
	{
		DWORD dwOwnerID;
	}TSubPacketCGShopOpen;



	typedef struct
	{
		TItemPos	pos;
		TPriceInfo  price;
	}TSubPacketCGAddItem;


	typedef struct
	{
		DWORD dwItemID;
	}TSubPacketCGRemoveItem;



	typedef struct
	{
		DWORD dwItemID;
		TPriceInfo price;
	}TSubPacketCGEditItem;



	typedef struct
	{
		TFilterInfo filter;
	}TSubPacketCGFilterRequest;



	typedef struct
	{
		TOfferInfo offer;
	}TSubPacketCGOfferCreate;


	typedef struct
	{
		DWORD dwOfferID;
	}TSubPacketCGOfferAccept;


	typedef struct
	{
		DWORD dwOfferID;
		DWORD dwOwnerID;
	}TSubPacketCGOfferCancel;


	typedef struct
	{
		DWORD dwItemID;
	}TSubPacketCGShopSafeboxGetItem;


	typedef struct
	{
		TValutesInfo valutes;
	}TSubPacketCGShopSafeboxGetValutes;

	typedef struct
	{
		DWORD dwOwnerID;
		DWORD dwItemID;
		bool  bIsSearch;
		long long TotalPriceSeen;
	}TSubPacketCGShopBuyItem;



	//AUCTION
	typedef struct {
		DWORD dwOwnerID;
	} TSubPacketCGAuctionOpenRequest;

	typedef struct {
		DWORD		dwDuration;
		TItemPos	pos;

		TPriceInfo	init_price;
	} TSubPacketCGAuctionCreate;


	typedef struct {
		DWORD		dwOwnerID;
		TPriceInfo	price;
	}TSubPacketCGAuctionAddOffer;

	typedef struct {
		DWORD dwOwnerID;
	} TSubPacketCGAuctionExitFrom;


#ifdef ENABLE_NEW_SHOP_IN_CITIES
	typedef struct {
		DWORD dwShopVID;
	} TSubPacketCGShopClickEntity;
#endif
}

#endif

#ifdef ENABLE_CUBE_RENEWAL_WORLDARD

enum
{
	CUBE_RENEWAL_SUB_HEADER_OPEN_RECEIVE,
	CUBE_RENEWAL_SUB_HEADER_CLEAR_DATES_RECEIVE,
	CUBE_RENEWAL_SUB_HEADER_DATES_RECEIVE,
	CUBE_RENEWAL_SUB_HEADER_DATES_LOADING,

	CUBE_RENEWAL_SUB_HEADER_MAKE_ITEM,
	CUBE_RENEWAL_SUB_HEADER_CLOSE,
};


typedef struct  packet_send_cube_renewal
{
	BYTE header;
	BYTE subheader;
	DWORD index_item;
	DWORD count_item;
	DWORD index_item_improve;
}TPacketCGCubeRenewalSend;



typedef struct dates_cube_renewal
{
	DWORD npc_vnum;
	DWORD index;

	DWORD	vnum_reward;
	int		count_reward;

	bool 	item_reward_stackable;

	DWORD	vnum_material_1;
	int		count_material_1;

	DWORD	vnum_material_2;
	int		count_material_2;

	DWORD	vnum_material_3;
	int		count_material_3;

	DWORD	vnum_material_4;
	int		count_material_4;

	DWORD	vnum_material_5;
	int		count_material_5;

	unsigned long long 	gold;
	int 	percent;

#if defined(ENABLE_GAYA_RENEWAL)
	int 	gaya;
#endif
#ifdef ENABLE_CUBE_RENEWAL_COPY_WORLDARD
	DWORD   allowCopy;
#endif
	
	char 	category[100];
}TInfoDateCubeRenewal;

typedef struct packet_receive_cube_renewal
{
	packet_receive_cube_renewal(): header(HEADER_GC_CUBE_RENEWAL)
	{}

	BYTE header;
	BYTE subheader;
	TInfoDateCubeRenewal	date_cube_renewal;
}TPacketGCCubeRenewalReceive;
#endif

#ifdef ENABLE_WHISPER_ADMIN_SYSTEM
typedef struct SPacketCGWhisperAdmin
{
	BYTE	header;
	char	szText[512 + 1];
	char	szLang[2 + 1];
	int		color;
} TPacketCGWhisperAdmin;

typedef struct SPacketCGGetWhisperDetails {
	BYTE	header;
	char	name[CHARACTER_NAME_MAX_LEN + 1];
} TPacketCGGetWhisperDetails;

typedef struct SPacketGCGetWhisperDetails {
	BYTE	header;
	char	name[CHARACTER_NAME_MAX_LEN + 1];
	BYTE	bLanguage;
	BYTE	bEmpire;
} TPacketGCGetWhisperDetails;

#endif

#ifdef ENABLE_ATLAS_BOSS
typedef struct SPacketGCBossPosition
{
	BYTE	bHeader;
	WORD	wSize;
	WORD	wCount;
} TPacketGCBossPosition;

struct TBossPosition
{
	BYTE	bType;
#ifdef ENABLE_MULTI_NAMES
	DWORD	szName;
#else
	char	szName[CHARACTER_NAME_MAX_LEN + 1];
#endif
	long	lX;
	long	lY;
	long	lTime;
};
#endif

#if defined(ENABLE_TEXTS_RENEWAL)
typedef struct SPacketGCChatNew {
	BYTE header;
	WORD size;
	BYTE type;
	DWORD idx;
} TPacketGCChatNew;
#endif

#ifdef ENABLE_NEW_FISHING_SYSTEM
enum {
	FISHING_SUBHEADER_NEW_START = 0,
	FISHING_SUBHEADER_NEW_STOP = 1,
	FISHING_SUBHEADER_NEW_CATCH = 2,
	FISHING_SUBHEADER_NEW_CATCH_FAIL = 3,
	FISHING_SUBHEADER_NEW_CATCH_SUCCESS = 4,
	FISHING_SUBHEADER_NEW_CATCH_FAILED = 5,
};

typedef struct SPacketFishingNew
{
	BYTE header;
	BYTE subheader;
	DWORD vid;
	int dir;
	BYTE need;
	BYTE count;
} TPacketFishingNew;
#endif

#ifdef ENABLE_OPENSHOP_PACKET
typedef struct SPacketOpenShop {
	uint8_t header;
	int32_t shopid;
} TPacketOpenShop;
#endif

#ifdef ENABLE_REWARD_SYSTEM
enum
{
	REWARD_105 = 1,
	REWARD_PET_115 = 2,
	REWARD_120 = 3,
	REWARD_LEGENDARY_SKILL = 4,
	REWARD_LEGENDARY_SKILL_SET = 5,
	REWARD_KILL_DRAGON = 6,
	REWARD_KILL_RAZADOR = 7,
	REWARD_KILL_NEMERE = 8,
	REWARD_OFFLINESHOP_SLOT = 9,
	REWARD_INVENTORY_SLOT = 10,
	REWARD_AVERAGE = 11,
	REWARD_ELEMENT = 12,
	REWARD_BATTLEPASS = 13,
	REWARD_CUSTOM_SASH = 14,
	REWARD_AURA = 15,
	REWARD_ENERGY = 16,
	REWARD_112_BIO = 17,
	REWARD_120_BIO = 18,
	REWARD_LEADER_SHIP = 19,
	REWARD_BUFFI_LEGENDARY_SKILL = 20,
	REWARD_MAX,
};
#endif

#if defined(ENABLE_EVENT_MANAGER)
typedef struct SPacketGCEventManager
{
	uint8_t header;
	int32_t size;
} TPacketGCEventManager;

typedef struct event_struct_
{
	int16_t eventID;
	uint8_t eventIndex;
	int32_t startTime;
	int32_t endTime;
	uint8_t empireFlag;
	uint8_t channelFlag;
	uint32_t value[4];
	bool eventStatus;
	bool eventTypeOnlyStart;
} TEventManagerData;

enum
{
	EVENT_MANAGER_LOAD,
	EVENT_MANAGER_EVENT_STATUS,
	EVENT_MANAGER_REMOVE_EVENT,
	EVENT_MANAGER_UPDATE,
	BONUS_EVENT = 1,
	DOUBLE_BOSS_LOOT_EVENT = 2,
	DOUBLE_METIN_LOOT_EVENT = 3,
	DOUBLE_MISSION_BOOK_EVENT = 4,
	DUNGEON_COOLDOWN_EVENT = 5,
	DUNGEON_TICKET_LOOT_EVENT = 6,
	EMPIRE_WAR_EVENT = 7,
	MOONLIGHT_EVENT = 8,
	TOURNAMENT_EVENT = 9,
	WHELL_OF_FORTUNE_EVENT = 10,
#if defined(ENABLE_HALLOWEEN_EVENT_2022)
	HALLOWEEN_EVENT = 11,
#endif
	NPC_SEARCH_EVENT = 12,
	EXP_EVENT = 13,
	ITEM_DROP_EVENT = 14,
	YANG_DROP_EVENT = 15,
#if defined(ENABLE_NEW_FISH_EVENT)
	JIGSAW_EVENT = 16,
#endif
#if defined(ENABLE_LETTERS_EVENT)
	LETTERS_EVENT = 17,
#endif
#if defined(ENABLE_OKEY_CARD_GAME)
	OKEY_CARD_EVENT = 18,
#endif
};
#endif

#if defined(ENABLE_INGAME_ITEMSHOP)
enum
{
	ITEMSHOP_LOAD,
	ITEMSHOP_LOG,
	ITEMSHOP_BUY,
	ITEMSHOP_DRAGONCOIN,
	ITEMSHOP_RELOAD,
};

typedef struct SIShopData
{
	DWORD	id;
	DWORD	itemVnum;
	long long	itemPrice;
	int		topSellingIndex;
	BYTE	discount;
	int		offerTime;
	int		addedTime;
	long long	sellCount;
	int	week_limit;
	int	month_limit;
}TIShopData;

typedef struct SIShopLogData
{
	DWORD	accountID;
	char	playerName[CHARACTER_NAME_MAX_LEN + 1];
	char	buyDate[21];
	int		buyTime;
	char	ipAdress[16];
	DWORD	itemVnum;
	int		itemCount;
	long long	itemPrice;
}TIShopLogData;

typedef struct SPacketGCItemShop
{
	BYTE	header;
	DWORD	size;
} TPacketGCItemShop;
#endif

#if defined(USE_BATTLEPASS)
typedef struct SPacketCGExtBattlePassAction
{
	BYTE bHeader;
	BYTE bAction;
} TPacketCGExtBattlePassAction;

typedef struct SPacketCGExtBattlePassSendPremiumItem
{
	BYTE bHeader;
	int iSlotIndex;
} TPacketCGExtBattlePassSendPremiumItem;

typedef struct SPacketGCExtBattlePassOpen
{
	BYTE bHeader;
} TPacketGCExtBattlePassOpen;

typedef struct SPacketGCExtBattlePassGeneralInfo
{
	BYTE bHeader;
	char szSeasonName[64+1];
	DWORD dwBattlePassID;
	DWORD dwBattlePassStartTime;
	DWORD dwBattlePassEndTime;
} TPacketGCExtBattlePassGeneralInfo;

typedef struct SPacketGCExtBattlePassMissionInfo
{
	BYTE bHeader;
	WORD wSize;
	WORD wRewardSize;
	DWORD dwBattlePassID;
} TPacketGCExtBattlePassMissionInfo;

typedef struct SPacketGCExtBattlePassMissionUpdate
{
	BYTE bHeader;
	BYTE bMissionIndex;
	BYTE bMissionType;
	DWORD dwNewProgress;
} TPacketGCExtBattlePassMissionUpdate;

typedef struct SPacketGCExtBattlePassRanking
{
	BYTE bHeader;
	char szPlayerName[CHARACTER_NAME_MAX_LEN + 1];
	BYTE bBattlePassID;
	DWORD dwStartTime;
	DWORD dwEndTime;
} TPacketGCExtBattlePassRanking;
#endif

#ifdef ENABLE_SWITCHBOT_WORLDARD
enum
{
	SWITCH_SUB_HEADER_CHANGE,
	SWITCH_SUB_HEADER_CLOSE,
	SWITCH_SUB_HEADER_OPEN,

	SWITCH_RECEIVE_OPEN,
	SWITCH_RECEIVE_CLEAR_INFO,
	SWITCH_RECEIVE_INFO_BONUS_ITEM,
	SWITCH_RECEIVE_INFO_EXTRA,
};

typedef struct packet_send_switchbot
{
	BYTE header;
	BYTE subheader;
	TPlayerItemAttribute aAttr[5];
	int vnum_change;
} TPacketCGSwitchBotSend;
	
typedef struct SPacketGCSwitchBotReceive
{
	SPacketGCSwitchBotReceive() : header(HEADER_GC_SWITCHBOT)
	{}
	BYTE header;
	BYTE bSubType;
	int  id_bonus;
	int  value_bonus_0;
	int  value_bonus_1;
	int  value_bonus_2;
	int  value_bonus_3;
	int  value_bonus_4;

} TPacketGCSwitchBotReceive;
#endif

#if defined(ENABLE_INGAME_CHCHANGE)
typedef struct SPacketCGChangeChannel {
	BYTE header;
	BYTE channel;
} TPacketCGChangeChannel;
#endif

#if defined(ENABLE_EXCHANGE_FRAGMENTS)
typedef struct SPacketExchangeFragments
{
	BYTE bHeader;
	TItemPos itemPos;
} TPacketExchangeFragments;
#endif

#ifdef USE_CAPTCHA_SYSTEM
typedef struct SPacketGCCaptcha
{
    uint8_t     bHeader;
    uint16_t    code;
    uint8_t     limit;
} TPacketGCCaptcha;

typedef struct SPacketCGCaptcha
{
    uint8_t     bHeader;
    uint16_t    code;
} TPacketCGCaptcha;
#endif

#if defined(ENABLE_NEW_ANTICHEAT_RULES)
enum EAntiCheatSubHeaders
{
	ANTICHEAT_TYPE_ATTACKSPEED,
	ANTICHEAT_TYPE_RANGE,
};

typedef struct SPacketGCAntiCheat
{
	uint8_t bHeader;
	uint8_t bReason;
} TPacketGCAntiCheat;
#endif

typedef struct SPacketEmpty
{
	uint8_t bHeader;
} TPacketEmpty;

#if defined(ENABLE_NEW_FISH_EVENT)
enum {
	FISH_EVENT_SUBHEADER_BOX_USE,
	FISH_EVENT_SUBHEADER_SHAPE_ADD,
	FISH_EVENT_SUBHEADER_GC_REWARD,
	FISH_EVENT_SUBHEADER_GC_ENABLE,
};

typedef struct SPacketGCFishEvent {
	uint8_t bHeader;
	uint8_t bSubheader;
} TPacketCGFishEvent;

typedef struct SPacketGCFishEventInfo {
	uint8_t bHeader;
	uint8_t bSubheader;
	uint32_t dwFirstArg;
	uint32_t dwSecondArg;
} TPacketGCFishEventInfo;
#endif

#if defined(ENABLE_MESSENGER_BLOCK)
typedef struct SPacketGCMessengerBlockList {
	uint8_t connected;
	uint8_t length;
} TPacketGCMessengerBlockList;
#endif

#if defined(ENABLE_AURA_SYSTEM)
enum EPacketGCAuraSubHeader {
	AURA_SUBHEADER_GC_OPEN,
	AURA_SUBHEADER_GC_CLOSE,
	AURA_SUBHEADER_GC_SET_ITEM,
	AURA_SUBHEADER_GC_CLEAR_SLOT,
	AURA_SUBHEADER_GC_CLEAR_ALL,
	AURA_SUBHEADER_GC_CLEAR_RIGHT,
	AURA_SUBHEADER_GC_REFINE_INFO,
};

typedef struct SSubPacketGCAuraOpenClose {
	uint8_t bAuraWindowType;
} TSubPacketGCAuraOpenClose;

typedef struct SSubPacketGCAuraSetItem {
	TItemPos Cell;
	TItemPos AuraCell;
	TItemData pItem;
} TSubPacketGCAuraSetItem;

typedef struct SSubPacketGCAuraClearSlot {
	uint8_t bAuraSlotPos;
} TSubPacketGCAuraClearSlot;

typedef struct SSubPacketGCAuraRefineInfo {
	uint8_t bAuraRefineInfoType;
	uint8_t bAuraRefineInfoLevel;
	uint8_t bAuraRefineInfoExpPercent;
} TSubPacketGCAuraRefineInfo;

enum EPacketCGAuraSubHeader {
	AURA_SUBHEADER_CG_REFINE_CHECKIN,
	AURA_SUBHEADER_CG_REFINE_CHECKOUT,
	AURA_SUBHEADER_CG_REFINE_ACCEPT,
	AURA_SUBHEADER_CG_REFINE_CANCEL,
};

typedef struct SSubPacketCGAuraRefineCheckIn {
	TItemPos ItemCell;
	TItemPos AuraCell;
	uint8_t byAuraRefineWindowType;
} TSubPacketCGAuraRefineCheckIn;

typedef struct SSubPacketCGAuraRefineCheckOut {
	TItemPos AuraCell;
	uint8_t byAuraRefineWindowType;
} TSubPacketCGAuraRefineCheckOut;

typedef struct SSubPacketCGAuraRefineAccept {
	uint8_t byAuraRefineWindowType;
} TSubPacketCGAuraRefineAccept;

typedef struct SPacketGCAura
{
	SPacketGCAura() : bHeader(HEADER_GC_AURA) {}
	uint8_t bHeader;
	WORD wSize;
	uint8_t bSubHeader;
} TPacketGCAura;

typedef struct SPacketCGAura {
	SPacketCGAura() : bHeader(HEADER_CG_AURA) {}
	uint8_t bHeader;
	WORD wSize;
	uint8_t bSubHeader;
} TPacketCGAura;
#endif

#if defined(ENABLE_CHANGELOOK)
enum EChangeLookSubHeader {
	SUBHEADER_CHANGE_LOOK_OPEN = 0,
	SUBHEADER_CHANGE_LOOK_CLOSE,
	SUBHEADER_CHANGE_LOOK_ADD,
	SUBHEADER_CHANGE_LOOK_REMOVE,
	SUBHEADER_CHANGE_LOOK_REFINE,
};

typedef struct SPacketChangeLook {
	uint8_t bHeader;
	uint8_t bSubHeader;
	int64_t dwCost;
	uint8_t bPos;
	TItemPos tPos;
} TPacketChangeLook;

typedef struct SChangeLookMaterial {
	uint8_t bHere;
	WORD wCell;
} TChangeLookMaterial;
#endif

#if defined(ENABLE_NEW_GOLD_LIMIT)
typedef struct packet_gold
{
	uint8_t header;
	uint64_t gold;
} TPacketGCGold;

typedef struct packet_gold_change
{
	uint8_t header;
	uint32_t dwVID;
	int64_t amount;
	uint64_t value;
} TPacketGCGoldChange;
#endif

typedef struct SPacketQuickSlotAdd
{
	uint8_t header;
	uint8_t pos;
	TQuickSlot slot;
} TPacketQuickSlotAdd;

typedef struct SPacketCGQuickSlotDel
{
	uint8_t header;
	uint8_t pos;
} TPacketQuickSlotDel;

typedef struct SPacketCGQuickSlotSwap
{
	uint8_t header;
	uint8_t pos;
	uint8_t change_pos;
} TPacketQuickSlotSwap;

#ifdef ENABLE_PREMIUM_PLAYERS
enum PremiumPlayersHeader
{
	HEADER_CG_PREMIUM_PLAYERS = 177,
	HEADER_GC_PREMIUM_PLAYERS = 142,

	PREMIUM_PLAYERS_SUBHEADER_CG_OPEN = 0,
	PREMIUM_PLAYERS_SUBHEADER_CG_LIST = 1,
	PREMIUM_PLAYERS_SUBHEADER_CG_ACTIVATE = 2,

	PREMIUM_PLAYERS_SUBHEADER_GC_OPEN = 0,
	PREMIUM_PLAYERS_SUBHEADER_GC_LIST = 1,
	PREMIUM_PLAYERS_SUBHEADER_GC_ACTIVATE = 2,
};

typedef struct SPacketCGPremiumPlayers
{
	SPacketCGPremiumPlayers() :
		byHeader(HEADER_CG_PREMIUM_PLAYERS)
	{}
	BYTE byHeader;
	BYTE bySubHeader;
} TPacketCGPremiumPlayers;

typedef struct SPacketGCPremiumPlayers
{
	SPacketGCPremiumPlayers() :
		byHeader(HEADER_GC_PREMIUM_PLAYERS)
	{}
	BYTE byHeader;
	BYTE bySubHeader;
	BYTE byPos;
	char szName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGCPremiumPlayers;
#endif

#if defined(USE_ATTR_6TH_7TH)
enum EAttr67AddSubHeader
{
	SUBHEADER_CG_ATTR67_ADD_CLOSE,
	SUBHEADER_CG_ATTR67_ADD_OPEN,
	SUBHEADER_CG_ATTR67_ADD_REGIST,
};

typedef struct SPacketCGAttr67Add
{
	uint8_t byHeader;
	uint8_t bySubHeader;
	TAttr67AddData Attr67AddData;
} TPacketCGAttr67Add;
#endif

#ifdef USE_MULTIPLE_OPENING
typedef struct SPacketCGMultipleOpening
{
    SPacketCGMultipleOpening() : header(HEADER_CG_MULTI_CHESTS_OPEN)
    {
        
    }

    uint8_t     header;
    TItemPos    pos;
    uint16_t    count;
} TPacketCGMultipleOpening;
#endif

struct SBossPosition
{
	uint32_t vnum;
	int32_t x, y;
	uint32_t time;
	uint32_t real_time;
	bool is_alive;
	SBossPosition() = default;
	SBossPosition(const uint32_t vnum, const int32_t x, const int32_t y, const uint32_t time) : vnum(vnum), x(x), y(y),
		time(time),
		real_time(0),
		is_alive(false)
	{
	}

	bool operator==(const SBossPosition& rhs) const
	{
		return vnum == rhs.vnum && x == rhs.x && y == rhs.y && time == rhs.time;
	}

	bool operator!=(const SBossPosition& rhs) const
	{
		return !(*this == rhs);
	}
};

struct SPacketGCBossPosition
{
	uint8_t header;
	uint16_t size;
};

typedef struct SPacketCGChangeCountryFlag
{
	BYTE header;
	BYTE index;
	char country_flag[3 + 1];
} TPacketCGChangeCountryFlag;

typedef struct SPacketGCChangeCountryFlag
{
	BYTE header;
	BYTE index;
	char country_flag[3 + 1];
} TPacketGCChangeCountryFlag;

struct SPacketCGWhisperInfo
{
	uint8_t	header;
	char name[CHARACTER_NAME_MAX_LEN + 1];

	SPacketCGWhisperInfo() : header(HEADER_CG_WHISPER_INFO), name{}
	{
	}
};

struct SPacketGCWhisperInfo
{
	uint8_t	header;
	char name[CHARACTER_NAME_MAX_LEN + 1];
	char country_flag[3 + 1];
	uint8_t empire;

	SPacketGCWhisperInfo() : header(HEADER_GC_WHISPER_INFO), name{}, country_flag{}, empire(0)
	{
	}
};

#pragma pack(pop)

