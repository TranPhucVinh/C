#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

#define NTP_SERVER  "time.google.com"
#define NTP_PORT 	"123"

#define NTP_TIMESTAMP_DELTA 2208988800ull

#define LI          0   // Leap indicator: NULL
#define VN          0b11   // NTP version 3, IPv4 only
#define CLIENT_MODE 0b11

struct ntp_packet {
    uint8_t li_vn_mode;      // Eight bits. li, vn, and mode.
    uint8_t stratum;         // Eight bits. Stratum level of the local clock.
    uint8_t poll;            // Eight bits. Maximum interval between successive messages.
    uint8_t precision;       // Eight bits. Precision of the local clock.
    uint32_t rootDelay;      // 32 bits. Total round-trip delay time.
    uint32_t rootDispersion; // 32 bits. Max error aloud from primary clock source.
    uint32_t refId;          // 32 bits. Reference clock identifier.
    uint32_t refTm_s;        // 32 bits. Reference time-stamp seconds.
    uint32_t refTm_f;        // 32 bits. Reference time-stamp fraction of a second.
    uint32_t origTm_s;       // 32 bits. Originate time-stamp seconds.
    uint32_t origTm_f;       // 32 bits. Originate time-stamp fraction of a second.
    uint32_t rxTm_s;         // 32 bits. Received time-stamp seconds.
    uint32_t rxTm_f;         // 32 bits. Received time-stamp fraction of a second.
    uint32_t txTm_s;         // 32 bits and the most important field the client cares about. Transmit time-stamp seconds.
    uint32_t txTm_f;         // 32 bits. Transmit time-stamp fraction of a second.
};

struct sockaddr_in ntp_server_addr; // Set global as ntp_server_addr is used by both udp_socket_param_init() and main()
socklen_t ntp_server_addr_len;

int udp_socket_param_init(char *ntp_server, char *ntp_port){
    struct addrinfo hints = {
		.ai_family = AF_INET,
		.ai_socktype = SOCK_STREAM,
	};
    struct addrinfo *ntp_server_response;
    int err = getaddrinfo(ntp_server, ntp_port, &hints, &ntp_server_response);
    if(err != 0 || ntp_server_response == NULL) {
		printf("DNS lookup failed err=%d res=%p", err, ntp_server_response);
		exit(1);
	}

    int receiver_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (receiver_fd < 0){
        perror("receiver_fd\n");
    } else printf("Create UDP receiver socket successfully\n");

    memcpy(&ntp_server_addr, ntp_server_response->ai_addr, ntp_server_response->ai_addrlen);
    ntp_server_addr_len = ntp_server_response->ai_addrlen;

    freeaddrinfo(ntp_server_response);
    return receiver_fd;
}

void init_ntp_packet(struct ntp_packet *packet) {
    memset(packet, 0, sizeof(struct ntp_packet));

    // NTP is MSB, so its li_vn_mode bits must be set like this order
    packet->li_vn_mode = LI;
    packet->li_vn_mode = (packet->li_vn_mode << 3) | VN;
    packet->li_vn_mode = (packet->li_vn_mode << 3) | CLIENT_MODE;
}

int main() {
    struct ntp_packet packet;
    ntp_server_addr_len = sizeof(ntp_server_addr);

    init_ntp_packet(&packet);// Initialize the NTP packet

    int receiver_fd = udp_socket_param_init(NTP_SERVER, NTP_PORT);

    // Send the NTP request
    if (sendto(receiver_fd, (char*) &packet, sizeof(struct ntp_packet), MSG_CONFIRM, (struct sockaddr *)&ntp_server_addr, ntp_server_addr_len) < 0) {
        perror("sendto");
        close(receiver_fd);
        return 1;
    }

    // Receive the NTP response
    if (recvfrom(receiver_fd, (char*) &packet, sizeof(struct ntp_packet), MSG_CONFIRM, (struct sockaddr *)&ntp_server_addr, &ntp_server_addr_len) < 0) {
        perror("recvfrom");
        close(receiver_fd);
        return 1;
    }

    close(receiver_fd);

    // Extract the transmit timestamp
    packet.txTm_s = ntohl(packet.txTm_s); // Get transmit time-stamp seconds
    packet.txTm_f = ntohl(packet.txTm_f); // Get transmit time-stamp fraction of a second

    // Convert NTP time to UNIX time (seconds since 1970)
    time_t txTm = (time_t)(packet.txTm_s - NTP_TIMESTAMP_DELTA);

    printf("Time: %s", ctime(&txTm));

    return 0;
}
