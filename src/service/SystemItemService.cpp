#include "SystemItemService.hpp"
#include "Serializers.hpp"

#include "oatpp/web/protocol/http/Http.hpp"

oatpp::Object<StatusDto> get_status(oatpp::Int32 status_code, oatpp::String msg = "") {
  auto status = StatusDto::createShared();
  status->code = std::move(status_code);
  status->message = std::move(msg);
  return status;
}

oatpp::Object<StatusDto> SystemItemService::imports(const oatpp::Object<SystemItemImportRequest>& systemItemImportRequest) {
  for (auto &systemItem : *systemItemImportRequest->items) {
    systemItem->updateDate = systemItemImportRequest->updateDate;

    if (systemItemExists(systemItem->id)) {
      auto dbResponse = systemItemDb->udpateSystemItem(systemItem);

      OATPP_ASSERT_HTTP(dbResponse->isSuccess(), Status ::CODE_500, dbResponse->getErrorMessage())

      OATPP_LOGD("SystemItem", "UPDATED System Item %s", systemItem->id->c_str())
    } else {
      auto dbResponse = systemItemDb->createSystemItem(systemItem);
      OATPP_ASSERT_HTTP(dbResponse->isSuccess(), Status::CODE_500, dbResponse->getErrorMessage())

      OATPP_LOGD("SystemItem", "CREATED System Item %s", systemItem->id->c_str())
    }
  }
  return get_status(200, "OK");
}
oatpp::Object<StatusDto> SystemItemService::deleteById(const oatpp::String& id) {
  OATPP_ASSERT_HTTP(systemItemExists(id), Status::CODE_404, "System Item not found")

  auto dbResponse = systemItemDb->deleteSystemItemById(id);

  OATPP_ASSERT_HTTP(dbResponse->isSuccess(), Status ::CODE_500, dbResponse->getErrorMessage())

  OATPP_LOGD("SystemItem", "DELETED System Item %s", id->c_str())

  return get_status(200);
}
oatpp::Object<StatusDto> SystemItemService::getById(const oatpp::String& id) {

  auto dbResponse = systemItemDb->getSystemItemById(id);

  OATPP_ASSERT_HTTP(dbResponse->isSuccess(), Status ::CODE_500, dbResponse->getErrorMessage())

  OATPP_ASSERT_HTTP(dbResponse->hasMoreToFetch(), Status::CODE_404, "System Item not found");

  return get_status(200);
}
bool SystemItemService::systemItemExists(oatpp::String id) {
  auto dbResponse = systemItemDb->getId(id);

  OATPP_ASSERT_HTTP(dbResponse->isSuccess(), Status ::CODE_500, dbResponse->getErrorMessage())

  return dbResponse->hasMoreToFetch();
}
