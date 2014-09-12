#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include "CCC.h"

CCC::CCC()
{
    //ctor
}

CCC::CCC( CCC_Role_t role, <tbd> )
{
    pr_eRole = role;
    if (role == eMaster)
    {
        pr_anMyMACAddr = pu_anCCCMasterMACAddress;
        pr_anPeerMACAddr = {};
    } else {
        pr_anPeerMACAddr = pu_anCCCMasterMACAddress;
        pr_anMyMACAddr = {};
    }
    // Determine our MAC Address

}

CCC::~CCC()
{
    //dtor
}
