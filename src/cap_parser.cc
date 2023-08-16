#include "cap_parser.h"
#include <spdlog/spdlog.h>

CapParser::CapParser(const std::string& filename) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcapHandler_ = std::shared_ptr<pcap_t>(pcap_open_offline(filename.c_str(), errbuf), pcap_close);
    if (pcapHandle == nullptr) {
        SPDLOG_ERROR("Error opening file: {}", errbuf);
    }
}

void CapParser::processPackages() {
    struct pcap_pkthdr header;
    const u_char* packet;
    while((packet = pcap_next(pcapHandler_.get(), &header)) != NULL) {
        processHeaders(packet);
    }
}

void CapParser::processHeaders(const u_char* package) {
    //解析源MAC地址和目的MAC地址
    struct ether_header* eth_header = (struct ether_header*)packet;
    const u_char* src_mac = eth_header->ether_shost;
    const u_char* dst_mac = eth_header->ether_dhost;

    char src_mac_str[MAC_ADDR_LEN];
    char dst_mac_str[MAC_ADDR_LEN];
    sprintf(src_mac_str, "%02x:%02x:%02x:%02x:%02x:%02x",
            src_mac[0], src_mac[1], src_mac[2],
            src_mac[3], src_mac[4], src_mac[5]);
    sprintf(dst_mac_str, "%02x:%02x:%02x:%02x:%02x:%02x",
            dst_mac[0], dst_mac[1], dst_mac[2],
            dst_mac[3], dst_mac[4], dst_mac[5]);

    //协议类型解析
    struct ip* ip_header = (struct ip*)(packet + ETHER_HEADER_LEN);
    int protocol = ip_header->ip_p;

    if (protocol == IPPROTO_TCP) {
        struct tcphdr* tcp_header = (struct tcphdr*)(packet + ETHER_HEADER_LEN + ip_header->ip_hl * 4); // Skip IP header
        uint16_t src_port = ntohs(tcp_header->th_sport);
        uint16_t dst_port = ntohs(tcp_header->th_dport);
        uint32_t seq_num = ntohl(tcp_header->th_seq);

        std::cout << "Tcp Protocol: " << std::endl;
        std::cout << "Source Address: " << inet_ntoa(ip_header->ip_src) << std::endl;
        std::cout << "Source Port: " << src_port << std::endl;
        std::cout << "Dest Address: " << inet_ntoa(ip_header->ip_dst) << std::endl;
        std::cout << "Dest Port: " << dst_port << std::endl;
        std::cout << "Sequence Number: " << seq_num << std::endl;
    } else if(protocol == IPPROTO_UDP) {
        struct udphdr* udp_header = (struct udphdr*)(packet + ETHER_HEADER_LEN + ip_header->ip_hl * 4); // Skip IP header
        uint16_t src_port = ntohs(udp_header->uh_sport);
        uint16_t dst_port = ntohs(udp_header->uh_dport);

        std::cout << "Udp Protocol" << std::endl;
        std::cout << "Source Address: " << inet_ntoa(ip_header->ip_src) << std::endl;
        std::cout << "Source Port: " << src_port << std::endl;
        std::cout << "Dest Address: " << inet_ntoa(ip_header->ip_dst) << std::endl;
        std::cout << "Dest Port: " << dst_port << std::endl;
    }
    std::cout << "Source MAC: " << src_mac_str << std::endl;
    std::cout << "Destination MAC: " << dst_mac_str << std::endl;
}

