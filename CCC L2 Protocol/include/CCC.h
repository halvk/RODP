#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>

#ifndef CCC_H
#define CCC_H

#define ETH_FRAME_LEN 64


class CCC
{
    public:
        typedef enum            CCC_Role_t { eMaster, eSlave };

        typedef uint8_t[6]      MAC_Addr_t;
        const MAC_Addr_t        pu_anCCCMasterMACAddress = {0x01, 0x00, 0x5E, 0x00, 0x00, 0x00};

        CCC ( CCC_Role_t role, <tbd> );
        virtual ~CCC();

        //
        // Allowed operations
        //

        int DataRead            ( const uint16_t table,
                                  const uint16_t start_address,
                                  uint8_t num_bytes );
        void DataReadResponse   ( uint16_t &table,
                                  uint16_t &start_address,
                                  uint8_t &data[] );
        int DataWrite           ( const uint16_t table,
                                  const uint16_t start_address,
                                  const uint8_t data[] );
        void DataWriteResponse  ( uint16_t &table,
                                  uint16_t &start_address,
                                  uint8_t &data[] );
        int SlaveRead           ( const uint8_t attribute_type );
        void SlaveReadResponse  ( uint8_t &attribute_type,
                                  uint8_t &attribute_value[] );
        int SlaveWrite          ( const uint8_t attribute_type,
                                  const uint8_t attribute_value[] );
        void SlaveWriteResponse ( uint8_t &attribute_type,
                                  uint8_t &attribute_value[] );
        int SendStatusMsg       ( void );
        MAC_Addr_t& PeerMACAddr ( void );

    protected:

    private:
        CCC();  // To block creation of instances without initialization

        CCC_Role_t          pr_eRole;
        MAC_Addr_t          pr_anPeerMACAddr = { 0 };
        MAC_Addr_t          pr_anMyMACAddr = { 0 };
        queue               pr_aInbound;
        queue               pr_aOutbound;

        struct CCC_Packet_t
        {
            MAC_Addr_t      destination;
            MAC_Addr_t      source;
            uint16_t        type;
            uint8_t         rodp_status_bits[3];
            uint8_t         cmd_and_data[43];
            uint32_t        crc;
        };


        /*target address*/
        struct sockaddr_ll  pr_socket_address;

        void* AllocPacket   ()
        {
            /*buffer for ethernet frame*/
            void* buffer = (void*)malloc(ETH_FRAME_LEN);

        }

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

};

#endif // CCC_H
