/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#include "entities/character.h"
#include "entity.h"
#include "gamecontext.h"
#include "gameworld.h"


//////////////////////////////////////////////////
// game world
//////////////////////////////////////////////////
CGameWorld::CGameWorld()
{
}

CGameWorld::~CGameWorld()
{
}

void CGameWorld::SetGameServer(CGameContext *pGameServer)
{
}

CEntity *CGameWorld::FindFirst(int Type)
{
	return Type < 0 || Type >= NUM_ENTTYPES ? 0 : m_apFirstEntityTypes[Type];
}

int CGameWorld::FindEntities(vec2 Pos, float Radius, CEntity **ppEnts, int Max, int Type)
{
	return 0;
}

void CGameWorld::InsertEntity(CEntity *pEnt)
{
}

void CGameWorld::DestroyEntity(CEntity *pEnt)
{
}

void CGameWorld::RemoveEntity(CEntity *pEnt)
{
}

//
void CGameWorld::Snap(int SnappingClient)
{
}

void CGameWorld::PostSnap()
{
}

void CGameWorld::Reset()
{
}

void CGameWorld::RemoveEntities()
{
}

void CGameWorld::Tick()
{
}


// TODO: should be more general
CCharacter *CGameWorld::IntersectCharacter(vec2 Pos0, vec2 Pos1, float Radius, vec2& NewPos, CEntity *pNotThis)
{
	return nullptr;
}


CEntity *CGameWorld::ClosestEntity(vec2 Pos, float Radius, int Type, CEntity *pNotThis)
{
	return nullptr;
}
