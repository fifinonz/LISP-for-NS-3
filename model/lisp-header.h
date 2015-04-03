/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
# Module to intergrate the  Locator/Identifier Separation Protocol(LISP)
# into NS-3 Simulator

*/
#ifndef LISP_HEADER_H
#define LISP_HEADER_H
#include "ns3/header.h"
 namespace ns3 {
 
class LispHeader : public Header

{
public :
   LispHeader () ; // constructor
 ~ LispHeader () ; // deconstructor
 
/* Functions to set the values of LISP header fields */

 void SetLispHeaderRow1 ( uint32_t lispheaderrow1 ) ;
 void SetNflag ( bool nflag ) ; 
 void SetLflag ( bool lflag ) ;
 void SetEflag ( bool eflag ) ;
 void SetVflag ( bool vflag ) ;
 void SetIflag ( bool iflag ) ;
 void SetFlagfield ( uint32_t flagfield ) ;
 void SetNouncefield ( uint32_t nouncefield ) ;
 void SetLispHeaderRow2 ( uint32_t lispheaderrow2 ) ;
 void SetInstanceID ( uint32_t instanceid ) ;
 void SetLsbs ( uint32_t lsbs ) ;

/* Functions to  Get the value of a LISP header field*/

 uint32_t GetLispHeaderRow1 ( void ) const ;
 bool GetNflag ( void ) const ;
 bool GetLflag ( void ) const ;
 bool GetEflag ( void ) const ;
 bool GetVflag ( void ) const ;
 bool GetIflag ( void ) const ;
 uint32_t GetFlagfield ( void ) const ;
 uint32_t GetNouncefield ( void ) const ;
 uint32_t GetLispHeaderRow2 ( void ) const ;
 uint32_t GetInstanceID ( void ) const ;
 uint32_t GetLsbs ( void ) const ;

/* Functions to serialze and deserialze packet headers*/

 static TypeId GetTypeId ( void ) ;
 virtual TypeId GetInstanceTypeId ( void ) const ;
 virtual void Print ( std::ostream &os ) const ;
 virtual uint32_t GetSerializedSize ( void ) const ;
 virtual void Serialize ( Buffer::Iterator start ) const ;
 virtual uint32_t Deserialize ( Buffer::Iterator start ) ;

private :
 uint32_t m_lispheaderrow1 ; // First 32 - bit Field of LISP header
 uint32_t m_lispheaderrow2 ; // Second 32 - bit Field of LISP header
 };
 } // namespace ns3
 # endif 
/*LISP-HEADER_H*/
