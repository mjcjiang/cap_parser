#include "xtp_trader_api.h"
#include "xtp_trader.h"
#include "config_fetch.h"
#include <spdlog/spdlog.h>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    int request_id = 1;
    
    XtpInfo xtp_info;
    bool res = get_xtp_info("./configs/xtp.json", xtp_info);
    if (!res) {
        SPDLOG_INFO("Load config failed...");
        return -1;
    }
    
    XTP::API::TraderApi* pUserApi = XTP::API::TraderApi::CreateTraderApi(xtp_info.client_id, ".", XTP_LOG_LEVEL_DEBUG);
    if (!pUserApi) {
        SPDLOG_INFO("Failed to create trader api, please check input parameter...");
        return -1;
    }

    pUserApi->SubscribePublicTopic(XTP_TERT_QUICK); //只传输登陆后的公有流
    pUserApi->SetSoftwareVersion("1.0.0");          //设置软件版本号
    pUserApi->SetSoftwareKey(xtp_info.key.c_str()); //设置开发key
    pUserApi->SetHeartBeatInterval(10);             //设置心跳检查时间

    MyTraderSpi* pUserSpi = new MyTraderSpi();
    if(!pUserSpi) {
        SPDLOG_WARN("Failed to create user spi...");
        return -1;
    }

    pUserApi->RegisterSpi(pUserSpi);
    pUserSpi->setUserAPI(pUserApi);

    //开始登陆交易前台
    uint64_t session_id = pUserApi->Login(xtp_info.td_address.c_str(),
                                          xtp_info.td_port,
                                          xtp_info.user.c_str(),
                                          xtp_info.login_password.c_str(),
                                          XTP_PROTOCOL_TCP);

    if(session_id > 0) {
        SPDLOG_INFO("Login Success...");
    } else {
        XTPRI* error_info = pUserApi->GetApiLastError();
        SPDLOG_WARN("{} login to server error, error id {}, error message {}",
                    xtp_info.user,
                    error_info->error_id,
                    error_info->error_msg);
    }

    res = pUserApi->QueryOptionAuctionInfo(nullptr, session_id, request_id);
    if(res != 0) {
        XTPRI* error_info = pUserApi->GetApiLastError();
        SPDLOG_WARN("{} query option action info, error id {}, error message {}",
                    xtp_info.user,
                    error_info->error_id,
                    error_info->error_msg);
    }

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    return 0;
}
