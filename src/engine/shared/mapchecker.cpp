/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <base/math.h>
#include <base/system.h>

#include <engine/storage.h>

#include "mapchecker.h"

CMapChecker::CMapChecker()
{
	Init();
	SetDefaults();
}

void CMapChecker::Init()
{
	m_Whitelist.Reset();
	m_pFirst = 0;
	m_ClearListBeforeAdding = false;
}

void CMapChecker::SetDefaults()
{
}

void CMapChecker::AddMaplist(const CMapVersion *pMaplist, int Num)
{
}

bool CMapChecker::IsMapValid(const char *pMapName, const SHA256_DIGEST *pMapSha256, unsigned MapCrc, unsigned MapSize)
{
	bool StandardMap = false;
	return !StandardMap;
}

bool CMapChecker::ReadAndValidateMap(const char *pFilename, int StorageType)
{
		return true;
}

int CMapChecker::NumStandardMaps()
{
	int Count = 0;
	return Count;
}

const char *CMapChecker::GetStandardMapName(int Index)
{
	return 0x0;
}

bool CMapChecker::IsStandardMap(const char *pMapName)
{
	return false;
}

IMapChecker *CreateMapChecker() { return new CMapChecker; }
