//=========================================================================
//	Random number generator	(Algorithm by R. M. Ziff)
//  written by H. Hinrichsen and Ph. Otterbein
//=========================================================================

/*
void InitRandom 	(int randomize=1)			// Initialization
double rnd			(void)						// [0,1)
double rnd 			(double max) 	 			// [0,max)
double rnd 			(double min, double max) 	// [min,max)
int rndint 			(int num=2)  	 			// 0,1,...num-1
int rndint 			(int min, int max)			// min,min+1,...,max
*/

//-----------------------------------------------------------------------------
#define bits 31		//defines range (0,1,...,2^bits-1) of RandomInteger and the resolution (2^-bits) of rnd(...)
//-----------------------------------------------------------------------------


#if (bits==32 || bits==64)
	#define __sign unsigned
#else
	#define __sign signed
#endif
#if (bits<=32)
	#define __INT  int			//32-bit integer
#elif(bits<=64)
	//INT: 64-bit integer
	#define __INT long int		//for 64-bit platform	
	//#define __INT long long	//for 32-bit platform ("long long" is not supported by all compilers!)
#else
	#error "A resolution higher than 64 bit is not implemented!\n"
#endif
#define INT __sign __INT
#define UINT unsigned __INT
#if(bits>53)
	#define FLOAT long double
#else
	#define FLOAT double
#endif

const int Random_A = 471;
const int Random_B = 1586;
const int Random_C = 6988;
const int Random_D = 9689;
const int Random_M = 16383;
const INT Random_Max = ((INT)1<<(bits-1)) + (((INT)1<<(bits-1))-1);
const FLOAT IRandom_Max = powl(2.0, -bits);		//powl(...) is the long double version of pow(..)
int Random_nd;
INT Random_ra[Random_M+1];

void InitRandom (int randomize=1) {
	srand((unsigned int)randomize*time(0));
	INT test;
	do {
		test=0;
		for (int i=0; i<=Random_M; ++i)
		{
			for( int j=0; j<bits; j++ )
				Random_ra[i] += (INT)(rand()&1)<<j;
			test |= Random_ra[i];
		}
	}while( test != Random_Max );
}

#define RandomInteger (++Random_nd, Random_ra[Random_nd & Random_M] = \
	Random_ra[(Random_nd-Random_A) & Random_M] ^ \
	Random_ra[(Random_nd-Random_B) & Random_M] ^ \
	Random_ra[(Random_nd-Random_C) & Random_M] ^ \
	Random_ra[(Random_nd-Random_D) & Random_M])

inline FLOAT rnd(void)	{return (FLOAT)RandomInteger*IRandom_Max;} 


//-------------------Auxiliary random number routines---------------------

inline FLOAT rnd(double max)				{return max*rnd();}
inline FLOAT rnd(double min, double max)	{return min+(max-min)*rnd();}
inline int rndint(int num=2)				{return (INT)(num*rnd()); }
inline int rndint(int min, int max)			{return min+rndint(max-min+1); }
#define rndbit()	(RandomInteger&1)		//  0,1
#define rndsign()	((RandomInteger&2)-1)	// -1,1
#if (bits==32 || bits==64)
	const FLOAT IRandom_Max2 = powl(2.0, -(bits-1));
	inline FLOAT rnd_2()	{return (FLOAT)(__INT)RandomInteger*IRandom_Max2;}	// [-1, 1)
#endif
