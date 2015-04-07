
//
// Network topology
//
//  n0
//     \ 5 Mb/s, 2ms
//      \          1.5Mb/s, 10ms
//       n2 -------------------------n3
//      /
//     / 5 Mb/s, 2ms
//   n1
//

# include <iostream>
# include "ns3/core-module.h"
# include "ns3/network-module.h"
# include "ns3/internet-module.h"
# include "ns3/lisp-header.h"
# include "ns3/csma-module.h"
#include "ns3/netanim-module.h"

 namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("NetworkApp");
static void
GenerateTraffic( Ptr < Socket > socket , uint32_t size )
{
	LispHeader header ; // initialize a lisp header

	std::cout << " at = " << Simulator :: Now () . GetSeconds () << "s , tx bytes = " << size<< std::endl ;

	
	//  set header bits
	 header.SetNflag( true ) ;
	 header.SetLflag( true ) ;
	 header.SetEflag( true ) ;
	 header.SetVflag( true ) ;
	 header.SetIflag( true ) ;
	 header.SetFlagfield(0xF8FFFFFF ) ;
	 header.SetNouncefield(0x00FFFFFF ) ;
	 header.SetInstanceID (0x00123456 ) ;
	 header.SetLsbs(0x000000FF ) ;

	// display encapsulated header
	 std::cout << " header before sending : " << std :: endl ;
	 header.Print( std::cout ) ;
	 std::cout << std::endl ;

	// Create a packet and add the header
	 Ptr<Packet> p = Create <Packet> ( size ) ;
	 p->AddHeader ( header ) ;

	//send packet via socket
	 socket->Send ( p ) ;
	 if ( size > 0)
	{
	// create simualtion
		Simulator::Schedule( Seconds (0.5) , & GenerateTraffic , socket , size - 50) ;

	}

	else
	{
		socket->Close () ;

	} // end else-if
}// end generate traffic


//Process received packet and print contents
 static void
 SocketPrinter ( Ptr <Socket> socket )
 {
 	Ptr <Packet> packet ;
 	while (( packet = socket->Recv () ) )
	{
		// print header as received
		 LispHeader header ;
		 std :: cout << " header after receiving : " << std :: endl ;
		 packet->PeekHeader ( header ) ;
		 header.Print ( std::cout ) ;
		 std::cout<<std::endl ;

//std::cout <<"at ="<<Simulator::Now().GetSeconds()<< "s , rx bytes ="<<packet->GetSize()<< std :: endl ;

	}
 }

// Print response
 static void
 PrintTraffic ( Ptr <Socket> socket )
 {

	socket->SetRecvCallback (MakeCallback (&SocketPrinter ) ) ;
 }

// Function to Create Network Simulation


 int main ( int argc , char * argv [])
 {
	
	
	//Creating 3 nodes
	NodeContainer c;
	c.Create (3);


	// connect nodes using a csma channel
	 CsmaHelper csma ;
	 csma.SetChannelAttribute( " DataRate " , DataRateValue ( DataRate (5000000) ) ) ;
	 csma.SetChannelAttribute( " Delay " , TimeValue ( MilliSeconds (2) ) ) ;

	// Preparing csma channel between nodes
	NodeContainer c0 = NodeContainer (c.Get (0), c.Get (1));
	NodeContainer c1 = NodeContainer (c.Get (1), c.Get (2));
	NodeContainer c2 = NodeContainer (c.Get (2), c.Get (3));
	


	// create NetDevice containers

	 NetDeviceContainer n0 = csma.Install ( c.Get (0) ) ;
	 NetDeviceContainer n1 = csma.Install ( c . Get (1) ) ;
	 NetDeviceContainer n1 = csma.Install ( c . Get (2) ) ;
	

	// install ip stack on nodes
	 InternetStackHelper internet ;
	 internet.Install ( c ) ;

	// set IP addresses	
	Ipv4AddressHelper ipv4addr;

	ipv4.SetBase ("10.0.0.0", "255.255.255.0");
	Ipv4InterfaceContainer eidToxtrL;
	eidToxtrL = ipv4.Assign (n0);
	ipv4.SetBase ("10.0.1.0", "255.255.255.252");
	Ipv4InterfaceContainer xtrToxtr;
	xtrToxtr = ipv4.Assign (n1);
	ipv4.SetBase ("10.0.2.0", "255.255.255.0");
	Ipv4InterfaceContainer xtrToeidR;
	ipv4.Assign (n2);


	TypeId tid=TypeId::LookupByName ( " ns3::UdpSocketFactory" ) ;

	  // Create a packet sink to receive these packets
	 Ptr<Socket> sink = Socket::CreateSocket ( c.Get (0) , tid ) ;
	 InetSocketAddress local = InetSocketAddress ( eidToxtrL0 . GetAddress (0 ,0), 80); // set sink address to local tunnel router IP
	 sink->Bind ( local ) ; // bind socket to address
	
	// create source
	 Ptr<Socket> source = Socket::CreateSocket ( c.Get(1) , tid ) ;

// GetAddress( c.Get (1)->GetObject <Ipv4> ()->GetInterfaceForDevice(ndev1) ,1) ;

	 InetSocketAddress remote=InetSocketAddress (eidToxtrL1.GetAddress (0 ,0) , 80); //set source address to tunnel router IP
	 source->Connect ( remote ) ; // connect to remote socket

	
	GenerateTraffic ( source , 500) ; // begin traffic simulation
	PrintTraffic ( sink ) ; // print traffic to sink
	
	//Creating UdpEcho profile to issue ping
	UdpEchoServerHelper echoServer (900);
	ApplicationContainer serverApps = echoServer.Install (c0.Get (1));
	serverApps.Start (Seconds (1.0));
	serverApps.Stop (Seconds (10.0));
	UdpEchoClientHelper echoClient (eidToxtrL.GetAddress(1), 900);
	echoClient.SetAttribute ("MaxPackets", UintegerValue (10));
	echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
	echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

	ApplicationContainer clientApps = echoClient.Install (c0.Get (0));
	ApplicationContainer clientApps = echoClient.Install (c0.Get (2));

	clientApps.Start (Seconds (2.0));
	clientApps.Stop (Seconds (10.0));

	//enable pcap tracing in promiscous mode
 	csma.EnablePcapAll ( " u " , true ) ; 

	//create the animation file 
	 AnimationInterface anim ("lisp-network-anim.xml");
	 

	 Simulator::Run();
	 Simulator::Destroy();

	 return 0;
	}
// end  example
}
