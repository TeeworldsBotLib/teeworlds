/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <engine/shared/config.h>

#include <generated/server_data.h>
#include <game/server/gamecontext.h>
#include <game/server/player.h>

#include "character.h"
#include "base/system.h"

#include <bots/sample.h>
#include <server/set_state.h>
#include <shared/hotreload.h>
#include <shared/types.h>

//input count
struct CInputCount
{
	int m_Presses;
	int m_Releases;
};

CInputCount CountInput(int Prev, int Cur)
{
	CInputCount c = {0, 0};
	return c;
}


MACRO_ALLOC_POOL_ID_IMPL(CCharacter, MAX_CLIENTS)

// Character, "physical" player's part
CCharacter::CCharacter(CGameWorld *pWorld)
: CEntity(pWorld, CGameWorld::ENTTYPE_CHARACTER, vec2(0, 0), ms_PhysSize)
{
}

void CCharacter::Reset()
{
}

bool CCharacter::Spawn(CPlayer *pPlayer, vec2 Pos)
{
	return true;
}

void CCharacter::Destroy()
{
}

void CCharacter::SetWeapon(int W)
{
}

bool CCharacter::IsGrounded()
{
	return false;
}


void CCharacter::HandleNinja()
{
}


void CCharacter::DoWeaponSwitch()
{
}

void CCharacter::HandleWeaponSwitch()
{
}

void CCharacter::FireWeapon()
{
}

void CCharacter::HandleWeapons()
{
	return;
}

bool CCharacter::GiveWeapon(int Weapon, int Ammo)
{
	return false;
}

void CCharacter::GiveNinja()
{
}

void CCharacter::SetEmote(int Emote, int Tick)
{
}

void CCharacter::OnPredictedInput(CNetObj_PlayerInput *pNewInput)
{
}

void CCharacter::OnDirectInput(CNetObj_PlayerInput *pNewInput)
{
}

void CCharacter::ResetInput()
{
}

void CCharacter::Tick()
{
	CServerBotStateOut Bot;
	CServerBotStateIn State;

	TWBL::SetState(this, &State);
	State.m_pCollision = GameServer()->Collision();

	FTwbl_BotTick BotTick;
	void *pHandle = TWBL::LoadTick(Config()->m_SvSoPath, Config()->m_SvTick, &BotTick);

	//  If filename is NULL, then the returned handle is for the main progra

	if(pHandle)
	{
		BotTick(&State, &Bot);
		int Err = dlclose(pHandle);
		if(Err)
		{
			dbg_msg("twbl", "failed to close err=%d", Err);
		}
		dlerror();
	}
	// else
	// 	Twbl_SampleTick(&State, &Bot);

	// void *pMain = dlopen(NULL, RTLD_LAZY);
	// if(pMain && pMain == pHandle)
	// {
	// 	dbg_msg("twbl", "woah there! pHandle == pMain thats not loading external stuff");
	// }
	// dlclose(pMain);

	// dbg_msg("srv", "%s %s", g_Config.m_SvSoPath, g_Config.m_SvTick);
	// dbg_msg("srv", "f=%s handle=%p main=%p callback=%p native=%p", g_Config.m_SvTick, pHandle, pMain, BotTick, Twbl_SampleTick);
	// dbg_msg("srv", "'%s' handle=%p callback=%p native=%p", g_Config.m_SvTick, pHandle, BotTick, Twbl_SampleTick);

	dbg_msg("srv", "%s '%s' fp=%p static=%p", Config()->m_SvSoPath, Config()->m_SvTick, BotTick, Twbl_SampleTick);
	BotTick = nullptr;

	m_Input.m_Direction = Bot.m_Direction;



	dbg_msg("foo", "bar");

	m_Core.m_Input = m_Input;
	m_Core.Tick(true);

	// handle leaving gamelayer
	if(GameLayerClipped(m_Pos))
	{
		Die(m_pPlayer->GetCID(), WEAPON_WORLD);
	}

	// handle Weapons
	HandleWeapons();
}

void CCharacter::TickDefered()
{
}

void CCharacter::TickPaused()
{
}

bool CCharacter::IncreaseHealth(int Amount)
{
	return true;
}

bool CCharacter::IncreaseArmor(int Amount)
{
	return true;
}

void CCharacter::Die(int Killer, int Weapon)
{
}

bool CCharacter::TakeDamage(vec2 Force, vec2 Source, int Dmg, int From, int Weapon)
{

	return true;
}

void CCharacter::Snap(int SnappingClient)
{
}

void CCharacter::PostSnap()
{
}
