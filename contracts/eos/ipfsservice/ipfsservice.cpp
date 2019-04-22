#define SVC_NAME ipfs
#include "../dappservices/ipfs.hpp"
CONTRACT ipfsservice : public eosio::contract {
  using contract::contract;

private:
public:
  
  DAPPSERVICE_PROVIDER_ACTIONS
  IPFS_DAPPSERVICE_ACTIONS
  STANDARD_USAGE_MODEL(commit)
STANDARD_USAGE_MODEL(cleanup)
STANDARD_USAGE_MODEL(warmup)

#ifdef IPFS_DAPPSERVICE_SERVICE_MORE
  IPFS_DAPPSERVICE_SERVICE_MORE
#endif
  
  struct model_t {
    HANDLE_MODEL_SIGNAL_FIELD(commit)
HANDLE_MODEL_SIGNAL_FIELD(cleanup)
HANDLE_MODEL_SIGNAL_FIELD(warmup)
  };
  TABLE providermdl {
    model_t model;
    name package_id;
    uint64_t primary_key() const { return package_id.value; }
  };
    
  typedef eosio::multi_index<"providermdl"_n, providermdl> providermodels_t;  

 [[eosio::action]] void xsignal(name service, name action,
                 name provider, name package, std::vector<char> signalRawData) {
    if (current_receiver() != service || _self != service) 
      return;
    require_auth(get_first_receiver());
    HANDLECASE_SIGNAL_TYPE(commit)
HANDLECASE_SIGNAL_TYPE(cleanup)
HANDLECASE_SIGNAL_TYPE(warmup)
  }
  
  DAPPSERVICE_PROVIDER_BASIC_ACTIONS
};

EOSIO_DISPATCH_SVC_PROVIDER(ipfsservice)
