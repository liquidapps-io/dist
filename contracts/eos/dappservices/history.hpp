#pragma once
#include "../dappservices/dappservices.hpp"

#define SVC_RESP_HISTORY(name) \
    SVC_RESP_X(history,name)
    
#define SVC_CONTRACT_NAME_HISTORY historyservc 


#include "../dappservices/_history_impl.hpp"



#define HISTORY_DAPPSERVICE_BASE_ACTIONS \
  SVC_ACTION(hststore, false, ,              ((uint64_t)(size)),          ((uint64_t)(size)),"historyservc"_n) {     _history_hststore(size, current_provider);     SEND_SVC_SIGNAL(hststore, current_provider, package, request_id, size)                         };\
SVC_ACTION(hsthold, false, ,              ((uint64_t)(size)),          ((uint64_t)(size)),"historyservc"_n) {     _history_hsthold(size, current_provider);     SEND_SVC_SIGNAL(hsthold, current_provider, package, request_id, size)                         };\
SVC_ACTION(hstserve, false, ,              ((uint64_t)(size)),          ((uint64_t)(size)),"historyservc"_n) {     _history_hstserve(size, current_provider);     SEND_SVC_SIGNAL(hstserve, current_provider, package, request_id, size)                         };\
SVC_ACTION(hstreg, false, ,              ((uint64_t)(size)),          ((uint64_t)(size)),"historyservc"_n) {     _history_hstreg(size, current_provider);     SEND_SVC_SIGNAL(hstreg, current_provider, package, request_id, size)                         }; \
  static void svc_history_hststore() {     SEND_SVC_REQUEST(hststore, ) };\
static void svc_history_hsthold() {     SEND_SVC_REQUEST(hsthold, ) };\
static void svc_history_hstserve() {     SEND_SVC_REQUEST(hstserve, ) };\
static void svc_history_hstreg() {     SEND_SVC_REQUEST(hstreg, ) };


#ifdef HISTORY_DAPPSERVICE_ACTIONS_MORE
#define HISTORY_DAPPSERVICE_ACTIONS \
  HISTORY_DAPPSERVICE_BASE_ACTIONS \
  HISTORY_DAPPSERVICE_ACTIONS_MORE() 


#else
#define HISTORY_DAPPSERVICE_ACTIONS \
  HISTORY_DAPPSERVICE_BASE_ACTIONS 
#endif


#ifndef HISTORY_SVC_COMMANDS
#define HISTORY_SVC_COMMANDS() (xhststore)(xhsthold)(xhstserve)(xhstreg)


#ifndef HISTORY_DAPPSERVICE_SKIP_HELPER
struct history_svc_helper{
    HISTORY_DAPPSERVICE_ACTIONS
};
#endif

#endif