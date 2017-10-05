#include <stdio.h>
#include <string>
#include <thread>
#include <mutex>
#include <list>
#include <map>
#include <fcntl.h>

// Important for amxplugin.cpp aswell!
#define HAVE_STDINT_H

#include "SDK/plugin.h"

#define BUF_LEN								(2048)
#if defined __WIN32__ || defined _WIN32 || defined WIN32
#	define ETI_popen(_cmd,_params)			_popen(_cmd,_params)
#	define ETI_pclose(_file)				_pclose(_file)
#	define TYPENAME							typename
#else
#	define ETI_popen(_cmd,_params)			popen(_cmd,_params)
#	define ETI_pclose(_file)				pclose(_file)
#	define TYPENAME							
#endif

#define list_foreach(type,_list,var)		for(std::list<type>::iterator (var)=(_list).begin();(var)!=(_list).end();++(var))
#define map_foreach(type1,type2,_map,var)	for(std::map<type1,type2>::iterator (var)=(_map).begin();(var)!=(_map).end();++(var))

#include "exception.h"

template <class _T> class CTR
{
public:
	typename std::map<_T, typename std::list<_T>::iterator> _map;
	typename std::list<_T> _list;
	TYPENAME void Add(_T ptr);
	typename std::list<_T>::iterator Delete(_T ptr);
	TYPENAME bool Exists(_T ptr);
	void Clear();
	void CleanUp();
	void Destruct();
};

class ShellThread
{
private:
	FILE *pipe_handle;
	std::thread *thread;
	std::list<std::string> msgs;
	bool joinable, quit_it;
	ShellThread();
	ShellThread(const ShellThread &);
public:
	ShellThread(std::string *exec_str);
	~ShellThread();
	void ThreadedCall();
	void CloseHandle();
	std::thread *GetThread();
	bool Joinable();
};

struct CMDRet
{
	std::string str;
	cell handle;
};

struct CallbackInfo
{
	AMX *amx;
	int orsm_idx, ors_idx;
};

//#define PLUGIN_DEBUG