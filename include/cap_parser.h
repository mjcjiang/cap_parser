/**
 * @file cap_parser.h
 * @brief parse .cap file, fetch information in package header
 *
 * @date 2023-08-16
 */

#ifndef CAP_PARSER_H
#define CAP_PARSER_H

#include <iostream>
#include <memory>
#include <string>
#include <pcap.h>

class CapParser {
public:
    CapParser(const std::string& filename);
    void processPackages();
private:
    void processHeaders(const u_char* packet);
private:
    std::shared_ptr<pcap_t> pCapHandler_;
};

#endif //CAP_PARSER_H

