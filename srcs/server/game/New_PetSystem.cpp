#include "stdafx.h"
#include "utils.h"
#include "vector.h"
#include "char.h"
#include "sectree_manager.h"
#include "char_manager.h"
#include "mob_manager.h"
#include "New_PetSystem.h"
#include "../common/VnumHelper.h"
#include "packet.h"
#include "item_manager.h"
#include "item.h"
#include "db.h"

//#define DISABLE_TRADE_UNSUMMON // this disable the unsummon of pet when a excange/trade/shop/myshop/safebox windows is open, MAKE SURE to have set the items with vnum 55401/55402/55403/55404 with antiflag ANTI_SAFEBOX | ANTI_PKDROP | ANTI_DROP | ANTI_SELL | ANTI_GIVE | ANTI_STACK | ANTI_MYSHOP
//USE AT OWN YOUR RISK								


extern int passes_per_sec;
EVENTINFO(newpetsystem_event_info)
{
	CNewPetSystem* pPetSystem;
};

EVENTINFO(newpetsystem_event_infoe)
{
	CNewPetSystem* pPetSystem;
};

// PetSystem聖 update 背爽澗 event.
// PetSystem精 CHRACTER_MANAGER拭辞 奄糎 FSM生稽 update 背爽澗 奄糎 chracters人 含軒,
// Owner税 STATE研 update 拝 凶 _UpdateFollowAI 敗呪稽 update 背層陥.
// 益訓汽 owner税 state研 update研 CHRACTER_MANAGER拭辞 背爽奄 凶庚拭,
// petsystem聖 update馬陥亜 pet聖 unsummon馬澗 採歳拭辞 庚薦亜 持医陥.
// (CHRACTER_MANAGER拭辞 update 馬檎 chracter destroy亜 pending鞠嬢, CPetSystem拭辞澗 dangling 匂昔斗研 亜走壱 赤惟 吉陥.)
// 魚虞辞 PetSystem幻 穣汽戚闘 背爽澗 event研 降持獣鉄.
EVENTFUNC(newpetsystem_update_event)
{
	newpetsystem_event_info* info = dynamic_cast<newpetsystem_event_info*>( event->info );
	if ( info == NULL )
	{
		sys_err( "check_speedhack_event> <Factor> Null pointer" );
		return 0;
	}

	CNewPetSystem*	pPetSystem = info->pPetSystem;

	if (NULL == pPetSystem)
		return 0;

	
	pPetSystem->Update(0);
	// 0.25段原陥 飴重.
	return PASSES_PER_SEC(1) / 4;
}

EVENTFUNC(newpetsystem_expire_event)
{
	newpetsystem_event_infoe* info = dynamic_cast<newpetsystem_event_infoe*>(event->info);
	if (info == NULL)
	{
		sys_err("check_speedhack_event> <Factor> Null pointer");
		return 0;
	}

	CNewPetSystem*	pPetSystem = info->pPetSystem;

	if (NULL == pPetSystem)
		return 0;


	pPetSystem->UpdateTime();
	// 0.25段原陥 飴重.
	return PASSES_PER_SEC(1);
}


/// NOTE: 1蝶遣斗亜 護鯵税 楢聖 亜霜 呪 赤澗走 薦廃... 蝶遣斗原陥 鯵呪研 陥牽惟 拝暗虞檎 痕呪稽 隔去亜... 製..
/// 亜霜 呪 赤澗 鯵呪人 疑獣拭 社発拝 呪 赤澗 鯵呪亜 堂険 呪 赤澗汽 戚訓闇 奄塙 蒸生艦 析舘 巷獣
const float PET_COUNT_LIMIT = 3;

///////////////////////////////////////////////////////////////////////////////////////
//  CPetActor
///////////////////////////////////////////////////////////////////////////////////////

CNewPetActor::CNewPetActor(LPCHARACTER owner, DWORD vnum, DWORD options)
{
	m_dwVnum = vnum;
	m_dwVID = 0;
	m_dwlevel = 1;
	m_dwlevelstep = 0;
	m_dwExpFromMob = 0;
	m_dwExpFromItem = 0;
	m_dwexp = 0;
	m_dwexpitem = 0;
	m_dwOptions = options;
	m_dwLastActionTime = 0;

	m_pkChar = 0;
	m_pkOwner = owner;

	m_originalMoveSpeed = 0;
	
	m_dwSummonItemVID = 0;
	m_dwSummonItemID = 0;
	m_dwSummonItemVnum = 0;

	m_dwevolution = 0;
	m_dwduration = 0;
	m_dwtduration = 0;
#ifdef ENABLE_NEW_PET_EDITS
	lMinAge = 0;
	dwMinAge = 0;
	m_idx = 0;
#endif
	m_dwTimePet = 0;
	m_dwslotimm = 0;
	m_dwImmTime = 0;

	m_dwskill[0] = 0;
	m_dwskill[1] = 0;
	m_dwskill[2] = 0;
	m_dwskill[3] = 0;

	for (int s = 0; s < 9; ++s) 
	{
		m_dwpetslotitem[s] = -1;
	}
	

	//Riferimento allo slot -1 se non disp 0 disp non set > 0 setted
	m_dwskillslot[0] = -1;
	m_dwskillslot[1] = -1;
	m_dwskillslot[2] = -1;
	m_dwskillslot[3] = -1;

	for (int x = 0; x < 3; ++x) //Inizializzazione bonus del pet
	{
		int btype[3] = { 69, 63, 119};
		m_dwbonuspet[x][0] = btype[x];
		m_dwbonuspet[x][1] = 0;
	}
}

CNewPetActor::~CNewPetActor()
{
	this->Unsummon();

	m_pkOwner = 0;
}

void CNewPetActor::SetName(const char* name)
{
	//std::string petName = m_pkOwner->GetName();
	std::string petName = "";

	if (0 != m_pkOwner && 
		0 == name && 
		0 != m_pkOwner->GetName())
	{
		petName += "'s Pet";
	}
	else
		petName += name;

	if (true == IsSummoned())
		m_pkChar->SetName(petName);

	m_name = petName;
}

void CNewPetActor::SetItemCube(int pos, int invpos) 
{
	if (m_dwpetslotitem[pos] != -1) //Controllo se l'item e' gia settato
		return;
	if (pos > 180 || pos < 0)
		return;

	m_dwpetslotitem[pos] = invpos;
}

void CNewPetActor::ItemCubeFeed(int type)
{
	for (int i = 0; i < 9; ++i) 
	{
		if (m_dwpetslotitem[i] != -1) 
		{
			LPITEM itemxp = m_pkOwner->GetInventoryItem(m_dwpetslotitem[i]);
			if (!itemxp)
				return;
			if (itemxp->GetID() == ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID())->GetID() || m_pkOwner->GetExchange() || m_pkOwner->GetMyShop() || m_pkOwner->GetShopOwner() || m_pkOwner->IsOpenSafebox() || m_pkOwner->IsCubeOpen())
				return;
			if(type == 1)
			{
				if ((itemxp->GetVnum() >= 55401 && itemxp->GetVnum() <= 55411 )|| (itemxp->GetVnum() >= 55701 && itemxp->GetVnum() <= 55711 )||( itemxp->GetVnum() == 55001) )
				{
					if(itemxp->GetVnum() == 55001)
					{
						int tmp_dur = m_dwtduration/2;
						if (m_dwduration+tmp_dur > m_dwtduration)
							m_dwduration = m_dwtduration;
						else
							m_dwduration += tmp_dur;
					}
					else
					{
						int tmp_dur = m_dwtduration * 3 / 100;
						if (m_dwduration+tmp_dur > m_dwtduration)
							m_dwduration = m_dwtduration;
						else
							m_dwduration += tmp_dur;
						m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetDuration %d %d", m_dwduration, m_dwtduration);
					}
					ITEM_MANAGER::instance().RemoveItem(itemxp);
				}
			}
			else if(type == 3)
			{
				if (GetLevel() < 120)
				{
					if(itemxp->GetType() == 1 || itemxp->GetType() == 2)
					{
						SetExp(itemxp->GetShopBuyPrice() / 2, 1);
						ITEM_MANAGER::instance().RemoveItem(itemxp);
					}
				}
#if defined(ENABLE_TEXTS_RENEWAL)
				else {
					m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 742, "");
				}
#endif
			}
		}
	}
	for (int s = 0; s < 9; ++s) 
	{
		m_dwpetslotitem[s] = -1;
	}
}

#ifdef ENABLE_NEW_PET_EDITS
bool CNewPetActor::IncreasePetSkill(int iSlot, int iType) 
#else
bool CNewPetActor::IncreasePetSkill(int skill) 
#endif
{
#ifdef ENABLE_NEW_PET_EDITS
	int idx = m_dwskillslot[iSlot];
	if (idx == -1)
		return false;
	
	if (m_dwskill[iSlot] >= 10) {
#if defined(ENABLE_TEXTS_RENEWAL)
		m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 58, "");
#endif
		return false;
	}
	
	TItemPos Cell;
	Cell.cell = iType;
#ifdef ENABLE_EXTRA_INVENTORY
	Cell.window_type = EXTRA_INVENTORY;
#else
	Cell.window_type = INVENTORY;
#endif
	LPITEM bookItem = m_pkOwner->GetItem(Cell);
	if (!bookItem)
		return false;
	
	iType = bookItem->GetValue(0);
	if ((iType > 12) || (iType < 1) || ((idx != 0) && (idx != iType)) || (bookItem->GetType() != ITEM_TYPE_PET))
		return false;
	
	for (int i = 0; i < 4; i++) {
		if ((iType == m_dwskillslot[i]) && (iSlot != i)) {
#if defined(ENABLE_TEXTS_RENEWAL)
			m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 55, "");
#endif
			return false;
		}
	}
	
	bookItem->SetCount(bookItem->GetCount() - 1);
	
	if (idx == 0)
		m_dwskillslot[iSlot] = iType;
	
	m_dwskill[iSlot] += 1;

#if defined(ENABLE_TEXTS_RENEWAL)
	if (m_dwskill[iSlot] == 1) {
		m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 57, "");
	}
	else {
		m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 56, "%d", m_dwskill[iSlot]);
	}
#endif
	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", iSlot, m_dwskillslot[iSlot], m_dwskill[iSlot]);
	
	ClearBuff();
	GiveBuff();
	
	return true;
#else
	if (GetLevel() < 80 && m_dwevolution < 3)
		return false;
	for (int i = 0; i < 4; ++i) 
	{ //Itero gli slot per cercare la skill
		if (m_dwskillslot[i] == skill) 
		{  //Se trova la skill o la aumenta oppure e' gi?max
			if (m_dwskill[i] < 20) 
			{
				m_dwskill[i] += 1;
#if defined(ENABLE_TEXTS_RENEWAL)
				m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 743, "%d", m_dwskill[i]);
#endif
				m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", i, m_dwskillslot[i], m_dwskill[i]);
				return true;
			}
			else 
			{
#if defined(ENABLE_TEXTS_RENEWAL)
				m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 744, "");
#endif
				return false;
			}
		}
	}

	for (int i = 0; i < 4; ++i) 
	{
		if (m_dwskillslot[i] == 0) 
		{ //Controllo se trovo uno slot vuoto abilitato 
			m_dwskillslot[i] = skill;
			m_dwskill[i] = 1;
#if defined(ENABLE_TEXTS_RENEWAL)
			m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 745, "");
#endif
			m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", i, m_dwskillslot[i], m_dwskill[i]);
			return true;
		}
	}

	/* Qualora il pet non soddisfi le condizioni precedenti
	   Allora tutti gli slot sono pieni e quind non pu?
	   imparare nuove skill 
	*/
#if defined(ENABLE_TEXTS_RENEWAL)
	m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 745, "");
#endif
	return false;
#endif
}

#ifdef ENABLE_NEW_PET_EDITS
bool CNewPetActor::IncreasePetSkillByBook(LPITEM bookItem) 
{
	if (!bookItem)
		return false;
	
	if (bookItem->GetType() != ITEM_TYPE_PET)
		return false;
	
	int iType = bookItem->GetValue(0);
	if ((iType > 12) || (iType < 1))
		return false;
	
	int ret = 0;
	bool bContinue = false;
	for (int i = 0; i < 4; i++) {
		if (iType == m_dwskillslot[i]) {
			ret = i;
			bContinue = true;
			break;
		}
	}
	
	if (!bContinue) {
#if defined(ENABLE_TEXTS_RENEWAL)
		m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 54, "");
#endif
		return false;
	}
	
	if (m_dwskill[ret] >= 10) {
#if defined(ENABLE_TEXTS_RENEWAL)
		m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 58, "");
#endif
		return false;
	}
	
	char szName[128];
	snprintf(szName, sizeof(szName), "pet_skills.%d", iType);
	int iLast = m_pkOwner->GetQuestFlag(szName);
	int iTime = iLast - get_global_time();
	if (iTime > 0) {
		if (m_pkOwner->FindAffect(AFFECT_SKILL_NO_BOOK_DELAY))
			m_pkOwner->RemoveAffect(AFFECT_SKILL_NO_BOOK_DELAY);
		else {
			int iHours = iTime / 3600;
			int iMinutes = (iTime - (iHours * 3600)) / 60;
#if defined(ENABLE_TEXTS_RENEWAL)
			m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 51, "%d#%d", iHours, iMinutes);
#endif
			return false;
		}
	}
	
	bookItem->SetCount(bookItem->GetCount() - 1);
	
	if (number(1, 100) < 30) {
#if defined(ENABLE_TEXTS_RENEWAL)
		m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 52, "");
#endif
		return false;
	}
	
	m_dwskill[ret] += 1;
	
#if defined(ENABLE_TEXTS_RENEWAL)
	m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 56, "%d", m_dwskill[ret]);
#endif
	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", ret, m_dwskillslot[ret], m_dwskill[ret]);
	
	ClearBuff();
	GiveBuff();
	
	m_pkOwner->SetQuestFlag(szName, get_global_time() + (3600 * 3));
	
	return true;
}

int CNewPetActor::ResetSkills() 
{
	bool bContinue = false;
	for (int i = 0; i < 4; i++) {
		if (m_dwskillslot[i] > 0) {
			bContinue = true;
			break;
		}
	}
	
	if (!bContinue)
		return 3;
	
	for (int i = 0; i < 4; i++) {
		if (m_dwskillslot[i] > 0)
			m_dwskillslot[i] = 0;
		
		m_dwskill[i] = 0;
		m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", i, m_dwskillslot[i], m_dwskill[i]);
	}
	
	ClearBuff();
	GiveBuff();
	
	return 1;
}

int CNewPetActor::ResetSkill(int iType) 
{
	int ret = 0;
	bool bContinue = false;
	for (int i = 0; i < 4; i++) {
		if (m_dwskillslot[i] == iType) {
			ret = i;
			bContinue = true;
			break;
		}
	}
	
	if (!bContinue)
		return 3;
	
	m_dwskillslot[ret] = 0;
	m_dwskill[ret] = 0;
	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", ret, m_dwskillslot[ret], m_dwskill[ret]);
	
	ClearBuff();
	GiveBuff();
	
	return 1;
}
#endif

bool CNewPetActor::IncreasePetEvolution() 
{
	if (m_dwevolution < 3) 
	{
		if ((GetLevel() >= 40 && m_dwevolution < 1 )||( GetLevel() >= 60 && m_dwevolution < 2 )||( GetLevel() >= 80 && m_dwevolution < 3) )
		{
			m_dwevolution += 1;
			m_pkChar->SendPetLevelUpEffect(m_pkChar->GetVID(), 1, GetLevel(), 1);
			m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetEvolution %d", m_dwevolution);
#if defined(ENABLE_TEXTS_RENEWAL)
			m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 747, "%d", m_dwevolution);
#endif
			if (m_dwevolution == 3) 
			{
				LPITEM pSummonItem = ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID());
				if (pSummonItem != NULL){
					Unsummon();
					Summon("Noname", pSummonItem, false);
				}
			}
			
#ifdef ENABLE_NEW_PET_EDITS
			SetLevel(GetLevel() + 1);
			m_pkChar->SendPetLevelUpEffect(m_pkChar->GetVID(), 1, GetLevel(), 1);
#ifdef ENABLE_NEW_PET_EDITS
			IncreasePetBonus();
#endif
			m_dwlevelstep = 0;
			m_dwexp = 0;
			m_dwexpitem = 0;
			m_pkChar->SetExp(0);
			m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetExp %d %d %d", m_dwexp, m_dwexpitem, m_pkChar->PetGetNextExp());
#endif
			int idx = m_dwevolution - 1;
			m_dwskill[idx] = 0;
			m_dwskillslot[idx] = 0;
			m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", idx, m_dwskillslot[idx], m_dwskill[idx]);
		}
		else
			return false;
	}
	else 
	{
#if defined(ENABLE_TEXTS_RENEWAL)
		m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 748, "");
#endif
		return false;
	}
	return true;
}

void CNewPetActor:: IncreasePetBonus() 
{
	int tmplevel = GetLevel();
	if (tmplevel % 5 == 0) {
		m_dwbonuspet[0][1] += float(number(1, 6));

	}
	if (tmplevel % 7 == 0) {
		m_dwbonuspet[1][1] += float(number(1, 6));
	}
	if (tmplevel % 4 == 0) {
		m_dwbonuspet[2][1] += float(number(1, 6));
	}
	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetBonus %d %d %d", m_dwbonuspet[0][1], m_dwbonuspet[1][1], m_dwbonuspet[2][1]);
	LPITEM pSummonItem = ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID());
	if (pSummonItem != NULL){
		for (int b = 0; b < 3; b++){
			pSummonItem->SetForceAttribute(b, 1, m_dwbonuspet[b][1]);
		}
		
	}
}

void CNewPetActor::SetNextExp(int nextExp)
{	
	m_dwExpFromMob = (nextExp/10)* 9;
	//m_dwExpFromMob = nextExp;
	//m_dwExpFromItem = 0;
	m_dwExpFromItem = nextExp - m_dwExpFromMob;
}

void CNewPetActor::SetLevel(DWORD level)
{
	m_pkChar->SetLevel(static_cast<char>(level));
	m_dwlevel = level;
	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetLevel %d", m_dwlevel);	
	SetNextExp(m_pkChar->PetGetNextExp());
	LPITEM pSummonItem = ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID());
	if (pSummonItem) {
#ifdef ENABLE_NEW_PET_EDITS
	pSummonItem->SetForceAttribute(3, 1, m_dwlevel);
#else
	pSummonItem->SetSocket(1,m_dwlevel);
#endif
	}
}

void CNewPetActor::SetEvolution(int lv) 
{
	if (lv == 40)
		m_dwevolution = 1;
	else if (lv == 60)
		m_dwevolution = 2;
	else if (lv == 80)
		m_dwevolution = 3;
}	

bool CNewPetActor::SetExp(uint32_t exp, int32_t mode) {
	if (exp < 0)
	{
		exp = MAX(m_dwexp - exp, 0);
	}

	if(mode == 0)
	{
#if defined(ENABLE_NEW_PET_EDITS)
		if (GetExp() + exp >= (DWORD) GetNextExpFromMob())
#else
		if(GetExp() + exp >= (DWORD) GetNextExpFromMob() && GetExpI() >= (DWORD) GetNextExpFromItem())
#endif
		{
			if (GetEvolution() == 0)
			{
				if (GetLevel() == 40)
				{
					m_dwexp = (DWORD) GetNextExpFromMob();
					m_pkChar->SetExp(m_dwexp - 1);
					m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetExp %d %d %d", m_dwexp - 1, m_dwexpitem, m_pkChar->PetGetNextExp());
					return false;
				}
				else if (GetLevel() > 40)
				{
					return false;
				}
			}
			else if (GetEvolution() <= 1)
			{
				if (GetLevel() == 60)
				{
					m_dwexp = (DWORD) GetNextExpFromMob();
					m_pkChar->SetExp(m_dwexp - 1);
					m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetExp %d %d %d", m_dwexp - 1, m_dwexpitem, m_pkChar->PetGetNextExp());
					return false;
				}
				else if (GetLevel() > 60)
				{
					return false;
				}
			}
			else if (GetEvolution() <= 2)
			{
				if (GetLevel() == 80)
				{
					m_dwexp = (DWORD) GetNextExpFromMob();
					m_pkChar->SetExp(m_dwexp - 1);
					m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetExp %d %d %d", m_dwexp - 1, m_dwexpitem, m_pkChar->PetGetNextExp());
					return false;
				}
				else if (GetLevel() > 80)
				{
					return false;
				}
			}
		}
	}
	else if(mode == 1)
	{
#if defined(ENABLE_NEW_PET_EDITS)
		if(GetExp() >= (DWORD) GetNextExpFromMob())
#else
		if(GetExpI() + exp >= (DWORD) GetNextExpFromItem() && GetExp() >= (DWORD) GetNextExpFromMob())
#endif
		{
			if (GetEvolution() == 0)
			{
				if (GetLevel() == 40)
				{
					m_dwexp = (DWORD) GetNextExpFromMob();
					m_pkChar->SetExp(m_dwexp);
					m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetExp %d %d %d", m_dwexp, m_dwexpitem, m_pkChar->PetGetNextExp());
					return false;
				}
				else if (GetLevel() > 40)
				{
					return false;
				}
			}
			else if (GetEvolution() <= 1)
			{
				if (GetLevel() == 60)
				{
					m_dwexp = (DWORD) GetNextExpFromMob();
					m_pkChar->SetExp(m_dwexp);
					m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetExp %d %d %d", m_dwexp, m_dwexpitem, m_pkChar->PetGetNextExp());
					return false;
				}
				else if (GetLevel() > 60)
				{
					return false;
				}
			}
			else if (GetEvolution() <= 2)
			{
				if (GetLevel() == 80)
				{
					m_dwexp = (DWORD) GetNextExpFromMob();
					m_pkChar->SetExp(m_dwexp);
					m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetExp %d %d %d", m_dwexp, m_dwexpitem, m_pkChar->PetGetNextExp());
					return false;
				}
				else if (GetLevel() > 80)
				{
					return false;
				}
			}
		}
	}

	if (mode == 0)  {
		if (GetExp() + exp >= (DWORD) GetNextExpFromMob())  {
#ifndef ENABLE_NEW_PET_EDITS
			if (GetExpI() >= (DWORD) GetNextExpFromItem())
#endif
			{
				SetLevel(GetLevel() + 1);
				m_pkChar->SendPetLevelUpEffect(m_pkChar->GetVID(), 1, GetLevel(), 1);
#ifndef ENABLE_NEW_PET_EDITS
				IncreasePetBonus();
#endif
				m_dwlevelstep = 0;
				m_dwexp = 0;
				m_dwexpitem = 0;
				m_pkChar->SetExp(0);
				m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetExp %d %d %d", m_dwexp, m_dwexpitem, m_pkChar->PetGetNextExp());
				//SetEvolution(GetLevel());
				return true;
			}
#ifndef ENABLE_NEW_PET_EDITS
			else {
				m_pkChar->SendPetLevelUpEffect(m_pkChar->GetVID(), 25, GetLevel(), 1);
				m_dwlevelstep = 4;
				exp = GetNextExpFromMob() - GetExp();
				m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetExp %d %d %d", m_dwexp, m_dwexpitem, m_pkChar->PetGetNextExp());
			}
#endif
		}
		
		m_dwexp += exp;
		m_pkChar->SetExp(m_dwexp);
		m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetExp %d %d %d", m_dwexp, m_dwexpitem, m_pkChar->PetGetNextExp());
		if (GetLevelStep() < 4) {
			DWORD dwNextExpQuart = GetNextExpFromMob() / 4;
			if (m_dwexp >= dwNextExpQuart * 3 && m_dwlevelstep == 2) {
				m_dwlevelstep = 3;
				m_pkChar->SendPetLevelUpEffect(m_pkChar->GetVID(), 25, GetLevel(), 1);
			} else if (m_dwexp >= dwNextExpQuart * 2 && m_dwlevelstep == 1) {
				m_dwlevelstep = 2;
				m_pkChar->SendPetLevelUpEffect(m_pkChar->GetVID(), 25, GetLevel(), 1);
			} else if (m_dwexp >= dwNextExpQuart && m_dwlevelstep == 0)  {
				m_dwlevelstep = 1;
				m_pkChar->SendPetLevelUpEffect(m_pkChar->GetVID(), 25, GetLevel(), 1);
			}
		}
	} else if (mode == 1)  {
		if (GetExpI() + exp >= (DWORD) GetNextExpFromItem()) {
			if (GetExp() >= (DWORD) GetNextExpFromMob()) 
			{
				m_dwexpitem = GetExpI() + exp - GetNextExpFromItem();
				m_dwexp = 0;
				m_pkChar->SetExp(0);
				m_dwlevelstep = 0;
				SetLevel(GetLevel() + 1);
				m_pkChar->SendPetLevelUpEffect(m_pkChar->GetVID(), 1, GetLevel(), 1);
#ifndef ENABLE_NEW_PET_EDITS
				IncreasePetBonus();
#endif
				m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetExp %d %d %d", m_dwexp, m_dwexpitem, m_pkChar->PetGetNextExp());
				return true;
			} else {
				exp = GetNextExpFromItem() - GetExpI();
				m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetExp %d %d %d", m_dwexp, m_dwexpitem, m_pkChar->PetGetNextExp());
			}
		}

		m_dwexpitem += exp;
		m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetExp %d %d %d", m_dwexp, m_dwexpitem, m_pkChar->PetGetNextExp());
	}

	return true;
}

bool CNewPetActor::Mount()
{
	if (0 == m_pkOwner)
		return false;

	if (true == HasOption(EPetOption_Mountable))
		m_pkOwner->MountVnum(m_dwVnum);

	return m_pkOwner->GetMountVnum() == m_dwVnum;;
}

void CNewPetActor::UpdateTime(bool now)
{
	m_dwTimePet += 1;
	if (m_dwTimePet >= 60 || now) {
		LPITEM pSummonItem = ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID());
		if (pSummonItem != NULL) {
			lMinAge = get_global_time() - dwMinAge;
			if (lMinAge >= 1296000 && m_dwskillslot[3] == -1) {
				m_dwskill[3] = 0;
				m_dwskillslot[3] = 0;
				m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", 3, m_dwskillslot[3], m_dwskill[3]);
			}
			
			int idx = m_idx;
			if (m_idx != 1 && lMinAge >= 86400) {
				m_idx = 1;
			}
			
			if (m_idx != 2 && lMinAge >= 950400) {
				m_idx = 2;
			}
			
			if (m_idx != 3 && lMinAge >= 2246400) {
				m_idx = 3;
			}
			
			if (m_idx != 4 && lMinAge >= 4147200) {
				m_idx = 4;
			}

			if (idx != m_idx || now) {
				ClearBuff();
				GiveBuff();
			}
		}
		
		if (m_dwtduration > 525600)
			return;
		
		m_dwduration -= 1;
		m_dwTimePet = 0;
		if (pSummonItem != NULL){
#ifdef ENABLE_NEW_PET_EDITS
			pSummonItem->SetSocket(1, m_dwduration);
#else
			pSummonItem->SetForceAttribute(3, 1, m_dwduration);
			pSummonItem->SetForceAttribute(4, 1, m_dwtduration);
#endif
		}
		m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetDuration %d %d", m_dwduration, m_dwtduration);
	}

}

void CNewPetActor::Unmount()
{
	if (0 == m_pkOwner)
		return;

	if (m_pkOwner->IsHorseRiding())
		m_pkOwner->StopRiding();
}

void CNewPetActor::Unsummon()
{
	if (true == this->IsSummoned())
	{
		LPITEM pSummonItem = ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID());

		if (pSummonItem != NULL)
		{
			std::unique_ptr<SQLMsg> msg(DBManager::instance().DirectQuery("UPDATE new_petsystem SET level = %d, evolution=%d, exp=%d, expi=%d, bonus0=%d, bonus1=%d, bonus2=%d, skill0=%d, skill0lv= %d, skill1=%d, skill1lv= %d, skill2=%d, skill2lv= %d, skill3=%d, skill3lv= %d, duration=%d, tduration=%d WHERE id = %lu ", this->GetLevel(), this->m_dwevolution, this->GetExp(), this->GetExpI(), this->m_dwbonuspet[0][1], this->m_dwbonuspet[1][1], this->m_dwbonuspet[2][1], this->m_dwskillslot[0], this->m_dwskill[0], this->m_dwskillslot[1], this->m_dwskill[1], this->m_dwskillslot[2], this->m_dwskill[2], this->m_dwskillslot[3], this->m_dwskill[3], this->m_dwduration, this->m_dwtduration, ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID())->GetID()));
			this->ClearBuff();

			for (int b = 0; b < 3; b++)
			{
				pSummonItem->SetForceAttribute(b, 1, m_dwbonuspet[b][1]);
			}
			
#ifdef ENABLE_NEW_PET_EDITS
			pSummonItem->SetForceAttribute(3, 1, m_dwlevel);
			pSummonItem->SetSocket(1, m_dwduration);
			pSummonItem->SetSocket(2, m_dwtduration);
#else
			pSummonItem->SetForceAttribute(3, 1, m_dwduration);
			pSummonItem->SetForceAttribute(4, 1, m_dwtduration);
			pSummonItem->SetSocket(1,m_dwlevel);
#endif
			pSummonItem->SetSocket(0, false);
			pSummonItem->Lock(false);
		}

		this->SetSummonItem(NULL);

		if (NULL != m_pkOwner)
			m_pkOwner->ComputePoints();

		if (NULL != m_pkChar)
			M2_DESTROY_CHARACTER(m_pkChar);

		m_pkChar = 0;
		m_dwVID = 0;
		m_dwlevel = 1;
		m_dwlevelstep = 0;
		m_dwExpFromMob = 0;
		m_dwExpFromItem = 0;
		m_dwexp = 0;
		m_dwexpitem = 0;
		m_dwTimePet = 0;
		m_dwImmTime = 0;
		m_dwslotimm = 0;

		for (int s = 0; s < 9; ++s)
		{
			m_dwpetslotitem[s] = -1;
		}

		ClearBuff();
		m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetUnsummon");
	}
}

DWORD CNewPetActor::Summon(const char* petName, LPITEM pSummonItem, bool bSpawnFar)
{
	long x = m_pkOwner->GetX();
	long y = m_pkOwner->GetY();
	long z = m_pkOwner->GetZ();

	if (true == bSpawnFar)
	{
		x += (number(0, 1) * 2 - 1) * number(2000, 2500);
		y += (number(0, 1) * 2 - 1) * number(2000, 2500);
	}
	else
	{
		x += number(-100, 100);
		y += number(-100, 100);
	}

	if (0 != m_pkChar)
	{
		m_pkChar->Show (m_pkOwner->GetMapIndex(), x, y);
		m_dwVID = m_pkChar->GetVID();
		m_pkChar->SetObserverMode(m_pkOwner->IsObserverMode());
		return m_dwVID;
	}
	int evolution = 0;
	int ivnum = pSummonItem != NULL ? pSummonItem->GetVnum() : 0;
	int evocation = 0;
	char szQuery2[1024];
	snprintf(szQuery2, sizeof(szQuery2), "SELECT evolution,evocation FROM new_petsystem WHERE id = %d ", pSummonItem->GetID());
	std::unique_ptr<SQLMsg> pmsg3(DBManager::instance().DirectQuery(szQuery2));
	if (pmsg3->Get()->uiNumRows > 0) {
		MYSQL_ROW row1 = mysql_fetch_row(pmsg3->Get()->pSQLResult);	
		evolution = atoi(row1[0]);
		evocation = atoi(row1[1]);
	}

	if(evocation == 0)
	{
		evocation = 1;
		std::unique_ptr<SQLMsg> msg(DBManager::instance().DirectQuery("UPDATE new_petsystem SET evocation = %d WHERE id = %lu ",evocation, pSummonItem->GetID()));
	}
#ifdef ENABLE_NEW_PET_EDITS
	else {
		if (pSummonItem && pSummonItem->GetSocket(1) <= 0) {
			return 0;
		}
	}
#endif

	m_dwVnum = 0;
	switch (ivnum) {
		case 55701:
			m_dwVnum = evolution == 3 ? 34042 : 34041;
			break;
		case 55702:
			m_dwVnum = evolution == 3 ? 34046 : 34045;
			break;
		case 55703:
			m_dwVnum = evolution == 3 ? 34050 : 34049;
			break;
		case 55704:
			m_dwVnum = evolution == 3 ? 34054 : 34053;
			break;
		case 55705:
			m_dwVnum = evolution == 3 ? 34037 : 34036;
			break;
		case 55706:
			m_dwVnum = evolution == 3 ? 34065 : 34064;
			break;
		case 55707:
			m_dwVnum = evolution == 3 ? 34074 : 34073;
			break;
		case 55708:
			m_dwVnum = evolution == 3 ? 34076 : 34075;
			break;
		case 55709:
			m_dwVnum = evolution == 3 ? 34081 : 34080;
			break;
		case 55710:
			m_dwVnum = evolution == 3 ? 34083 : 34082;
			break;
		case 55711:
			m_dwVnum = evolution == 3 ? 34096 : 34095;
			break;
		default:
			break;
	}

	if (m_dwVnum == 0) {
		sys_err("[CPetSystem::Summon] Invalid seal: %d.", ivnum);
		return 0;
	}

	m_pkChar = CHARACTER_MANAGER::instance().SpawnMob(
				m_dwVnum, 
				m_pkOwner->GetMapIndex(), 
				x, y, z,
				false, (int)(m_pkOwner->GetRotation()+180), false);

	if (0 == m_pkChar)
	{
		sys_err("[CPetSystem::Summon] Failed to summon the pet. (vnum: %d)", m_dwVnum);
		return 0;
	}

	m_pkChar->SetNewPet();
	
//	m_pkOwner->DetailLog();
//	m_pkChar->DetailLog();

	//楢税 厩亜研 爽昔税 厩亜稽 竺舛敗.
	m_pkChar->SetEmpire(m_pkOwner->GetEmpire());

	m_dwVID = m_pkChar->GetVID();

	char szQuery1[1024];
	snprintf(szQuery1, sizeof(szQuery1), "SELECT name,level,exp,expi,bonus0,bonus1,bonus2,skill0,skill0lv,skill1,skill1lv,skill2,skill2lv,skill3,skill3lv,duration,tduration,evolution "
#ifdef ENABLE_NEW_PET_EDITS
	", minAge "
#endif
	"FROM new_petsystem WHERE id = %d ", pSummonItem->GetID());
	std::unique_ptr<SQLMsg> pmsg2(DBManager::instance().DirectQuery(szQuery1));
	if (pmsg2->Get()->uiNumRows > 0) 
	{
		MYSQL_ROW row = mysql_fetch_row(pmsg2->Get()->pSQLResult);
		this->SetName(row[0]);
		this->SetLevel(atoi(row[1]));
		this->SetExp(atoi(row[2]), 0);
		this->SetExp(atoi(row[3]), 1);
		this->m_dwbonuspet[0][1] = atoi(row[4]);
		this->m_dwbonuspet[1][1] = atoi(row[5]);
		this->m_dwbonuspet[2][1] = atoi(row[6]);
		this->m_dwskillslot[0] = atoi(row[7]);
		this->m_dwskill[0] = atoi(row[8]);
		this->m_dwskillslot[1] = atoi(row[9]);
		this->m_dwskill[1] = atoi(row[10]);
		this->m_dwskillslot[2] = atoi(row[11]);
		this->m_dwskill[2] = atoi(row[12]);
		this->m_dwskillslot[3] = atoi(row[13]);
		this->m_dwskill[3] = atoi(row[14]);
		this->m_dwduration = atoi(row[15]);
		this->m_dwtduration = atoi(row[16]);
		this->m_dwevolution = atoi(row[17]);
#ifdef ENABLE_NEW_PET_EDITS
		this->dwMinAge = atoi(row[18]);
#endif
	}else
		this->SetName(petName);
	
//#ifdef ENABLE_NEW_PET_EDITS
	//if ((evocation == 0) && (this->m_dwduration < 1))
	//if (m_dwduration < 1) {
	//	return 0;
	//}
//#endif
	
	// SetSummonItem(pSummonItem)研 採献 板拭 ComputePoints研 採牽檎 獄覗 旋遂喫.
	this->SetSummonItem(pSummonItem);
	
	//this->SetNextExp(m_pkChar->PetGetNextExp());
	m_pkOwner->ComputePoints();
	m_pkChar->Show(m_pkOwner->GetMapIndex(), x, y, z);
	m_pkChar->SetObserverMode(m_pkOwner->IsObserverMode());

	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetIcon %d", m_dwSummonItemVnum);
	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetEvolution %d", m_dwevolution);
	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetName %s", m_name.c_str());
	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetLevel %d", m_dwlevel);
	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetDuration %d %d", m_dwduration, m_dwtduration);
	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetBonus %d %d %d",m_dwbonuspet[0][1], m_dwbonuspet[1][1], m_dwbonuspet[2][1]);
#ifndef ENABLE_NEW_PET_EDITS
	if (GetLevel() >= 80 && m_dwevolution == 3 )
	{
		m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", 0, m_dwskillslot[0], m_dwskill[0]);
		m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", 1, m_dwskillslot[1], m_dwskill[1]);
		m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", 2, m_dwskillslot[2], m_dwskill[2]);
		m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", 3, m_dwskillslot[3], m_dwskill[3]);
	}
	else 
	{
		m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", 0, -1, m_dwskill[0]);
		m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", 1, -1, m_dwskill[1]);
		m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", 2, -1, m_dwskill[2]);
		m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", 3, -1, m_dwskill[3]);
	}
#else
	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetAge %d", dwMinAge);
	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", 0, m_dwskillslot[0], m_dwskill[0]);
	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", 1, m_dwskillslot[1], m_dwskill[1]);
	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", 2, m_dwskillslot[2], m_dwskill[2]);
	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkill %d %d %d", 3, m_dwskillslot[3], m_dwskill[3]);
#endif
	
	m_pkOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetExp %d %d %d", m_dwexp, m_dwexpitem, m_pkChar->PetGetNextExp());
	lMinAge = get_global_time() - dwMinAge;
	m_idx = 0;
	
	UpdateTime(true);

	for (int b = 0; b < 3; b++){
		pSummonItem->SetForceAttribute(b, 1, m_dwbonuspet[b][1]);
	}
	
#ifdef ENABLE_NEW_PET_EDITS
	pSummonItem->SetForceAttribute(3, 1, m_dwlevel);
	pSummonItem->SetSocket(1, m_dwduration);
	pSummonItem->SetSocket(2, m_dwtduration);
#else
	pSummonItem->SetForceAttribute(3, 1, m_dwduration);
	pSummonItem->SetForceAttribute(4, 1, m_dwtduration);
	pSummonItem->SetSocket(1,m_dwlevel);
#endif
	pSummonItem->SetSocket(0, true);
	pSummonItem->Lock(true);
#ifdef ENABLE_RECALL
	const CAffect* pAffect = m_pkOwner->FindAffect(AFFECT_RECALL2);
	if (pAffect) {
		m_pkOwner->RemoveAffect(const_cast<CAffect*>(pAffect));
	}
	
	m_pkOwner->AddAffect(AFFECT_RECALL2, APPLY_NONE, 0, pSummonItem->GetID(), INFINITE_AFFECT_DURATION, 0, true, false);
#endif
	return m_dwVID;
}

bool CNewPetActor::_UpdatAloneActionAI(float fMinDist, float fMaxDist)
{
	float fDist = number(fMinDist, fMaxDist);
	float r = (float)number (0, 359);
	float dest_x = GetOwner()->GetX() + fDist * cos(r);
	float dest_y = GetOwner()->GetY() + fDist * sin(r);

	//m_pkChar->SetRotation(number(0, 359));        // 号狽精 沓棋生稽 竺舛

	//GetDeltaByDegree(m_pkChar->GetRotation(), fDist, &fx, &fy);

	// 汗充廃 公姶 紗失 端滴; 置曽 是帖人 掻娃 是帖亜 哀呪蒸陥檎 亜走 省澗陥.
	//if (!(SECTREE_MANAGER::instance().IsMovablePosition(m_pkChar->GetMapIndex(), m_pkChar->GetX() + (int) fx, m_pkChar->GetY() + (int) fy) 
	//			&& SECTREE_MANAGER::instance().IsMovablePosition(m_pkChar->GetMapIndex(), m_pkChar->GetX() + (int) fx/2, m_pkChar->GetY() + (int) fy/2)))
	//	return true;

	m_pkChar->SetNowWalking(true);

	//if (m_pkChar->Goto(m_pkChar->GetX() + (int) fx, m_pkChar->GetY() + (int) fy))
	//	m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0);
	if (!m_pkChar->IsStateMove() && m_pkChar->Goto(dest_x, dest_y))
		m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0);

	m_dwLastActionTime = get_dword_time();

	return true;
}

// char_state.cpp StateHorse敗呪 益撹 C&P -_-;
bool CNewPetActor::_UpdateFollowAI()
{
	if (0 == m_pkChar->m_pkMobData)
	{
		//sys_err("[CPetActor::_UpdateFollowAI] m_pkChar->m_pkMobData is NULL");
		return false;
	}
	
	// NOTE: 蝶遣斗(楢)税 据掘 戚疑 紗亀研 硝焼醤 馬澗汽, 背雁 葵(m_pkChar->m_pkMobData->m_table.sMovingSpeed)聖 送羨旋生稽 羨悦背辞 硝焼馨 呪亀 赤走幻
	// m_pkChar->m_pkMobData 葵戚 invalid廃 井酔亜 切爽 降持敗. 薄仙 獣娃淫域雌 据昔精 陥製拭 督焦馬壱 析舘精 m_pkChar->m_pkMobData 葵聖 焼森 紫遂馬走 省亀系 敗.
	// 食奄辞 古腰 伊紫馬澗 戚政澗 置段 段奄鉢 拝 凶 舛雌 葵聖 薦企稽 公条嬢神澗 井酔亀 赤製.. -_-;; ばばばばばばばばば
	if (0 == m_originalMoveSpeed)
	{
		const CMob* mobData = CMobManager::Instance().Get(m_dwVnum);

		if (0 != mobData)
			m_originalMoveSpeed = mobData->m_table.sMovingSpeed;
	}
	float	START_FOLLOW_DISTANCE = 300.0f;		// 戚 暗軒 戚雌 恭嬢走檎 耐焼亜奄 獣拙敗
	float	START_RUN_DISTANCE = 900.0f;		// 戚 暗軒 戚雌 恭嬢走檎 禽嬢辞 耐焼姶.

	float	RESPAWN_DISTANCE = 4500.f;			// 戚 暗軒 戚雌 菰嬢走檎 爽昔 新生稽 社発敗.
	int		APPROACH = 290;						// 羨悦 暗軒
	bool bRun = false;							// 禽嬢醤 馬蟹?

	DWORD currentTime = get_dword_time();

	long ownerX = m_pkOwner->GetX();		long ownerY = m_pkOwner->GetY();
	long charX = m_pkChar->GetX();			long charY = m_pkChar->GetY();

	float fDist = DISTANCE_APPROX(charX - ownerX, charY - ownerY);

	if (fDist >= RESPAWN_DISTANCE)
	{
		float fOwnerRot = m_pkOwner->GetRotation() * 3.141592f / 180.f;
		float fx = -APPROACH * cos(fOwnerRot);
		float fy = -APPROACH * sin(fOwnerRot);
		if (m_pkChar->Show(m_pkOwner->GetMapIndex(), ownerX + fx, ownerY + fy))
		{
			return true;
		}
	}
	
	
	if (fDist >= START_FOLLOW_DISTANCE)
	{
		if( fDist >= START_RUN_DISTANCE)
		{
			bRun = true;
		}

		m_pkChar->SetNowWalking(!bRun);		// NOTE: 敗呪 戚硯左壱 誇蓄澗闇匝 硝紹澗汽 SetNowWalking(false) 馬檎 禽澗暗績.. -_-;
		
		Follow(APPROACH);

		m_pkChar->SetLastAttacked(currentTime);
		m_dwLastActionTime = currentTime;
	}
	//else
	//{
	//	if (fabs(m_pkChar->GetRotation() - GetDegreeFromPositionXY(charX, charY, ownerX, ownerX)) > 10.f || fabs(m_pkChar->GetRotation() - GetDegreeFromPositionXY(charX, charY, ownerX, ownerX)) < 350.f)
	//	{
	//		m_pkChar->Follow(m_pkOwner, APPROACH);
	//		m_pkChar->SetLastAttacked(currentTime);
	//		m_dwLastActionTime = currentTime;
	//	}
	//}
	// Follow 掻戚走幻 爽昔引 析舛 暗軒 戚鎧稽 亜猿趨然陥檎 誇茶
	else 
		m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0);
	//else if (currentTime - m_dwLastActionTime > number(5000, 12000))
	//{
	//	this->_UpdatAloneActionAI(START_FOLLOW_DISTANCE / 2, START_FOLLOW_DISTANCE);
	//}

	return true;
}

bool CNewPetActor::Update(DWORD deltaTime)
{
	bool bResult = true;

	// 楢 爽昔戚 宋醸暗蟹, 社発吉 楢税 雌殿亜 戚雌馬陥檎 楢聖 蒸証. (NOTE: 亜懐亜陥 戚訓 煽訓 戚政稽 社発吉 楢戚 DEAD 雌殿拭 匙走澗 井酔亜 赤製-_-;)
	// 楢聖 社発廃 焼戚奴戚 蒸暗蟹, 鎧亜 亜遭 雌殿亜 焼艦虞檎 楢聖 蒸証.
#ifndef ENABLE_NEW_PET_EDITS
	if (IsSummoned()) {
		if (m_pkOwner->IsImmortal() && Pet_Skill_Table[16][2 + m_dwskill[m_dwslotimm]] <= (get_global_time() - m_dwImmTime)*10) {
			m_dwImmTime = 0;
			m_pkOwner->SetImmortal(0);
		}
	}
#endif
	
#ifdef DISABLE_TRADE_UNSUMMON
	//if (m_pkOwner->IsDead() || (IsSummoned() && m_pkChar->IsDead()) || (IsSummoned() && m_dwduration <= 0)
	if ((IsSummoned() && m_pkChar->IsDead()) || (IsSummoned() && m_dwduration <= 0)
		|| NULL == ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID())
		|| ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID())->GetOwner() != this->GetOwner()
		)
#else
	//if (m_pkOwner->IsDead() || (IsSummoned() && m_pkChar->IsDead()) || (IsSummoned() && (m_pkOwner->GetExchange() || m_pkOwner->GetMyShop() || m_pkOwner->GetShopOwner() || m_pkOwner->IsOpenSafebox() || m_pkOwner->IsCubeOpen() || m_dwduration <= 0))
	//if ((IsSummoned() && m_pkChar->IsDead()) || (IsSummoned() && (m_pkOwner->GetExchange() || m_pkOwner->GetMyShop() || m_pkOwner->GetShopOwner() || m_pkOwner->IsOpenSafebox() || m_pkOwner->IsCubeOpen() || m_dwduration <= 0))
	if ((IsSummoned() && m_pkChar->IsDead()) || (IsSummoned() && m_dwduration <= 0)
		|| NULL == ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID())
		|| ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID())->GetOwner() != this->GetOwner()
		)
#endif
	{
		this->Unsummon();
		return true;
	}

	if (this->IsSummoned() && HasOption(EPetOption_Followable))
		bResult = bResult && this->_UpdateFollowAI();

	return bResult;
}

//NOTE : 爽税!!! MinDistance研 滴惟 説生檎 益 痕是幻鏑税 痕鉢疑照精 follow馬走 省澗陥,
bool CNewPetActor::Follow(float fMinDistance)
{
	// 亜形澗 是帖研 郊虞坐醤 廃陥.
	if( !m_pkOwner || !m_pkChar) 
		return false;

	float fOwnerX = m_pkOwner->GetX();
	float fOwnerY = m_pkOwner->GetY();

	float fPetX = m_pkChar->GetX();
	float fPetY = m_pkChar->GetY();

	float fDist = DISTANCE_SQRT(fOwnerX - fPetX, fOwnerY - fPetY);
	if (fDist <= fMinDistance)
		return false;

	m_pkChar->SetRotationToXY(fOwnerX, fOwnerY);

	float fx, fy;

	float fDistToGo = fDist - fMinDistance;
	GetDeltaByDegree(m_pkChar->GetRotation(), fDistToGo, &fx, &fy);
	
	if (!m_pkChar->Goto((int)(fPetX+fx+0.5f), (int)(fPetY+fy+0.5f)) )
		return false;

	m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0, 0);

	return true;
}

void CNewPetActor::SetSummonItem (LPITEM pItem)
{
	if (NULL == pItem)
	{
		m_dwSummonItemVID = 0;
		m_dwSummonItemID = 0;
		m_dwSummonItemVnum = 0;
		return;
	}

	m_dwSummonItemVID = pItem->GetVID();
	m_dwSummonItemID = pItem->GetID();
	m_dwSummonItemVnum = pItem->GetVnum();
}

void CNewPetActor::GiveBuff()
{
#ifdef ENABLE_NEW_PET_EDITS
	int idx = 1;
	if ((lMinAge >= 950400) && (lMinAge < 2246400)) {
		idx = 2;
	} else if ((lMinAge >= 2246400) && (lMinAge < 4147200)) {
		idx = 3;
	} else if (lMinAge >= 4147200) {
		idx = 4;
	}

	int val[3][5] = {{POINT_MAX_HP, 500, 1200, 2100, 3000}, {POINT_RESIST_MONSTER, 2, 4, 7, 10}, {POINT_RESIST_MEZZIUOMINI, 2, 4, 7, 10}};

	for (int i = 0; i < 3; ++i) {
		m_pkOwner->AddAffect(AFFECT_NEW_PET, val[i][0], val[i][idx], 0, 60 * 60 * 24 * 365, 0, false);
		if (m_dwbonuspet[i][1] > 0) {
			m_pkOwner->AddAffect(AFFECT_NEW_PET, aApplyInfo[m_dwbonuspet[i][0]].bPointType, float(m_dwbonuspet[i][1]/10), 0, 60 * 60 * 24 * 365, 0, false);
		}
	}

	for (int i = 0; i < 4; i++) {
		idx = m_dwskillslot[i];
		if (idx != -1 && idx != 0) {
			m_pkOwner->AddAffect(AFFECT_NEW_PET, aApplyInfo[Pet_Skill_Table[m_dwskillslot[i]-1][1]].bPointType, Pet_Skill_Table[m_dwskillslot[i]-1][1+m_dwskill[i]], 0, 60 * 60 * 24 * 365, 0, false);
		}
	}
#else
	//Inizializzo i bonus del NewPetSystem //hp sp e def
	// 559 Affect NewPet
	int cbonus[3] = { m_pkOwner->GetMaxHP(),  m_pkOwner->GetPoint(POINT_DEF_GRADE), m_pkOwner->GetMaxSP() };
	for (int i = 0; i < 3; ++i) {
		m_pkOwner->AddAffect(AFFECT_NEW_PET, aApplyInfo[m_dwbonuspet[i][0]].bPointType, float((cbonus[i]*m_dwbonuspet[i][1]/10)/1000), 0,  60 * 60 * 24 * 365, 0, false);
	}
	
	//Inizializzo le skill del pet inattive  No 10-17-18 No 0 no -1
	//Condizione lv > 81 evo 3 Solo Skill Passive
	if (GetLevel() >= 80 && m_dwevolution == 3) 
	{
		for (int s = 0; s < 3; s++) 
		{
			switch (m_dwskillslot[s]) 
			{

			/*
				Pet_Skill_Table[m_dwskillslot[s] - 1][0]; //Mi ritorna il type della skill
				Pet_Skill_Table[m_dwskillslot[s] - 1][1]; // Mi ritorna attiva/passiva della skill 
				Pet_Skill_Table[m_dwskillslot[s] - 1][2]; // Mi ritorna il cd della skill
				Pet_Skill_Table[m_dwskillslot[s] - 1][2 + m_dwskill[s]]; //Mi ritorna l'apply della skill
			*/
			case 1: //Resistenza Guerriero 78 Punti				
			case 2: //Resistenza Sura 80
			case 3: //Resistenza Ninja 79
			case 4: //Resistenza Shamani 81
			case 6: //Valore Attacco 53 Punti
			case 9: //critici 25 Punti
			case 10: // exp 43
			case 13: // Blocco corp 27 Punti
			case 14: // Riflessione 28 Punti
			case 15: // Drop Yang 44 Punti
			case 16: //forte contro mostri 63
			case 17: //forte contro metin 116
			case 18: //forte contro boss 117
				m_pkOwner->AddAffect(AFFECT_NEW_PET, aApplyInfo[Pet_Skill_Table[m_dwskillslot[s] - 1][0]].bPointType, float(Pet_Skill_Table[m_dwskillslot[s] - 1][2 + m_dwskill[s]]/10), 0, 60 * 60 * 24 * 365, 0, false);
				break;
			default:
				return;
			}
		}
	}
#endif
}

void CNewPetActor::ClearBuff()
{
	m_pkOwner->RemoveAffect(AFFECT_NEW_PET);
}

void CNewPetActor::DoPetSkill(int skillslot) {
#ifdef ENABLE_NEW_PET_EDITS
	return;
#else
	if (GetLevel() < 80 || m_dwevolution < 3)
		return;
	switch (m_dwskillslot[skillslot]) 
	{
	case 10:
	{
		if (get_global_time() - m_pkOwner->GetNewPetSkillCD(0) <= 480) {
#if defined(ENABLE_TEXTS_RENEWAL)
			m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 749, "%d", (480 - (get_global_time() - m_pkOwner->GetNewPetSkillCD(0))));
#endif
			return;
		}
		if (m_pkOwner->GetHPPct() > 20) {
#if defined(ENABLE_TEXTS_RENEWAL)
			m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 750, "");
#endif
			return;
		}
		m_pkOwner->SetNewPetSkillCD(0, get_global_time());
		int riphp = MIN(m_pkOwner->GetHP() + (int)Pet_Skill_Table[9][2 + m_dwskill[skillslot]], m_pkOwner->GetMaxHP());
#if defined(ENABLE_TEXTS_RENEWAL)
		m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 751, "");
#endif
		m_pkOwner->PointChange(POINT_HP, riphp);
		m_pkOwner->EffectPacket(SE_HPUP_RED);
	}
	break;

	case 17:
	{
		if (get_global_time() - m_pkOwner->GetNewPetSkillCD(1) <= 600) {
#if defined(ENABLE_TEXTS_RENEWAL)
			m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 749, "%d", (600 - (get_global_time() - m_pkOwner->GetNewPetSkillCD(1))));
#endif
			return;
		}
		m_pkOwner->SetNewPetSkillCD(1, get_global_time());
#if defined(ENABLE_TEXTS_RENEWAL)
		m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 752, "");
#endif
		m_pkOwner->SetImmortal(1);
		m_dwslotimm = skillslot;
		m_dwImmTime = get_global_time();
	}
	break;
	case 18:
	{
		if (get_global_time() - m_pkOwner->GetNewPetSkillCD(2) <= 480) {
#if defined(ENABLE_TEXTS_RENEWAL)
			m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 749, "%d", (480 - (get_global_time() - m_pkOwner->GetNewPetSkillCD(2))));
#endif
			return;
		}
		m_pkOwner->SetNewPetSkillCD(2, get_global_time());
#if defined(ENABLE_TEXTS_RENEWAL)
		m_pkOwner->ChatPacketNew(CHAT_TYPE_INFO, 753, "");
#endif
		m_pkOwner->RemoveBadAffect();
	}
	break;
	
	default:
		return;
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////////////
//  CPetSystem
///////////////////////////////////////////////////////////////////////////////////////

CNewPetSystem::CNewPetSystem(LPCHARACTER owner)
{
//	assert(0 != owner && "[CPetSystem::CPetSystem] Invalid owner");

	m_pkOwner = owner;
	m_dwUpdatePeriod = 400;

	m_dwLastUpdateTime = 0;
}

CNewPetSystem::~CNewPetSystem()
{
	Destroy();
}

#ifdef ENABLE_NEW_PET_EDITS
bool CNewPetSystem::IncreasePetSkill(int iSlot, int iType) 
#else
bool CNewPetSystem::IncreasePetSkill(int skill) 
#endif
{
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned()) {
#ifdef ENABLE_NEW_PET_EDITS
				return petActor->IncreasePetSkill(iSlot, iType);
#else
				return petActor->IncreasePetSkill(skill);
#endif
			}
		}
	}
	return false;
}

#ifdef ENABLE_NEW_PET_EDITS
bool CNewPetSystem::IncreasePetSkillByBook(LPITEM bookItem) 
{
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned()) {
				return petActor->IncreasePetSkillByBook(bookItem);
			}
		}
	}
	return false;
}

int CNewPetSystem::ResetSkills() 
{
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned()) {
				return petActor->ResetSkills();
			}
		}
	}
	
	return 2;
}

int CNewPetSystem::ResetSkill(int iType) 
{
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned()) {
				return petActor->ResetSkill(iType);
			}
		}
	}
	
	return 2;
}
#endif

bool  CNewPetSystem::IncreasePetEvolution() {
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned()) {
				return petActor->IncreasePetEvolution();
			}
		}
	}
	return false;
}


void CNewPetSystem::Destroy()
{
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;

		if (0 != petActor)
		{
			delete petActor;
		}
	}
	event_cancel(&m_pkNewPetSystemUpdateEvent);
	event_cancel(&m_pkNewPetSystemExpireEvent);
	m_petActorMap.clear();
}


void CNewPetSystem::UpdateTime()
{
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;

		if (0 != petActor && petActor->IsSummoned())
		{
			petActor->UpdateTime();
		}
	}
}
/// 楢 獣什奴 穣汽戚闘. 去系吉 楢級税 AI 坦軒 去聖 敗.
bool CNewPetSystem::Update(DWORD deltaTime)
{
	bool bResult = true;

	DWORD currentTime = get_dword_time();

	// CHARACTER_MANAGER拭辞 蝶遣斗嫌 Update拝 凶 古鯵痕呪稽 爽澗 (Pulse虞壱 鞠嬢赤澗)葵戚 戚穿 覗傾績引税 獣娃託戚昔匝 硝紹澗汽
	// 穿粕 陥献 葵戚虞辞-_-; 食奄拭 脊径生稽 級嬢神澗 deltaTime精 税耕亜 蒸製ばば	
	
	if (m_dwUpdatePeriod > currentTime - m_dwLastUpdateTime)
		return true;
	
	std::vector <CNewPetActor*> v_garbageActor;

	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;

		if (0 != petActor && petActor->IsSummoned())
		{
			LPCHARACTER pPet = petActor->GetCharacter();
			
			if (NULL == CHARACTER_MANAGER::instance().Find(pPet->GetVID()))
			{
				v_garbageActor.push_back(petActor);
			}
			else
			{
				bResult = bResult && petActor->Update(deltaTime);
			}
		}
	}
	for (std::vector<CNewPetActor*>::iterator it = v_garbageActor.begin(); it != v_garbageActor.end(); it++)
		DeletePet(*it);

	m_dwLastUpdateTime = currentTime;

	return bResult;
}

/// 淫軒 鯉系拭辞 楢聖 走崇
void CNewPetSystem::DeletePet(DWORD mobVnum)
{
	TNewPetActorMap::iterator iter = m_petActorMap.find(mobVnum);

	if (m_petActorMap.end() == iter)
	{
		sys_err("[CPetSystem::DeletePet] Can't find pet on my list (VNUM: %d)", mobVnum);
		return;
	}

	CNewPetActor* petActor = iter->second;

	if (0 == petActor)
		sys_err("[CPetSystem::DeletePet] Null Pointer (petActor)");
	else
		delete petActor;

	m_petActorMap.erase(iter);	
}

/// 淫軒 鯉系拭辞 楢聖 走崇
void CNewPetSystem::DeletePet(CNewPetActor* petActor)
{
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		if (iter->second == petActor)
		{
			delete petActor;
			m_petActorMap.erase(iter);

			return;
		}
	}

	sys_err("[CPetSystem::DeletePet] Can't find petActor(0x%x) on my list(size: %d) ", petActor, m_petActorMap.size());
}

void CNewPetSystem::Unsummon(DWORD vnum, bool bDeleteFromList)
{
	CNewPetActor* actor = this->GetByVnum(vnum);

	if (0 == actor)
	{
		sys_err("[CPetSystem::GetByVnum(%d)] Null Pointer (petActor)", vnum);
		return;
	}
	actor->Unsummon();

	if (true == bDeleteFromList)
		this->DeletePet(actor);

	bool bActive = false;
	for (TNewPetActorMap::iterator it = m_petActorMap.begin(); it != m_petActorMap.end(); it++)
	{
		bActive |= it->second->IsSummoned();
	}
	if (false == bActive)
	{
		event_cancel(&m_pkNewPetSystemUpdateEvent);
		event_cancel(&m_pkNewPetSystemExpireEvent);
		m_pkNewPetSystemUpdateEvent = NULL;
		m_pkNewPetSystemExpireEvent = NULL;
	}
}

void CNewPetSystem::UnsummonAll(LPCHARACTER ch)
{
	if (!ch)
		return;
	
#ifdef ENABLE_RECALL
	const CAffect* pAffect = ch->FindAffect(AFFECT_RECALL2);
	if (pAffect) {
		ch->RemoveAffect(const_cast<CAffect*>(pAffect));
	}
#endif
	
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned()) {
				petActor->Unsummon();
				break;
			}
		}
	}
	
	if (m_pkNewPetSystemUpdateEvent) {
		event_cancel(&m_pkNewPetSystemUpdateEvent);
		m_pkNewPetSystemUpdateEvent = NULL;
	}
	
	if (m_pkNewPetSystemExpireEvent) {
		event_cancel(&m_pkNewPetSystemExpireEvent);
		m_pkNewPetSystemExpireEvent = NULL;
	}
}

DWORD CNewPetSystem::GetNewPetITemID()
{
	DWORD itemid = 0;
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned()) {
				itemid = petActor->GetSummonItemID();
				break;
			}			
		}
	}
	return itemid;

}

bool CNewPetSystem::IsActivePet()
{
	bool state = false;
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned()) {
				state = true;
				break;
			}			
		}
	}
	return state;

}

int CNewPetSystem::GetLevelStep()
{
	int step = 4;
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned()) {
				step = petActor->GetLevelStep();
				break;
			}
		}
	}
	return step;
}

bool CNewPetSystem::SetExp(int iExp, int mode)
{
	bool ret = false;

	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned() && petActor->SetExp(iExp, mode)) {
				ret = true;
				break;
			}
		}
	}

	return ret;
}

int CNewPetSystem::GetEvolution()
{
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned()) {
				return petActor->GetEvolution();
			}
		}
	}
	return -1;
}

int CNewPetSystem::GetLevel()
{
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned()) {
				return petActor->GetLevel();
			}
		}
	}
	return -1;
}

int CNewPetSystem::GetExp()
{
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned()) {
				return petActor->GetExp();
			}
		}
	}
	return 0;
}

#ifdef ENABLE_NEW_PET_EDITS
int CNewPetSystem::GetNextExpFromMob()
{
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned()) {
				return petActor->GetNextExpFromMob();
			}
		}
	}
	return 0;
}
#endif

void CNewPetSystem::SetItemCube(int pos, int invpos) {
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned()) {
				return petActor->SetItemCube(pos, invpos);
			}
		}
	}
}

void CNewPetSystem::ItemCubeFeed(int type) {
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned()) {
				return petActor->ItemCubeFeed(type);
			}
		}
	}
}

void CNewPetSystem::DoPetSkill(int skillslot) {
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;
		if (petActor != 0)
		{
			if (petActor->IsSummoned()) {
				return petActor->DoPetSkill(skillslot);
			}
		}
	}
}



CNewPetActor* CNewPetSystem::Summon(DWORD mobVnum, LPITEM pSummonItem, const char* petName, bool bSpawnFar, DWORD options)
{
	CNewPetActor* petActor = this->GetByVnum(mobVnum);

	if (0 == petActor) {
		petActor = M2_NEW CNewPetActor(m_pkOwner, mobVnum, options);
		m_petActorMap.insert(std::make_pair(mobVnum, petActor));
	}

	DWORD petVID = petActor->Summon(petName, pSummonItem, bSpawnFar);
	if (petVID == 0) {
		if (mobVnum != 0) {
			DeletePet(mobVnum);
		}

		sys_err("[CPetSystem::Summon] Failed to summon the pet. (sealVnum: %u, mobVnum: %u)", pSummonItem ? pSummonItem->GetVnum() : 0, mobVnum);
		return NULL;
	}

	sys_log(0, "Summon: %d", petVID);

	if (NULL == m_pkNewPetSystemUpdateEvent)
	{
		newpetsystem_event_info* info = AllocEventInfo<newpetsystem_event_info>();

		info->pPetSystem = this;

		m_pkNewPetSystemUpdateEvent = event_create(newpetsystem_update_event, info, PASSES_PER_SEC(1) / 4);	// 0.25段	
	}

	if (NULL == m_pkNewPetSystemExpireEvent)
	{
		newpetsystem_event_infoe* infoe = AllocEventInfo<newpetsystem_event_infoe>();

		infoe->pPetSystem = this;

		m_pkNewPetSystemExpireEvent = event_create(newpetsystem_expire_event, infoe, PASSES_PER_SEC(1) );	// 1 volata per sec
	}

	return petActor;
}


CNewPetActor* CNewPetSystem::GetByVID(DWORD vid) const
{
	CNewPetActor* petActor = 0;

	bool bFound = false;

	for (TNewPetActorMap::const_iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		petActor = iter->second;

		if (0 == petActor)
		{
			sys_err("[CPetSystem::GetByVID(%d)] Null Pointer (petActor)", vid);
			continue;
		}

		bFound = petActor->GetVID() == vid;

		if (true == bFound)
			break;
	}

	return bFound ? petActor : 0;
}

/// 去系 吉 楢 掻拭辞 爽嬢遭 光 VNUM聖 亜遭 衝斗研 鋼発馬澗 敗呪.
CNewPetActor* CNewPetSystem::GetByVnum(DWORD vnum) const
{
	CNewPetActor* petActor = 0;

	TNewPetActorMap::const_iterator iter = m_petActorMap.find(vnum);

	if (m_petActorMap.end() != iter)
		petActor = iter->second;

	return petActor;
}

size_t CNewPetSystem::CountSummoned() const
{
	size_t count = 0;

	for (TNewPetActorMap::const_iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;

		if (0 != petActor)
		{
			if (petActor->IsSummoned())
				++count;
		}
	}

	return count;
}

void CNewPetSystem::RefreshBuff()
{
	for (TNewPetActorMap::const_iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CNewPetActor* petActor = iter->second;

		if (0 != petActor)
		{
			if (petActor->IsSummoned())
			{
				petActor->ClearBuff();
				petActor->GiveBuff();
			}
		}
	}
}

void CNewPetActor::ChangeName(const char * name) {
	char query2[256] = {0};
	snprintf(query2, sizeof(query2), "UPDATE player.new_petsystem SET name='%s' WHERE name='%s' LIMIT 1;", name, m_name.c_str());
	std::unique_ptr<SQLMsg> pRes(DBManager::instance().DirectQuery(query2));

	LPITEM pSummonItem = ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID());
	if (pSummonItem != NULL){
		Unsummon();
		Summon("Noname", pSummonItem, false);
	}
}

void CNewPetSystem::ChangeName(const char * name)
{
	for (TNewPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter) {
		CNewPetActor* petActor = iter->second;
		if (petActor != 0) {
			if (petActor->IsSummoned()) {
				return petActor->ChangeName(name);
			}
		}
	}
}

void CNewPetSystem::UpdateObserver(bool bFlag)
{
	if (!m_pkOwner)
		return;

	for (auto iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		const CNewPetActor* petActor = iter->second;
		if (petActor == nullptr)
			continue;

		const LPCHARACTER petCh = petActor->GetCharacter();
		if (petCh)
			petCh->SetObserverMode(bFlag);
	}
}
