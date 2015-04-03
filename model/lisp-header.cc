#include "lisp-header.h"
#include "ns3/log.h"
#include "ns3/uinteger.h"

namespace ns3 {



TypeId 
LispHeader::GetTypeId  ( void ) 
{ 
	static  TypeId  tid  =  TypeId  ("ns3 :: LispHeader ") 
	.SetParent<Header>  () 
	.AddConstructor<LispHeader>  (); 
	
	return  tid; 

} 

TypeId 
LispHeader::GetInstanceTypeId  ( void )  const 
{ 
	return  GetTypeId  (); 
}


//Set lisp header row
void
LispHeader::SetLispHeaderRow1 ( uint32_t  lispheaderrow1 )
{
	m_lispheaderrow1  =  lispheaderrow1 ; 
} //end

//Set nonce flage
void 
LispHeader::SetNflag ( bool  nflag ) 
{ 
 	m_lispheaderrow1  &=  0x7FFFFFFF ; 
	 if  ( nflag ) 
	{ 
		m_lispheaderrow1  |=  0x80000000 ;

	} 
} //end


void 
LispHeader::SetLflag ( bool  lflag ) 
{ 
	m_lispheaderrow1  &=  0xBFFFFFFF ; 
	if  ( lflag ) 
	{ 
		m_lispheaderrow1  |=  0x40000000 ;
	} 
} 

void 
LispHeader::SetEflag ( bool  eflag ) 
{ 
	m_lispheaderrow1  &=  0xDFFFFFFF ; 
	if  ( eflag ) 
	{ 
		m_lispheaderrow1  |=  0x20000000 ;
	} 

} 

void 
LispHeader::SetVflag ( bool  vflag ) 
{ 
	m_lispheaderrow1  &=  0xEFFFFFFF ; 
	if  ( vflag ) 
	{ 
	m_lispheaderrow1  |=  0x10000000 ;
	} 
} 

void 
LispHeader::SetIflag ( bool  iflag ) 
{ 
	m_lispheaderrow1  &=  0xF7FFFFFF ; 
	if  ( iflag ) 
	{ 
	m_lispheaderrow1  |=  0x08000000 ;
	} 
} 

void 
LispHeader::SetFlagfield ( uint32_t  flagfield ) 
{ 
	flagfield  =  0x00000000 ; 
	m_lispheaderrow1  &=  0xF8FFFFFF ; 
	m_lispheaderrow1  |=  flagfield ; 
} 

void 
LispHeader::SetNouncefield ( uint32_t  nouncefield ) 
{ 
	NS_ASSERT (!( nouncefield  &  0xFF000000 )); 
	m_lispheaderrow1  &=  0xFF000000 ; 
	m_lispheaderrow1  |=  nouncefield ; 
} 

void 
LispHeader::SetLispHeaderRow2 ( uint32_t  lispheaderrow2 ) 
{ 
	m_lispheaderrow2  =  lispheaderrow2 ; 
} 

void 
LispHeader::SetInstanceID ( uint32_t  instanceid ) 
{ 
	instanceid  =  instanceid  <<  8; 
	m_lispheaderrow2  &=  0x000000FF ; 
	m_lispheaderrow2  |=  instanceid ; 
} 

void  LispHeader::SetLsbs ( uint32_t  lsbs ) 
{ 
	NS_ASSERT (!( lsbs  &  0xFFFFFF00 )); 
	m_lispheaderrow2  &=  0xFFFFFF00 ; 
	m_lispheaderrow2  |=  lsbs ; 
} 

uint32_t 
LispHeader::GetLispHeaderRow1 ( void )  const 
{ 
	return  m_lispheaderrow1 ; 
} 

bool 
LispHeader::GetNflag ( void )  const 
{ 
	if  ( m_lispheaderrow1  &  0x80000000 ) 
		return true ;

	else 
		return false ;
} 

bool 
LispHeader::GetLflag ( void )  const 
{ 
	if  ( m_lispheaderrow1  &  0x40000000 ) 
		return true ;

	else 
		return false ;

} 

bool 
LispHeader::GetEflag ( void )  const 
{ 

	if  ( m_lispheaderrow1  &  0x20000000 ) 
		return true ;

	else
		return false ;
} 

bool 
LispHeader::GetVflag ( void )  const 
{ 
	if  ( m_lispheaderrow1  &  0x10000000 ) 
		return true ;

	else
		return false ;

} 

bool 
LispHeader::GetIflag ( void )  const 
{ 

	if  ( m_lispheaderrow1  &  0x08000000 ) 

		return true ;

	else
		return false ;
} 

uint32_t 
LispHeader::GetFlagfield ( void )  const 
{ 
	return  ( m_lispheaderrow1  &  0x07000000 ); 
} 

uint32_t 
LispHeader::GetNouncefield ( void )  const 
{ 
	return  ( m_lispheaderrow1  & 0x00FFFFFF ); 
} 

uint32_t 
LispHeader::GetLispHeaderRow2 ( void )  const 
{ 
	return  m_lispheaderrow2 ; 
} 

uint32_t 
LispHeader::GetInstanceID ( void )  const 
{ 
	uint32_t  retval  =  m_lispheaderrow2  & 0xFFFFFF00 ; 
	retval  =  retval >>8  ; 
	return  retval ; 

} 

uint32_t 
LispHeader::GetLsbs ( void )  const 
{ 
	return  ( m_lispheaderrow2  &  0x000000FF ); 
} 


void 
LispHeader::Print  (std :: ostream  &os)  const 
{ 
	os  <<  " LISP_Header  " 
	<<  " Nflag  is  set  to:  "  <<  GetNflag ()  <<  "  \n" 
	<<  " Lflag  is  set  to:  "  <<  GetLflag ()  <<  "\n" 
	<<  " Eflag  is  set  to:  "  <<  GetEflag ()  <<  "  \n" 
	<<  " Vflag  is  set  to:  "  <<  GetVflag ()  <<  "\n" 
	<<  " Iflag  is  set  to:  "  <<  GetIflag ()  <<  "  \n" 
	<<  " Flagfield  is  set  to:  "  <<  GetFlagfield ()  <<  "  \n" 
	<<  " Nouncefield  is  set  to:  "  <<  GetNouncefield ()  <<  "  \n" 
	<<  " InstanceID  is  set  to:  "  <<  GetInstanceID ()  <<  "  \n" 
	<<  " LsBits  is  set  to:  "  <<  GetLsbs ()  <<  "  \n" 
	<<  " Lisp  Header  Row  1  is  set  to:  "  <<  m_lispheaderrow1  		<<  "  \n"
	<<  " Instance  ID/ Locator - Status - Bits :  "  << m_lispheaderrow2  <<  "  \n"; 

} 

uint32_t 
LispHeader::GetSerializedSize  ( void )  const 
{ 
	uint32_t  length  =  32  +  // first  32 - bit  row  length
					  32;   // second  32 - bit  row  length

	return  length ; 

} 

void 
LispHeader::Serialize  ( Buffer :: Iterator  start )  const 
{ 
	Buffer::Iterator  i  =  start ; 

	/*  LISP_Header  */ 
	i.WriteU32 ( m_lispheaderrow1 ); 
	i.WriteU32 ( m_lispheaderrow2 ); 

} 

uint32_t 
LispHeader::Deserialize  ( Buffer :: Iterator  start ) 
{ 
	Buffer::Iterator  i  =  start ; 
	m_lispheaderrow1  =  i.ReadU32  ();  //  Read  first  32 - bit  row 
	m_lispheaderrow2  =  i.ReadU32  ();  //  Read  second  32 - bit  row 

return  GetSerializedSize  (); 

} 
}
