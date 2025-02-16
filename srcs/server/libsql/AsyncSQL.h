#ifndef __INC_METIN_II_ASYNCSQL_H__
#define __INC_METIN_II_ASYNCSQL_H__

#include "../libthecore/stdafx.h"

#include <string>
#include <queue>
#include <vector>
#include <map>
#include <mariadb/mysql.h>

#include "Semaphore.h"

#define QUERY_MAX_LEN 8192

typedef struct _SQLResult
{
	_SQLResult()
		: pSQLResult(nullptr), uiNumRows(0), uiAffectedRows(0), uiInsertID(0)
	{
	}

	~_SQLResult()
	{
		if (pSQLResult)
		{
			mysql_free_result(pSQLResult);
			pSQLResult = nullptr;
		}
	}

	MYSQL_RES* pSQLResult;
	uint32_t uiNumRows;
	uint32_t uiAffectedRows;
	uint32_t uiInsertID;
} SQLResult;

typedef struct _SQLMsg
{
	_SQLMsg()
		: m_pkSQL(nullptr), iID(0), uiResultPos(0), pvUserData(nullptr), bReturn(false), uiSQLErrno(0)
	{
	}

	~_SQLMsg()
	{
		std::vector<SQLResult*>::iterator first = vec_pkResult.begin();
		std::vector<SQLResult*>::iterator past = vec_pkResult.end();

		while (first != past)
			delete *(first++);

		vec_pkResult.clear();
	}

	void Store()
	{
		do
		{
			SQLResult* pRes = new SQLResult;

			pRes->pSQLResult = mysql_store_result(m_pkSQL);
			pRes->uiInsertID = mysql_insert_id(m_pkSQL);
			pRes->uiAffectedRows = mysql_affected_rows(m_pkSQL);

			if (pRes->pSQLResult)
			{
				pRes->uiNumRows = mysql_num_rows(pRes->pSQLResult);
			}
			else
			{
				pRes->uiNumRows = 0;
			}

			vec_pkResult.push_back(pRes);
		}
		while (!mysql_next_result(m_pkSQL));
	}

	SQLResult* Get()
	{
		if (uiResultPos >= vec_pkResult.size())
			return nullptr;

		return vec_pkResult[uiResultPos];
	}

	bool Next()
	{
		if (uiResultPos + 1 >= vec_pkResult.size())
			return false;

		++uiResultPos;
		return true;
	}

	MYSQL* m_pkSQL;
	int32_t iID;
	std::string stQuery;

	std::vector<SQLResult*> vec_pkResult;
	uint32_t uiResultPos;

	void* pvUserData;
	bool bReturn;

	uint32_t uiSQLErrno;
} SQLMsg;

class CAsyncSQL
{
public:
	CAsyncSQL();
	virtual ~CAsyncSQL();

	void Quit();

	bool Setup(const char* c_pszHost, const char* c_pszUser, const char* c_pszPassword, const char* c_pszDB,
	           const char* c_pszLocale,
	           bool bNoThread = false, int32_t iPort = 0);
	bool Setup(CAsyncSQL* sql, bool bNoThread = false);

	bool Connect();
	bool IsConnected() const { return m_bConnected; }
	bool QueryLocaleSet();

	void AsyncQuery(const char* c_pszQuery);
	void ReturnQuery(const char* c_pszQuery, void* pvUserData);
	SQLMsg* DirectQuery(const char* c_pszQuery);

	uint32_t CountQuery();
	uint32_t CountResult();

	void PushResult(SQLMsg* p);
	bool PopResult(SQLMsg** pp);

	void ChildLoop();

	MYSQL* GetSQLHandle();

	int32_t CountQueryFinished();
	void ResetQueryFinished();

	size_t EscapeString(char* dst, size_t dstSize, const char* src, size_t srcSize);

protected:
	void Destroy();

	void PushQuery(SQLMsg* p);

	bool PeekQuery(SQLMsg** pp);
	bool PopQuery(int32_t iID);

	bool PeekQueryFromCopyQueue(SQLMsg** pp);
	int32_t CopyQuery();
	bool PopQueryFromCopyQueue();

public:
	int32_t GetCopiedQueryCount();
	void ResetCopiedQueryCount();
	void AddCopiedQueryCount(int32_t iCopiedQuery);

	//private:
protected:
	MYSQL m_hDB{};

	std::string m_stHost;
	std::string m_stUser;
	std::string m_stPassword;
	std::string m_stDB;
	std::string m_stLocale;

	int32_t m_iMsgCount;
	int32_t m_aiPipe[2]{};
	int32_t m_iPort;

	std::queue<SQLMsg*> m_queue_query;
	std::queue<SQLMsg*> m_queue_query_copy;
	//std::map<int32_t, SQLMsg *>	m_map_kSQLMsgUnfinished;

	std::queue<SQLMsg*> m_queue_result;

	volatile bool m_bEnd;

#ifndef _WIN32
		pthread_t m_hThread;
		pthread_mutex_t	* m_mtxQuery;
		pthread_mutex_t	* m_mtxResult;
#else
	HANDLE m_hThread;
	CRITICAL_SECTION* m_mtxQuery;
	CRITICAL_SECTION* m_mtxResult;
#endif

	CSemaphore m_sem;

	int32_t m_iQueryFinished;

	uint32_t m_ulThreadID;
	bool m_bConnected;
	int32_t m_iCopiedQuery;
};

class CAsyncSQL2 : public CAsyncSQL
{
public:
	void SetLocale(const std::string& stLocale);
};

#endif
