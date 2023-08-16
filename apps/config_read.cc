#include <iostream>
#include "config_fetch.h"

int main() {
    AccountInfo acct_info;
    bool res = get_account_info("./configs/account.json", acct_info);
    if (res) {
        std::cout << "account_id: " << acct_info.account_id << std::endl;
    }

    XtpInfo xtp_info;
    res = get_xtp_info("./configs/xtp.json", xtp_info);
    if (res) {
        std::cout << xtp_info.client_id << std::endl;
        std::cout << xtp_info.key << std::endl;
        std::cout << xtp_info.login_password << std::endl;
        std::cout << xtp_info.md_address << std::endl;
        std::cout << xtp_info.td_address << std::endl;
    }
    return 0;
}
