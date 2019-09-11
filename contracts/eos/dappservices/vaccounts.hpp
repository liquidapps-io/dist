#pragma once
#include "../dappservices/dappservices.hpp"

#define SVC_RESP_VACCOUNTS(name) \
    SVC_RESP_X(vaccounts,name)
    
#define SVC_CONTRACT_NAME_VACCOUNTS accountless1 


#include "../dappservices/_vaccounts_impl.hpp"



#define VACCOUNTS_DAPPSERVICE_BASE_ACTIONS \
  SVC_ACTION(vexec, false, ,              ((eosio::signature)(sig))((eosio::public_key)(pubkey)),          ((std::vector<char>)(payload))((eosio::signature)(sig))((eosio::public_key)(pubkey)),"accountless1"_n) {     _vaccounts_vexec(payload, sig, pubkey, current_provider);     SEND_SVC_SIGNAL(vexec, current_provider, package, request_id, sig, pubkey)                         }; \
  static void svc_vaccounts_vexec() {     SEND_SVC_REQUEST(vexec, ) };


#ifdef VACCOUNTS_DAPPSERVICE_ACTIONS_MORE
#define VACCOUNTS_DAPPSERVICE_ACTIONS \
  VACCOUNTS_DAPPSERVICE_BASE_ACTIONS \
  VACCOUNTS_DAPPSERVICE_ACTIONS_MORE() 


#else
#define VACCOUNTS_DAPPSERVICE_ACTIONS \
  VACCOUNTS_DAPPSERVICE_BASE_ACTIONS 
#endif


#ifndef VACCOUNTS_SVC_COMMANDS
#define VACCOUNTS_SVC_COMMANDS() (xvexec)


#ifndef VACCOUNTS_DAPPSERVICE_SKIP_HELPER
struct vaccounts_svc_helper{
    VACCOUNTS_DAPPSERVICE_ACTIONS
};
#endif

#endif