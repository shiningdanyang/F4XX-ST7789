//**************************************************************************************************
//
//	ASTIdef 	共通定数ファイル
//
//	Coding		K.Wada
//
//	History		01	2008.07.31		K.Wada	NEW
//				02	2009.06.26-01	K.Wada	ビットフィールド用の型宣言を追加
//					2009.06.26-02	K.Wada	データの一部を参照できる共用体型宣言を削除
//				03	2010.12.08		K.Wada	共用体型宣言を削除
//				04	2019.10.24		S.Ando	U8型, S8型追加
//
//**************************************************************************************************
#ifndef  ASTIDEF
#define ASTIDEF

//------------------------------------------------------------------------------
//	別名宣言
//------------------------------------------------------------------------------
typedef	unsigned char			U1 ;
typedef unsigned short			U2 ;
typedef unsigned long			U4 ;
typedef unsigned long long		U8 ;

typedef	signed char				S1 ;
typedef signed short			S2 ;
typedef signed long				S4 ;
typedef signed long long		S8 ;

typedef volatile unsigned char 	VU1 ;
typedef volatile unsigned short VU2 ;
typedef volatile unsigned long	VU4 ;

typedef volatile signed char	VS1 ;
typedef volatile signed short	VS2 ;
typedef volatile signed long	VS4 ;

typedef unsigned int			UINT ;		// ビットフィールドのみ使用可能 (2009.06.26-01 追加)
typedef signed int				SINT ;		// ビットフィールドのみ使用可能 (2009.06.26-01 追加)

//typedef double		D8 ;								// double型宣言
//typedef float			F4 ;								// float型宣言

//------------------------------------------------------------------------------
//	基本定数宣言
//------------------------------------------------------------------------------
#define		U1TRUE			((U1)1)
#define		U1FALSE			((U1)0)
#define		U1ON			((U1)1)
#define		U1OFF			((U1)0)
#define		U1HI			((U1)1)
#define		U1LO			((U1)0)
#define		U1UP			((U1)1)
#define		U1DOWN			((U1)0)
#define		U1OK			((U1)1)
#define		U1NG			((U1)0)

#define		BIT0			((U1)0x01)
#define		BIT1			((U1)0x02)
#define		BIT2			((U1)0x04)
#define		BIT3			((U1)0x08)
#define		BIT4			((U1)0x10)
#define		BIT5			((U1)0x20)
#define		BIT6			((U1)0x40)
#define		BIT7			((U1)0x80)
#define		BIT_OFF			((U1)0x00)
#define		BIT_ON			((U1)0x01)

#define		U1MAX			((U1)0xff)
#define		U2MAX			((U2)0xffffUL)
#define		U4MAX			((U4)0xffffffffUL)
#define		U8MAX			((U8)0xffffffffffffffffUL)

#define		U1MIN			((U1)0x00)
#define		U2MIN			((U2)0x0000)
#define		U4MIN			((U4)0x00000000)
#define		U8MIN			((U8)0x0000000000000000)

#define		S1MAX			((S1)0x7f)
#define		S2MAX			((S2)0x7fffL)
#define		S4MAX			((S4)0x7fffffffL)
#define		S8MAX			((S8)0x7fffffffffffffffL)

#define		S1MIN			((S1)0x80)
#define		S2MIN			((S2)0x8000L)
#define		S4MIN			((S4)0x80000000L)
#define		S8MIN			((S8)0x8000000000000000L)

#define		S1ZERO			((S1)0x00)
#define		S2ZERO			((S2)0x0000L)
#define		S4ZERO			((S4)0x00000000L)
#define		S8ZERO			((S8)0x0000000000000000L)

#define 	U1_HI_NBL	 	((U1)0xf0)
#define 	U1_LO_NBL	 	((U1)0x0f)

// 共用体の型宣言(フラグ) (2010.12.08)
// 共用体の型宣言 削除 (2009.06.26-02)

#endif
/*====================================== End of File =============================================*/
