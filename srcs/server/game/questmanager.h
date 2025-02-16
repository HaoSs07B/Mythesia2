#ifndef __METIN2_SERVER_QUEST_MANAGER__
#define __METIN2_SERVER_QUEST_MANAGER__

#include <unordered_map>

#include "questnpc.h"

class ITEM;
class CHARACTER;
class CDungeon;

#ifndef lua_String
#define lua_String const char*
#endif

enum ETL {ETL_NIL, ETL_CFUN, ETL_LNUM, ETL_LSTR};

class lua_Any
{
	public:
		// non-merged union data
		lua_CFunction cfVal;
		lua_Number lnVal;
		lua_String lsVal;
		// specified type
		ETL type;

	lua_Any(): type(ETL_NIL) {}
	lua_Any(lua_CFunction a1): cfVal(a1), type(ETL_CFUN) {}
	lua_Any(lua_Number a1): lnVal(a1), type(ETL_LNUM) {}
	lua_Any(lua_String a1): lsVal(a1), type(ETL_LSTR) {}
};

typedef struct luaC_tab {
	const char *name;
	lua_Any val;
} _luaC_tab;

namespace quest
{
	bool IsScriptTrue(const char* code, int size);
	std::string ScriptToString(const std::string& str);

	class CQuestManager : public singleton<CQuestManager>
	{
		public:
			enum
			{
				QUEST_SKIN_NOWINDOW,
				QUEST_SKIN_NORMAL,
				//QUEST_SKIN_CINEMATIC,
				QUEST_SKIN_SCROLL=4,
				QUEST_SKIN_CINEMATIC=5,
				QUEST_SKIN_COUNT
			};

			typedef std::map<std::string, int>		TEventNameMap;
			typedef std::map<unsigned int, PC>	PCMap;

		public:
			CQuestManager();
			virtual ~CQuestManager();

			bool		Initialize();
			void		Destroy();

			bool		InitializeLua();
			lua_State *		GetLuaState() { return L; }
			void		AddLuaFunctionTable(const char * c_pszName, luaL_reg * preg, bool bCheckIfExists = false);
			void		AddLuaFunctionSubTable(const char * c_pszName, const char * c_pszSubName, luaL_reg * preg);
			void		AppendLuaFunctionTable(const char * c_pszName, luaL_reg * preg, bool bForceCreation = false);
			void		AddLuaConstantGlobal(const char * c_pszName, lua_Number lNumber, bool bOverwrite = false);
			void		AddLuaConstantInTable(const char * c_pszName, const char * c_pszSubName, lua_Number lNumber, bool bForceCreation = false);
			void		AddLuaConstantInTable(const char * c_pszName, const char * c_pszSubName, const char * szString, bool bForceCreation = false);
			void		AddLuaConstantSubTable(const char * c_pszName, const char * c_pszSubName, luaC_tab * preg);

			TEventNameMap	m_mapEventName;

			QuestState		OpenState(const std::string& quest_name, int state_index);
			void		CloseState(QuestState& qs);
			bool		RunState(QuestState& qs);

			PC *		GetPC(unsigned int pc);
			PC *		GetPCForce(unsigned int pc);	// 현재 PC를 바꾸지 않고 PC 포인터를 가져온다.

			unsigned int	GetCurrentNPCRace();
			const std::string & 	GetCurrentQuestName();
			unsigned int	FindNPCIDByName(const std::string& name);

			//void		SetCurrentNPCCharacterPtr(LPCHARACTER ch) { m_pkCurrentNPC = ch; }
			LPCHARACTER		GetCurrentNPCCharacterPtr();

			void		SetCurrentEventIndex(int index) { m_iRunningEventIndex = index; }

			bool		UseItem(unsigned int pc, LPITEM item, bool bReceiveAll);
			bool		SIGUse(unsigned int pc, DWORD sig_vnum, LPITEM item, bool bReceiveAll);
			bool		TakeItem(unsigned int pc, unsigned int npc, LPITEM item);
			LPITEM		GetCurrentItem();
			void		ClearCurrentItem();
			void		SetCurrentItem(LPITEM item);
			void		AddServerTimer(const std::string& name, DWORD arg, LPEVENT event);
			void		ClearServerTimer(const std::string& name, DWORD arg);
			void		ClearServerTimerNotCancel(const std::string& name, DWORD arg);
			void		CancelServerTimers(DWORD arg);

			void		SetServerTimerArg(DWORD dwArg);
			DWORD		GetServerTimerArg();

			// event over state and stae
			bool		ServerTimer(unsigned int npc, unsigned int arg);

			void		Login(unsigned int pc, const char * c_pszQuestName = NULL);
			void		Logout(unsigned int pc);
			bool		Timer(unsigned int pc, unsigned int npc);
			bool		Click(unsigned int pc, LPCHARACTER pkNPC);
			void		Kill(unsigned int pc, unsigned int npc);
#ifdef ENABLE_QUEST_DIE_EVENT
			void		Die(unsigned int pc, unsigned int npc);
#endif
#if defined(__DUNGEON_INFO_SYSTEM__)
			void		QuestDamage(unsigned int pc, unsigned int npc);
#endif
			void		LevelUp(unsigned int pc);
			void		AttrIn(unsigned int pc, LPCHARACTER ch, int attr);
			void		AttrOut(unsigned int pc, LPCHARACTER ch, int attr);
			bool		Target(unsigned int pc, DWORD dwQuestIndex, const char * c_pszTargetName, const char * c_pszVerb);
			bool		GiveItemToPC(unsigned int pc, LPCHARACTER pkChr);
			void		Unmount(unsigned int pc);

			void		QuestButton(unsigned int pc, unsigned int quest_index);
			void		QuestInfo(unsigned int pc, unsigned int quest_index);

			void		EnterState(DWORD pc, DWORD quest_index, int state);
			void		LeaveState(DWORD pc, DWORD quest_index, int state);

			void		Letter(DWORD pc);
			void		Letter(DWORD pc, DWORD quest_index, int state);

			void		ItemInformer(unsigned int pc, unsigned int vnum);	//독일선물기능

			//

			bool		CheckQuestLoaded(PC* pc) { return pc && pc->IsLoaded(); }

			// event occurs in one state
			void		Select(unsigned int pc, unsigned int selection);
			void		Resume(unsigned int pc);

			void		Input(unsigned int pc, const char* msg);
			void		Confirm(unsigned int pc, EQuestConfirmType confirm, unsigned int pc2 = 0);
			void		SelectItem(unsigned int pc, unsigned int selection);

			void		LogoutPC(LPCHARACTER ch);
			void		DisconnectPC(LPCHARACTER ch);

			QuestState *	GetCurrentState()	{ return m_CurrentRunningState; }

			void 		LoadStartQuest(const std::string& quest_name, unsigned int idx);
			//bool		CanStartQuest(const string& quest_name, const PC& pc);
			bool		CanStartQuest(unsigned int quest_index, const PC& pc);
			bool		CanStartQuest(unsigned int quest_index);
			bool		CanEndQuestAtState(const std::string& quest_name, const string& state_name);

			LPCHARACTER		GetCurrentCharacterPtr() { return m_pCurrentCharacter; }
			LPCHARACTER		GetCurrentPartyMember() { return m_pCurrentPartyMember; }
			PC *		GetCurrentPC() { return m_pCurrentPC; }

			void		ClearScript();
			void		SendScript();
			void		AddScript(const std::string& str);

			void		BuildStateIndexToName(const char* questName);

			int			GetQuestStateIndex(const std::string& quest_name, const std::string& state_name);
			const char*		GetQuestStateName(const std::string& quest_name, const int state_index);

			void		SetSkinStyle(int iStyle);

			void		SetNoSend() { m_bNoSend = true; }

			unsigned int	LoadTimerScript(const std::string& name);

			//unsigned int	RegisterQuestName(const string& name);

			void		RegisterQuest(const std::string & name, unsigned int idx);
			unsigned int 	GetQuestIndexByName(const std::string& name);
			const std::string& 	GetQuestNameByIndex(unsigned int idx);

			void		RequestSetEventFlag(const std::string& name, int value);

			void		SetEventFlag(const std::string& name, int value);
			int			GetEventFlag(const std::string& name);
			void		BroadcastEventFlagOnLogin(LPCHARACTER ch);

			void		SendEventFlagList(LPCHARACTER ch);

			void		Reload();

			//void		CreateAllButton(const std::string& quest_name, const std::string& button_name);
			void		SetError() { m_bError = true; }
			void		ClearError() { m_bError = false; }
			bool		IsError() { return m_bError; }
			void		WriteRunningStateToSyserr();
#if !defined(_WIN32)
			void		QuestError(const char* func, int line, const char* fmt, ...);
#else
			//void		QuestError(const char* fmt, ...);
			void		QuestError(const char* func, int line, const char* fmt, ...);
#endif

			void		RegisterNPCVnum(DWORD dwVnum);

		private:
			DWORD			m_dwServerTimerArg;

			std::map<std::pair<std::string, DWORD>, LPEVENT> m_mapServerTimer;

			int				m_iRunningEventIndex;

			std::map<std::string, int>		m_mapEventFlag;

			void			GotoSelectState(QuestState& qs);
			void			GotoPauseState(QuestState& qs);
			void			GotoEndState(QuestState& qs);
			void			GotoInputState(QuestState& qs);
			void			GotoConfirmState(QuestState& qs);
			void			GotoSelectItemState(QuestState& qs);
#if defined(ENABLE_GAYA_RENEWAL)
			void			GotoSelectItemExState(QuestState& qs);
#endif

			lua_State *		L;

			bool			m_bNoSend;

			std::set<unsigned int>			m_registeredNPCVnum;
			std::map<unsigned int, NPC>		m_mapNPC;
			std::map<std::string, unsigned int>	m_mapNPCNameID;
			std::map<std::string, unsigned int>	m_mapTimerID;

			QuestState *	m_CurrentRunningState;

			PCMap			m_mapPC;

			LPCHARACTER		m_pCurrentCharacter;
			LPCHARACTER		m_pCurrentNPCCharacter;
			LPCHARACTER		m_pCurrentPartyMember;
			PC*				m_pCurrentPC;

			std::string			m_strScript;
			bool			m_bQuestInfoFlag;
			int				m_iCurrentSkin;

			struct stringhash
			{
				size_t operator () (const std::string& str) const
				{
					const unsigned char * s = (const unsigned char*) str.c_str();
					const unsigned char * end = s + str.size();
					size_t h = 0;

					while (s < end)
					{
						h *= 16777619;
						h ^= (unsigned char) *(unsigned char *) (s++);
					}

					return h;

				}
			};

			typedef std::unordered_map<std::string, int, stringhash> THashMapQuestName;
			typedef std::unordered_map<unsigned int, std::vector<char> > THashMapQuestStartScript;

			THashMapQuestName			m_hmQuestName;
			THashMapQuestStartScript	m_hmQuestStartScript;
			std::map<unsigned int, std::string>	m_mapQuestNameByIndex;

			bool						m_bError;

		public:
			static bool ExecuteQuestScript(PC& pc, const std::string& quest_name, const int state, const char* code, const int code_size, std::vector<AArgScript*>* pChatScripts = NULL, bool bUseCache = true);
			static bool ExecuteQuestScript(PC& pc, DWORD quest_index, const int state, const char* code, const int code_size, std::vector<AArgScript*>* pChatScripts = NULL, bool bUseCache = true);


		// begin_other_pc_blcok, end_other_pc_block을 위한 객체들.
		public:
			void		BeginOtherPCBlock(DWORD pid);
			void		EndOtherPCBlock();
			bool		IsInOtherPCBlock();
			PC*			GetOtherPCBlockRootPC();
		private:
			PC*			m_pOtherPCBlockRootPC;
			std::vector <DWORD>	m_vecPCStack;
	};
};

#endif
