#pragma once
#include "../dappservices/dappservices.hpp"

#define SVC_RESP_IPFS(name) \
    SVC_RESP_X(ipfs,name)



#ifdef LIQUIDX

#define SVC_CONTRACT_NAME_IPFS SVC_CONTRACT_NAME_IPFS_undefined 

#else
#define SVC_CONTRACT_NAME_IPFS ipfsservice1 

#endif

#include "../dappservices/_ipfs_impl.hpp"



#define IPFS_DAPPSERVICE_BASE_ACTIONS \
SVC_ACTION(commit, false, ((std::vector<char>)(data)),     \
         ((uint32_t)(size))((std::string)(uri)), \
         ((uint32_t)(size))((std::string)(uri)),TONAME(SVC_CONTRACT_NAME_IPFS) ) \
{ \
    _ipfs_commit(size, uri, current_provider); \
    SEND_SVC_SIGNAL(commit, current_provider, package, size, uri)                         \
}; \
SVC_ACTION(cleanup, false, ((std::string)(uri)),     \
         ((uint32_t)(size))((std::string)(uri)), \
         ((uint32_t)(size))((std::string)(uri)),TONAME(SVC_CONTRACT_NAME_IPFS) ) \
{ \
    _ipfs_cleanup(size, uri, current_provider); \
    SEND_SVC_SIGNAL(cleanup, current_provider, package, size, uri)                         \
}; \
SVC_ACTION(warmup, true, ((std::string)(uri)),     \
         ((uint32_t)(size))((std::string)(uri)), \
         ((uint32_t)(size))((std::string)(uri))((std::vector<char>)(data)),TONAME(SVC_CONTRACT_NAME_IPFS) ) \
{ \
    _ipfs_warmup(size, uri, data, current_provider); \
    SEND_SVC_SIGNAL(warmup, current_provider, package, size, uri)                         \
};  \
static void svc_ipfs_commit(std::vector<char> data) { \
    SEND_SVC_REQUEST(commit, data) \
};\
static void svc_ipfs_cleanup(std::string uri) { \
    SEND_SVC_REQUEST(cleanup, uri) \
};\
static void svc_ipfs_warmup(std::string uri) { \
    SEND_SVC_REQUEST(warmup, uri) \
};


#ifdef IPFS_DAPPSERVICE_ACTIONS_MORE
#define IPFS_DAPPSERVICE_ACTIONS \
  IPFS_DAPPSERVICE_BASE_ACTIONS \
  IPFS_DAPPSERVICE_ACTIONS_MORE() 


#else
#define IPFS_DAPPSERVICE_ACTIONS \
  IPFS_DAPPSERVICE_BASE_ACTIONS
#endif


#ifndef IPFS_SVC_COMMANDS
#define IPFS_SVC_COMMANDS() (xcommit)(xcleanup)(xwarmup)


#ifndef IPFS_DAPPSERVICE_SKIP_HELPER
struct ipfs_svc_helper{
    IPFS_DAPPSERVICE_ACTIONS
};
#endif

#endif