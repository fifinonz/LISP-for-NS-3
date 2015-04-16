/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*/*
 * Copyright (c) 2005 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */

/*
# Module to intergrate the  Locator/Identifier Separation Protocol(LISP)
# into NS-3 Simulator

#Modifies Existing IPV4 Header to implement a homogenous 
#LISP IPV4 - IPV4


Author: Muthoni Nguthi

 */

#include "ns3/assert.h"
#include "ns3/abort.h"
#include "ns3/log.h"
#include "ns3/uinteger.h"
#include "ns3/header.h"
#include "lisp-header.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("lispheader");

NS_OBJECT_ENSURE_REGISTERED (lispheader);

LispHeader::LispHeader ()
  : m_calcChecksum (false),
    m_payloadSize (0),
    m_identification (0),
    m_tos (0),
    m_ttl (0),
    m_protocol (0),
    m_flags (0),
    m_fragmentOffset (0),
    m_checksum (0),
    m_goodChecksum (true),
    m_headerSize(14*4)


void
LispHeader::EnableChecksum (void)
{
  NS_LOG_FUNCTION (this);
  m_calcChecksum = true;
}

void
LispHeader::SetPayloadSize (uint16_t size)
{
  NS_LOG_FUNCTION (this << size);
  m_payloadSize = size;
}
uint16_t
LispHeader::GetPayloadSize (void) const
{
  NS_LOG_FUNCTION (this);
  return m_payloadSize;
}

uint16_t
LispHeader::GetIdentification (void) const
{
  NS_LOG_FUNCTION (this);
  return m_identification;
}
void
LispHeader::SetIdentification (uint16_t identification)
{
  NS_LOG_FUNCTION (this << identification);
  m_identification = identification;
}

void 
LispHeader::SetTos (uint8_t tos)
{
  NS_LOG_FUNCTION (this << static_cast<uint32_t> (tos));
  m_tos = tos;
}

void
LispHeader::SetDscp (DscpType dscp)
{
  NS_LOG_FUNCTION (this << dscp);
  m_tos &= 0x3; // Clear out the DSCP part, retain 2 bits of ECN
  m_tos |= dscp;
}

void
LispHeader::SetEcn (EcnType ecn)
{
  NS_LOG_FUNCTION (this << ecn);
  m_tos &= 0xFC; // Clear out the ECN part, retain 6 bits of DSCP
  m_tos |= ecn;
}

LispHeader::DscpType 
LispHeader::GetDscp (void) const
{
  NS_LOG_FUNCTION (this);
  // Extract only first 6 bits of TOS byte, i.e 0xFC
  return DscpType (m_tos & 0xFC);
}

std::string 
LispHeader::DscpTypeToString (DscpType dscp) const
{
  NS_LOG_FUNCTION (this << dscp);
  switch (dscp)
    {
      case DscpDefault:
        return "Default";
      case DSCP_CS1:
        return "CS1";
      case DSCP_AF11:
        return "AF11";
      case DSCP_AF12:
        return "AF12";
      case DSCP_AF13:
        return "AF13";
      case DSCP_CS2:
        return "CS2";
      case DSCP_AF21:
        return "AF21";
      case DSCP_AF22:
        return "AF22";
      case DSCP_AF23:
        return "AF23";
      case DSCP_CS3:
        return "CS3";
      case DSCP_AF31:
        return "AF31";
      case DSCP_AF32:
        return "AF32";
      case DSCP_AF33:
        return "AF33";
      case DSCP_CS4:
        return "CS4";
      case DSCP_AF41:
        return "AF41";
      case DSCP_AF42:
        return "AF42";
      case DSCP_AF43:
        return "AF43";
      case DSCP_CS5:
        return "CS5";
      case DSCP_EF:
        return "EF";
      case DSCP_CS6:
        return "CS6";
      case DSCP_CS7:
        return "CS7";
      default:
        return "Unrecognized DSCP";
    };
}


LispHeader::EcnType 
LispHeader::GetEcn (void) const
{
  NS_LOG_FUNCTION (this);
  // Extract only last 2 bits of TOS byte, i.e 0x3
  return EcnType (m_tos & 0x3);
}

std::string 
LispHeader::EcnTypeToString (EcnType ecn) const
{
  NS_LOG_FUNCTION (this << ecn);
  switch (ecn)
    {
      case ECN_NotECT:
        return "Not-ECT";
      case ECN_ECT1:
        return "ECT (1)";
      case ECN_ECT0:
        return "ECT (0)";
      case ECN_CE:
        return "CE";      
      default:
        return "Unknown ECN";
    };
}

uint8_t 
LispHeader::GetTos (void) const
{
  NS_LOG_FUNCTION (this);
  return m_tos;
}
void 
LispHeader::SetMoreFragments (void)
{
  NS_LOG_FUNCTION (this);
  m_flags |= MORE_FRAGMENTS;
}
void
LispHeader::SetLastFragment (void)
{
  NS_LOG_FUNCTION (this);
  m_flags &= ~MORE_FRAGMENTS;
}
bool 
LispHeader::IsLastFragment (void) const
{
  NS_LOG_FUNCTION (this);
  return !(m_flags & MORE_FRAGMENTS);
}

void 
LispHeader::SetDontFragment (void)
{
  NS_LOG_FUNCTION (this);
  m_flags |= DONT_FRAGMENT;
}
void 
LispHeader::SetMayFragment (void)
{
  NS_LOG_FUNCTION (this);
  m_flags &= ~DONT_FRAGMENT;
}
bool 
LispHeader::IsDontFragment (void) const
{
  NS_LOG_FUNCTION (this);
  return (m_flags & DONT_FRAGMENT);
}

void 
LispHeader::SetFragmentOffset (uint16_t offsetBytes)
{
  NS_LOG_FUNCTION (this << offsetBytes);
  // check if the user is trying to set an invalid offset
  NS_ABORT_MSG_IF ((offsetBytes & 0x7), "offsetBytes must be multiple of 8 bytes");
  m_fragmentOffset = offsetBytes;
}
uint16_t 
LispHeader::GetFragmentOffset (void) const
{
  NS_LOG_FUNCTION (this);
  // -fstrict-overflow sensitive, see bug 1868
  if ( m_fragmentOffset + m_payloadSize > 65535 - 14*4 )
    {
      NS_LOG_WARN("Fragment will exceed the maximum packet size once reassembled");
    }

  return m_fragmentOffset;
}

void 
LispHeader::SetTtl (uint8_t ttl)
{
  NS_LOG_FUNCTION (this << static_cast<uint32_t> (ttl));
  m_ttl = ttl;
}
uint8_t 
LispHeader::GetTtl (void) const
{
  NS_LOG_FUNCTION (this);
  return m_ttl;
}

uint8_t 
LispHeader::GetProtocol (void) const
{
  NS_LOG_FUNCTION (this);
  return m_protocol;
}
void 
LispHeader::SetProtocol (uint8_t protocol)
{
  NS_LOG_FUNCTION (this << static_cast<uint32_t> (protocol));
  m_protocol = protocol;
}

void
LispHeader::SetLispOuterHeader ( uint32_t  OuterHeader )
{
	m_OuterHeader  =  OuterHeader ; 
} 

uint32_t 
LispHeader::GetLispOuterHeader ( void )  const 
{ 
	return  m_OuterHeader ; 
} 

void 
LispHeader::SetNflag ( bool  nflag ) 
{ 
 	m_OuterHeader  &=  0x7FFFFFFF ; 
	 if  ( nflag ) 
	{ 
		m_OuterHeader  |=  0x80000000 ;

	} 
} 

bool 
LispHeader::GetNflag ( void )  const 
{ 
	if  ( m_OuterHeader  &  0x80000000 ) 
		return true ;

	else 
		return false ;
} 
void 
LispHeader::SetLflag ( bool  lflag ) 
{ 
	m_OuterHeader  &=  0xBFFFFFFF ; 
	if  ( lflag ) 
	{ 
		m_OuterHeader  |=  0x40000000 ;
	} 
} 
bool 
LispHeader::GetLflag ( void )  const 
{ 
	if  ( m_OuterHeader  &  0x40000000 ) 
		return true ;

	else 
		return false ;

} 


void 
LispHeader::SetEflag ( bool  eflag ) 
{ 
	m_OuterHeader  &=  0xDFFFFFFF ; 
	if  ( eflag ) 
	{ 
		m_OuterHeader  |=  0x20000000 ;
	} 

} 

bool 
LispHeader::GetEflag ( void )  const 
{ 

	if  ( m_OuterHeader  &  0x20000000 ) 
		return true ;

	else
		return false ;
} 

void 
LispHeader::SetVflag ( bool  vflag ) 
{ 
	m_OuterHeader  &=  0xEFFFFFFF ; 
	if  ( vflag ) 
	{ 
	m_OuterHeader  |=  0x10000000 ;
	} 
} 


bool 
LispHeader::GetVflag ( void )  const 
{ 
	if  ( m_OuterHeader  &  0x10000000 ) 
		return true ;

	else
		return false ;

} 

void 
LispHeader::SetIflag ( bool  iflag ) 
{ 
	m_OuterHeader  &=  0xF7FFFFFF ; 
	if  ( iflag ) 
	{ 
	m_OuterHeader  |=  0x08000000 ;
	} 
} 

bool 
LispHeader::GetIflag ( void )  const 
{ 

	if  ( m_OuterHeader  &  0x08000000 ) 

		return true ;

	else
		return false ;
} 

void 
LispHeader::SetFlagfield ( uint32_t  flagfield ) 
{ 
	flagfield  =  0x00000000 ; 
	m_OuterHeader  &=  0xF8FFFFFF ; 
	m_OuterHeader  |=  flagfield ; 
} 

uint32_t 
LispHeader::GetFlagfield ( void )  const 
{ 
	return  ( m_OuterHeader  &  0x07000000 ); 
} 

void 
LispHeader::SetNoncefield ( uint32_t  noncefield ) 
{ 
	NS_ASSERT (!( noncefield  &  0xFF000000 )); 
	m_OuterHeader  &=  0xFF000000 ; 
	m_OuterHeader  |=  noncefield ; 
} 

uint32_t 
LispHeader::GetNoncefield ( void )  const 
{ 
	return  ( m_OuterHeader  & 0x00FFFFFF ); 
} 


void 
LispHeader::SetLispInnerHeader ( uint32_t  InnerHeader ) 
{ 
	m_InnerHeader  =  InnerHeader ; 
} 

uint32_t 
LispHeader::GetLispInnerHeader( void )  const 
{ 
	return  m_InnerHeader ; 
} 

void 
LispHeader::SetInstanceID ( uint32_t  instanceid ) 
{ 
	instanceid  =  instanceid  <<  8; 
	m_InnerHeader  &=  0x000000FF ; 
	m_InnerHeader  |=  instanceid ; 
} 

uint32_t 
LispHeader::GetInstanceID ( void )  const 
{ 
	uint32_t  retval  =  m_InnerHeader  & 0xFFFFFF00 ; 
	retval  =  retval >>8  ; 
	return  retval ; 

} 

void  LispHeader::SetLsbs ( uint32_t  lsbs ) 
{ 
	NS_ASSERT (!( lsbs  &  0xFFFFFF00 )); 
	m_InnerHeader  &=  0xFFFFFF00 ; 
	m_InnerHeader  |=  lsbs ; 
} 


uint32_t 
LispHeader::GetLsbs ( void )  const 
{ 
	return  ( m_InnerHeader  &  0x000000FF ); 
} 


void 
LispHeader::SetESource (Ipv4Address sourceEID)
{
  NS_LOG_FUNCTION (this << sourceEID);
  m_source = sourceEID;
}
Ipv4Address
LispHeader::GetESource (void) const
{
  NS_LOG_FUNCTION (this);
  return m_source;
}

void 
LispHeader::SetEDestination (Ipv4Address destinationEID)
{
  NS_LOG_FUNCTION (this << dst);
  m_destination = dst;
}
Ipv4Address
LispHeader::GetDestination (void) const
{
  NS_LOG_FUNCTION (this);
  return m_destination;
}

void 
LispHeader::SetRSource (Ipv4Address sourceRLOC)
{
  NS_LOG_FUNCTION (this << sourceRLOC);
  m_rsource = sourceRLOC;
}
Ipv4Address
LispHeader::GetRSource (void) const
{
  NS_LOG_FUNCTION (this);
  return m_rsource;
}

void 
LispHeader::SetRDestination (Ipv4Address destinationRLOC)
{
  NS_LOG_FUNCTION (this << destinationRLOC);
  m_rdestination = destinationRLOC;
}
Ipv4Address
LispHeader::GetDestination (void) const
{
  NS_LOG_FUNCTION (this);
  return m_rdestination;
}


bool
LispHeader::IsChecksumOk (void) const
{
  NS_LOG_FUNCTION (this);
  return m_goodChecksum;
}

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
	NS_LOG_FUNCTION (this);
	return  GetTypeId  (); 
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
	<<  " Noncefield  is  set  to:  "  <<  GetNoncefield ()  <<  "  \n" 
	<<  " InstanceID  is  set  to:  "  <<  GetInstanceID ()  <<  "  \n" 
	<<  " LsBits  is  set  to:  "  <<  GetLsbs ()  <<  "  \n" 
	<<  " Lisp  Header  Row  1  is  set  to:  "  <<  m_OuterHeader  		<<  "  \n"
	<<  " Instance  ID/ Locator - Status - Bits :  "  << m_InnerHeader  <<  "  \n"; 

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
	i.WriteU32 ( m_OuterHeader ); 
	i.WriteU32 ( m_InnerHeader ); 

} 

uint32_t 
LispHeader::Deserialize  ( Buffer :: Iterator  start ) 
{ 
	Buffer::Iterator  i  =  start ; 
	m_OuterHeader  =  i.ReadU32  ();  //  Read  first  32 - bit  row 
	m_InnerHeader  =  i.ReadU32  ();  //  Read  second  32 - bit  row 

return  GetSerializedSize  (); 

} 
}
