#pragma once
#include "../dappservices/dappservices.hpp"

#define SVC_RESP_SIGN(name) \
    SVC_RESP_X(sign,name)
    
#define SVC_CONTRACT_NAME_SIGN signfndspsvc 


#include "../dappservices/_sign_impl.hpp"



#define SIGN_DAPPSERVICE_BASE_ACTIONS \
  SVC_ACTION(signtrx, true, ((name)(account))((name)(permission))((std::string)(client_code))((checksum256)(payload_hash))((std::vector<char>)(signature)),              ((name)(account))((name)(permission))((std::string)(client_code))((checksum256)(payload_hash))((std::vector<char>)(signature)),          ((name)(account))((name)(permission))((std::string)(client_code))((checksum256)(payload_hash))((std::vector<char>)(signature)),"signfndspsvc"_n) {     _sign_signtrx(account, permission, client_code, payload_hash, signature, current_provider);     SEND_SVC_SIGNAL(signtrx, current_provider, package, account, permission, client_code, payload_hash, signature)                         };\
SVC_ACTION(sgcleanup, false, ((name)(account))((name)(permission))((std::string)(client_code))((checksum256)(payload_hash))((std::vector<char>)(signature)),              ((name)(account))((name)(permission))((std::string)(client_code))((checksum256)(payload_hash))((std::vector<char>)(signature)),          ((name)(account))((name)(permission))((std::string)(client_code))((checksum256)(payload_hash))((std::vector<char>)(signature)),"signfndspsvc"_n) {     _sign_sgcleanup(account, permission, client_code, payload_hash, signature, current_provider);     SEND_SVC_SIGNAL(sgcleanup, current_provider, package, account, permission, client_code, payload_hash, signature)                         }; \
  static void svc_sign_signtrx(name account, name permission, std::string client_code, checksum256 payload_hash, std::vector<char> signature) {     SEND_SVC_REQUEST(signtrx, account, permission, client_code, payload_hash, signature) };\
static void svc_sign_sgcleanup(name account, name permission, std::string client_code, checksum256 payload_hash, std::vector<char> signature) {     SEND_SVC_REQUEST(sgcleanup, account, permission, client_code, payload_hash, signature) };


#ifdef SIGN_DAPPSERVICE_ACTIONS_MORE
#define SIGN_DAPPSERVICE_ACTIONS \
  SIGN_DAPPSERVICE_BASE_ACTIONS \
  SIGN_DAPPSERVICE_ACTIONS_MORE() 


#else
#define SIGN_DAPPSERVICE_ACTIONS \
  SIGN_DAPPSERVICE_BASE_ACTIONS 
#endif


#ifndef SIGN_SVC_COMMANDS
#define SIGN_SVC_COMMANDS() (xsigntrx)(xsgcleanup)


#ifndef SIGN_DAPPSERVICE_SKIP_HELPER
struct sign_svc_helper{
    SIGN_DAPPSERVICE_ACTIONS
};
#endif

#endif