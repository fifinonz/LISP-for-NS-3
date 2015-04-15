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

#Modiefies Existing IPV4 Header to implement a homogenous 
#LISP IPV4 - IPV4


Author: Muthoni Nguthi

*/
#ifndef LISP_HEADER_H
#define LISP_HEADER_H

#include "ns3/header.h"
#include "ns3/ipv4-address.h"

 namespace ns3 {
/**
 * \brief Packet header for LISP  IPv4
 */
class LispHeader : public Header

{
public :
 /**
   * \brief Construct a null IPv4 header
   */
   LispHeader () ; 
/**
   * \brief Enable checksum calculation for this header.
   */
  void EnableChecksum (void);
  /**
   * \param size the size of the payload in bytes
   */
  void SetPayloadSize (uint16_t size);
  /**
   * \param identification the Identification field of IPv4 packets.
   *
   * By default, set to zero.
   */
  void SetIdentification (uint16_t identification);
  /**
   * \param tos the 8 bits of Ipv4 TOS.
   */
  void SetTos (uint8_t tos);
  /**
   * \enum DscpType
   * \brief DiffServ Code Points 
   * Code Points defined in
   * Assured Forwarding (AF) \RFC{2597}
   * Expedited Forwarding (EF) \RFC{2598}
   * Default and Class Selector (CS) \RFC{2474}
   */
  enum DscpType
    {
      DscpDefault = 0x00,

      // Prefixed with "DSCP" to avoid name clash (bug 1723)
      DSCP_CS1 = 0x20,
      DSCP_AF11 = 0x28,
      DSCP_AF12 = 0x30,
      DSCP_AF13 = 0x38,

      DSCP_CS2 = 0x40,
      DSCP_AF21 = 0x48,
      DSCP_AF22 = 0x50,
      DSCP_AF23 = 0x58,

      DSCP_CS3 = 0x60,
      DSCP_AF31 = 0x68,
      DSCP_AF32 = 0x70,
      DSCP_AF33 = 0x78,

      DSCP_CS4 = 0x80,
      DSCP_AF41 = 0x88,
      DSCP_AF42 = 0x90,
      DSCP_AF43 = 0x98,

      DSCP_CS5 = 0xA0,
      DSCP_EF = 0xB8,
      
      DSCP_CS6 = 0xC0,
      DSCP_CS7 = 0xE0
      
    };
  /**
   * \brief Set DSCP Field
   * \param dscp DSCP value
   */
  void SetDscp (DscpType dscp);

  /**
   * \enum EcnType
   * \brief ECN Type defined in \RFC{3168}
   */
  enum EcnType
    {
      // Prefixed with "ECN" to avoid name clash (bug 1723)
      ECN_NotECT = 0x00,
      ECN_ECT1 = 0x01,
      ECN_ECT0 = 0x02,
      ECN_CE = 0x03
    }; 
  /**
   * \brief Set ECN Field
   * \param ecn ECN Type
   */
  void SetEcn (EcnType ecn);
  /**
   * This packet is not the last packet of a fragmented ipv4 packet.
   */
  void SetMoreFragments (void);
  /**
   * This packet is the last packet of a fragmented ipv4 packet.
   */
  void SetLastFragment (void);
  /**
   * Don't fragment this packet: if you need to anyway, drop it.
   */
  void SetDontFragment (void);
  /**
   * If you need to fragment this packet, you can do it.
   */
  void SetMayFragment (void);
  /**
   * The offset is measured in bytes for the packet start.
   * Mind that IPv4 "fragment offset" field is 13 bits long and is measured in 8-bytes words.
   * Hence, the function does enforce that the offset is a multiple of 8.
   * \param offsetBytes the ipv4 fragment offset measured in bytes from the start.
   */
  void SetFragmentOffset (uint16_t offsetBytes);
  /**
   * \param ttl the ipv4 TTL
   */
  void SetTtl (uint8_t ttl);
  /**
   * \param num the ipv4 protocol field
   */
  void SetProtocol (uint8_t num);
  /**
   * \param source the source of this packet
   */
  void SetSource (Ipv4Address source);
  /**
   * \param destination the destination of this packet.
   */
  void SetDestination (Ipv4Address destination);
  /**
   * \returns the size of the payload in bytes
   */
  /**************************************************************************
  Functions to Set the values of IPV4  LISP Protocol Specific Header fields
***************************************************************************/
/**
   * \param header row value
   */
 void SetLispHeaderRow1 ( uint32_t lispheaderrow1 ) ;
/**
   * \param nonce-present bit
   */
 void SetNflag ( bool nflag ) ; 
/**
   * \param Locator-Status-Bit
   */
 void SetLflag ( bool lflag ) ;
/**
   * \param echo-nonce-request bit
   */
 void SetEflag ( bool eflag ) ;
/**
   * \param Map-Version present bit
   */ void SetVflag ( bool vflag ) ;

/**
   * \param Instance ID bit
   */
 void SetIflag ( bool iflag ) ;
/**
   * \param 'flags' reseeved field
   */
 void SetFlagfield ( uint32_t flagfield ) ;
/**
   * \param ISP Nonce
   */ void SetNoncefield ( uint32_t noncefield ) ;

/**
   * \param source the source of this packet
   */ void SetLispHeaderRow2 ( uint32_t lispheaderrow2 ) ;

/**
   * \param Instance ID
   */ void SetInstanceID ( uint32_t instanceid ) ;
/**
   * \param ISP Locator-Status-Bits
   */
 void SetLsbs ( uint32_t lsbs ) ;

 
/* Functions to serialze and deserialze packet headers*/

 static TypeId GetTypeId ( void ) ;
 virtual TypeId GetInstanceTypeId ( void ) const ;
 virtual void Print ( std::ostream &os ) const ;
 virtual uint32_t GetSerializedSize ( void ) const ;
 virtual void Serialize ( Buffer::Iterator start ) const ;
 virtual uint32_t Deserialize ( Buffer::Iterator start ) ;
uint16_t GetPayloadSize (void) const;
  /**
   * \returns the identification field of this packet.
   */
  uint16_t GetIdentification (void) const;
  /**
   * \returns the TOS field of this packet.
   */
  uint8_t GetTos (void) const;
  /**
   * \returns the DSCP field of this packet.
   */
  DscpType GetDscp (void) const;
  /**
   * \param dscp the dscp
   * \returns std::string of DSCPType
   */
  std::string DscpTypeToString (DscpType dscp) const;
  /**
   * \returns the ECN field of this packet.
   */
  EcnType GetEcn (void) const;
  /**
   * \param ecn the ECNType
   * \returns std::string of ECNType
   */
  std::string EcnTypeToString (EcnType ecn) const;
  /**
   * \returns true if this is the last fragment of a packet, false otherwise.
   */
  bool IsLastFragment (void) const;
  /**
   * \returns true if this is this packet can be fragmented.
   */
  bool IsDontFragment (void) const;
  /**
   * \returns the offset of this fragment measured in bytes from the start.
   */
  uint16_t GetFragmentOffset (void) const;
  /**
   * \returns the TTL field of this packet
   */
  uint8_t GetTtl (void) const;
  /**
   * \returns the protocol field of this packet
   */
  uint8_t GetProtocol (void) const;
  /**
   * \returns the source address of this packet
   */
  Ipv4Address GetSource (void) const;
  /**
   * \returns the destination address of this packet
   */
  Ipv4Address GetDestination (void) const;

  /**************************************************************************
  Functions to Get the values of IPV4  LISP Protocol Specific Header fields
***************************************************************************/
  /**
   * \returns LispHeader Row
   */
 uint32_t GetLispHeaderRow1 ( void ) const ;
  /**
   * \returns Nflag bit
   */
 bool GetNflag ( void ) const ;
  /**
   * \returns Lflag but
   */ 
 bool GetLflag ( void ) const ;
  /**
   * \returns Eflag bit
   */
 bool GetEflag ( void ) const ;
  /**
   * \returns Vflag bit
   */
 bool GetVflag ( void ) const ;
  /**
   * \returns the I flag bit
    */
 bool GetIflag ( void ) const ;
  /**
   * \returns 'flags' values MUST be 0
   */ 
 uint32_t GetFlagfield ( void ) const ;
  /**
   * \returns ISP nonce value
   */ 
 uint32_t GetNoncefield ( void ) const ;
  /**
   * \returns the Value of Header Row 2
   */
 uint32_t GetLispHeaderRow2 ( void ) const ;
  /**
   * \returns the Instance ID
   */
 uint32_t GetInstanceID ( void ) const ;
  /**
   * \returns the Locator-Status-bits
   */ 
 uint32_t GetLsbs ( void ) const ;


  /**
   * \returns true if the ipv4 checksum is correct, false otherwise.
   *
   * If Ipv4Header::EnableChecksums has not been called prior to
   * deserializing this header, this method will always return true.
   */
  bool IsChecksumOk (void) const;

  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  virtual void Print (std::ostream &os) const;
  virtual uint32_t GetSerializedSize (void) const;
  virtual void Serialize (Buffer::Iterator start) const;
  virtual uint32_t Deserialize (Buffer::Iterator start);
private:

  /// flags related to IP fragmentation
  enum FlagsE {
    DONT_FRAGMENT = (1<<0),
    MORE_FRAGMENTS = (1<<1)
  };

  bool m_calcChecksum; //!< true if the checksum must be calculated

  uint16_t m_payloadSize; //!< payload size
  uint16_t m_identification; //!< identification
  uint32_t m_tos : 8; //!< TOS, also used as DSCP + ECN value
  uint32_t m_ttl : 8; //!< TTL
  uint32_t m_protocol : 8;  //!< Protocol
  uint32_t m_flags : 3; //!< flags
  uint16_t m_fragmentOffset;  //!< Fragment offset
  Ipv4Address m_source; //!< source address
  Ipv4Address m_destination; //!< destination address
  uint16_t m_checksum; //!< checksum
  bool m_goodChecksum; //!< true if checksum is correct
  uint16_t m_headerSize; //!< IP header size


 

private :
 uint32_t m_lispheaderrow1 ; // First 32 - bit Field of LISP header
 uint32_t m_lispheaderrow2 ; // Second 32 - bit Field of LISP header
 };
 } // namespace ns3
 # endif 
/*LISP-HEADER_H*/
