#ifndef __PYTHON_CONFIG_HEADER__
#define __PYTHON_CONFIG_HEADER__

#include "StdAfx.h"

#ifdef ENABLE_CONFIG_MODULE
#include <minini_12b/minIni.h>

class CPythonConfig : public CSingleton<CPythonConfig>
{
public:
	enum EClassTypes
	{
		CLASS_GENERAL,
		CLASS_CHAT,
		CLASS_OPTION,
	};

public:
	CPythonConfig();
	~CPythonConfig();
	void Initialize(const std::string& stFileName);
	
	void Initialize_LoadDefault(EClassTypes eType, const std::string& stKey, float fDefaultValue);
	void Initialize_LoadDefault(EClassTypes eType, const std::string& stKey, const std::string& stDefaultValue);
	void Initialize_LoadDefaults();

	std::string	GetClassNameByType(EClassTypes eType) const;

	void		Write(EClassTypes eType, const std::string& stKey, const std::string& stValue);
	void		Write(EClassTypes eType, const std::string& stKey, const char* szValue);
	void		Write(EClassTypes eType, const std::string& stKey, int iValue);
	void		Write(EClassTypes eType, const std::string& stKey, bool bValue);

	std::string	GetString(EClassTypes eType, const std::string& stKey, const std::string& stDefaultValue = "") const;
	int			GetInteger(EClassTypes eType, const std::string& stKey, int iDefaultValue = 0) const;
	float		GetFloat(EClassTypes eType, const std::string& stKey, float fDefaultValue = 0.0f) const;
	bool		GetBool(EClassTypes eType, const std::string& stKey, bool bDefaultValue = false) const;

	void		RemoveSection(EClassTypes eType);

private:
	minIni*		m_pkIniFile;
	std::string	m_stFileName;
};
#endif

#endif
