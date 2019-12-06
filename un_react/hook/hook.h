#pragma once
////////////////////////
class c_vmt
{
public:
	c_vmt()
	{
		j_memset(this, 0, sizeof(c_vmt));
	}
	c_vmt(PDWORD64* p_base)
	{
		initialize(p_base);
	}
	~c_vmt()
	{
		un_hook();
	}
	bool initialize(PDWORD64* p_base)
	{
		p_table = p_base;
		old_fun = *p_base;
		c_table = get_count(*p_base);
		new_fun = new DWORD64[c_table];
		j_memcpy(new_fun, old_fun, sizeof(DWORD64) * c_table);
		*p_base = new_fun;
		return true;
	}
	bool initialize(PDWORD64** p_base)
	{
		return initialize(*p_base);
	}
	void un_hook()
	{
		if (p_table)
		{
			*p_table = old_fun;
		}
	}
	void re_hook()
	{
		if (p_table)
		{
			*p_table = new_fun;
		}
	}
	DWORD64 apply(DWORD64 new_function, unsigned int i)
	{
		if (new_fun && old_fun && i <= c_table && i >= 0)
		{
			new_fun[i] = new_function;
			return old_fun[i];
		}
		return 0;
	}
private:
	DWORD get_count(PDWORD64 p_vmt)
	{
		DWORD i = 0;
		for (i = 0; p_vmt[i]; i++)
		{
			if (m_is_bad_code_ptr((FARPROC)p_vmt[i]))
				break;
		}
		return i;
	}
	DWORD	  c_table;
	PDWORD64* p_table;
	PDWORD64  new_fun;
	PDWORD64  old_fun;
};
////////////////////////
typedef HRESULT(WINAPI* m_update)(i_system*, int, int);
m_update p_update;
c_vmt* p_hook = nullptr;
////////////////////////
