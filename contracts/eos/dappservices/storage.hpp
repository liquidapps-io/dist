#pragma once
#include "../dappservices/dappservices.hpp"

#define SVC_RESP_STORAGE(name) \
    SVC_RESP_X(storage,name)

#define SVC_CONTRACT_NAME_STORAGE liquidstorag 


#include "../dappservices/_storage_impl.hpp"



#define STORAGE_DAPPSERVICE_BASE_ACTIONS \
  SVC_ACTION(strstore, false, ,              ((uint64_t)(size)),          ((uint64_t)(size)),"liquidstorag"_n) {     _storage_strstore(size, current_provider);     SEND_SVC_SIGNAL(strstore, current_provider, package, size)                         };\
SVC_ACTION(strhold, false, ,              ((uint64_t)(size)),          ((uint64_t)(size)),"liquidstorag"_n) {     _storage_strhold(size, current_provider);     SEND_SVC_SIGNAL(strhold, current_provider, package, size)                         };\
SVC_ACTION(strserve, false, ,              ((uint64_t)(size)),          ((uint64_t)(size)),"liquidstorag"_n) {     _storage_strserve(size, current_provider);     SEND_SVC_SIGNAL(strserve, current_provider, package, size)                         }; \
  static void svc_storage_strstore() {     SEND_SVC_REQUEST(strstore, ) };\
static void svc_storage_strhold() {     SEND_SVC_REQUEST(strhold, ) };\
static void svc_storage_strserve() {     SEND_SVC_REQUEST(strserve, ) };


#ifdef STORAGE_DAPPSERVICE_ACTIONS_MORE
#define STORAGE_DAPPSERVICE_ACTIONS \
  STORAGE_DAPPSERVICE_BASE_ACTIONS \
  STORAGE_DAPPSERVICE_ACTIONS_MORE() 


#else
#define STORAGE_DAPPSERVICE_ACTIONS \
  STORAGE_DAPPSERVICE_BASE_ACTIONS
#endif


#ifndef STORAGE_SVC_COMMANDS
#define STORAGE_SVC_COMMANDS() (xstrstore)(xstrhold)(xstrserve)


#ifndef STORAGE_DAPPSERVICE_SKIP_HELPER
struct storage_svc_helper{
    STORAGE_DAPPSERVICE_ACTIONS
};
#endif

#endif