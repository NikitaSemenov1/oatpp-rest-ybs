#include "SystemItemService.hpp"

#include <utility>

oatpp::Object<StatusDto> get_status(oatpp::Int32 status_code, oatpp::String msg = "") {
  auto status = StatusDto::createShared();
  status->code = std::move(status_code);
  status->message = std::move(msg);
  return status;
}

oatpp::Object<StatusDto> SystemItemService::imports(const oatpp::Object<SystemItemImportRequest>&) {
  return get_status(200);
}
oatpp::Object<StatusDto> SystemItemService::deleteById(oatpp::String id) {
  return get_status(200);
}
oatpp::Object<StatusDto> SystemItemService::getById(oatpp::String id) {
  return get_status(200);
}