// Customer demarcation Control Channel Class Library
//
// Each instance of this class corresponds to one end of
// a CCC between a Master and a Slave.

#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include "if_CCC.h"             // NOTE: Rename this file to match this .h file!
                                // Remember to place header guards around it, using IF_CCC define.

//
// Create a RAW Ethernet socket
//

int s; /*socketdescriptor*/

s = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
if (s == -1) { errorhandling ... }

//
// Send a RAW Ethernet frame
//

#define ETH_FRAME_LEN 1518

...

/*target address*/
struct sockaddr_ll socket_address;

/*buffer for ethernet frame*/
void* buffer = (void*)malloc(ETH_FRAME_LEN);

/*pointer to ethenet header*/
unsigned char* etherhead = buffer;

/*userdata in ethernet frame*/
unsigned char* data = buffer + 14;

/*another pointer to ethernet header*/
struct ethhdr *eh = (struct ethhdr *)etherhead;

int send_result = 0;

/*our MAC address*/
unsigned char src_mac[6] = {0x00, 0x01, 0x02, 0xFA, 0x70, 0xAA};

/*other host MAC address*/
unsigned char dest_mac[6] = {0x00, 0x04, 0x75, 0xC8, 0x28, 0xE5};

/*prepare sockaddr_ll*/

/*RAW communication*/
socket_address.sll_family   = PF_PACKET;
/*we don't use a protocoll above ethernet layer
  ->just use anything here*/
socket_address.sll_protocol = htons(ETH_P_IP);

/*index of the network device
see full code later how to retrieve it*/
socket_address.sll_ifindex  = 2;

/*ARP hardware identifier is ethernet*/
socket_address.sll_hatype   = ARPHRD_ETHER;

/*target is another host*/
socket_address.sll_pkttype  = PACKET_OTHERHOST;

/*address length*/
socket_address.sll_halen    = ETH_ALEN;
/*MAC - begin*/
socket_address.sll_addr[0]  = 0x00;
socket_address.sll_addr[1]  = 0x04;
socket_address.sll_addr[2]  = 0x75;
socket_address.sll_addr[3]  = 0xC8;
socket_address.sll_addr[4]  = 0x28;
socket_address.sll_addr[5]  = 0xE5;
/*MAC - end*/
socket_address.sll_addr[6]  = 0x00;/*not used*/
socket_address.sll_addr[7]  = 0x00;/*not used*/


/*set the frame header*/
memcpy((void*)buffer, (void*)dest_mac, ETH_ALEN);
memcpy((void*)(buffer+ETH_ALEN), (void*)src_mac, ETH_ALEN);
eh->h_proto = 0x00;
/*fill the frame with some data*/
for (j = 0; j < 1500; j++) {
	data[j] = (unsigned char)((int) (255.0*rand()/(RAND_MAX+1.0)));
}

/*send the packet*/
send_result = sendto(s, buffer, ETH_FRAME_LEN, 0,
	      (struct sockaddr*)&socket_address, sizeof(socket_address));
if (send_result == -1) { errorhandling... }

//
// Receive a RAW Ethernet frame
//

void* buffer = (void*)malloc(ETH_FRAME_LEN); /*Buffer for ethernet frame*/
int length = 0; /*length of the received frame*/
...
length = recvfrom(s, buffer, ETH_FRAME_LEN, 0, NULL, NULL);
if (length == -1) { errorhandling .... }



extern "C"
{
    // A function adding two integers and returning the result
    int SampleAddInt(int i1, int i2)
    {
        return i1 + i2;
    }

    // A function doing nothing ;)
    void SampleFunction1()
    {
        // insert code here
    }

    // A function always returning zero
    int SampleFunction2()
    {
        // insert code here

        return 0;
    }
}
