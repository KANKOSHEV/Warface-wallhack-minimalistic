#pragma once

template <int X> struct EnsureCompileTime
{
	enum : int
	{
		Value = X
	};
};

#define compile_seed (	(__TIME__[7] - '0') * 1  + (__TIME__[6] - '0') * 10		+	\
						(__TIME__[4] - '0') * 60   + (__TIME__[3] - '0') * 600	+	\
						(__TIME__[1] - '0') * 3600 + (__TIME__[0] - '0') * 36000	)

constexpr int LinearCongruentGenerator(int Rounds)
{
	return 1013904223 + 1664525 * ((Rounds > 0) ? LinearCongruentGenerator(Rounds - 1) : compile_seed & 0xFFFFFFFF);
}
#define Random() EnsureCompileTime<LinearCongruentGenerator(10)>::Value 
#define RandomNumber(Min, Max) (Min + (Random() % (Max - Min + 1)))

template <int... Pack> struct IndexList {};
template <typename IndexList, int Right> struct Append;
template <int... Left, int Right> struct Append<IndexList<Left...>, Right>
{
	typedef IndexList<Left..., Right> Result;
};

template <int N> struct ConstructIndexList
{
	typedef typename Append<typename ConstructIndexList<N - 1>::Result, N - 1>::Result Result;
};

template <> struct ConstructIndexList<0>
{
	typedef IndexList<> Result;
};

#pragma warning(disable : 4307)
#pragma warning(disable : 4309)

template <typename Char, typename IndexList> class ecingT;
template <typename Char, int... Index> class ecingT<Char, IndexList<Index...> >
{
private:
	Char Value[sizeof...(Index) + 1];
	static const Char XORKEY = static_cast<Char>(RandomNumber(0, 0xFFFF));
	template <typename Char>
	constexpr Char EncryptCharacterT(const Char Character, int Index)
	{
		return Character ^ (XORKEY + Index);
	}
public:
	__forceinline constexpr ecingT(const Char* const String) : Value{ EncryptCharacterT(String[Index], Index)... } {}

	const Char *decrypt()
	{
		for (int t = 0; t < sizeof...(Index); t++)
		{
			Value[t] = Value[t] ^ (XORKEY + t);
		}
		Value[sizeof...(Index)] = static_cast<Char>(0);
		return Value;
	}
	const Char *get()
	{
		return Value;
	}
};

#pragma warning(disable : 4307)
const char XORKEYZ = static_cast<char>((char)RandomNumber(0, 0xFF));
#pragma warning(default : 4307)
__forceinline constexpr char EncryptCharacterS(const char Character, int Index)
{
	return Character ^ (XORKEYZ + Index);
}

template <typename IndexList> class CXorString;
template <int... Index> class CXorString<IndexList<Index...> >
{
private:
	char Value[sizeof...(Index) + 1];
public:
	__forceinline constexpr CXorString(const char* const String) : Value{ EncryptCharacterS(String[Index], Index)... } {}
	__forceinline char* decrypt()
	{
		for (int t = 0; t < sizeof...(Index); t++)
		{
			Value[t] = Value[t] ^ (XORKEYZ + t);
		}
		Value[sizeof...(Index)] = '\0';
		return Value;
	}
	__forceinline char* get()
	{
		return Value;
	}
};

#pragma warning(default : 4307)
#pragma warning(default : 4309)

#define xor_a( String ) ( CXorString<ConstructIndexList<sizeof( String ) - 1>::Result>( String ).decrypt() )
#define xor_w( String ) ( ecingT<wchar_t, ConstructIndexList<(sizeof( String ) - 1) / 2>::Result>( String ).decrypt() )
