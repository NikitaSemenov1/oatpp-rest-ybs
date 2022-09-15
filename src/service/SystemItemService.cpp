#include "SystemItemService.hpp"
#include "Serializers.hpp"

#include "oatpp/web/protocol/http/Http.hpp"

#define DB_ASSERT(DB_RESPONSE) OATPP_ASSERT_HTTP(DB_RESPONSE->isSuccess(), Status ::CODE_500, DB_RESPONSE->getErrorMessage())

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
      if (systemItem->type == Type::FILE) {
        auto dbResponse = systemItemDb->udpateFile(systemItem);
        DB_ASSERT(dbResponse)
        update_size_date(systemItem->parentId, systemItem->updateDate);
      } else {
        auto dbResponse = systemItemDb->updateFolder(systemItem);
        DB_ASSERT(dbResponse)
      }

      OATPP_LOGD("SystemItem", "UPDATED System Item %s", systemItem->id->c_str())
    } else {
      auto dbResponse = systemItemDb->createSystemItem(systemItem);
      DB_ASSERT(dbResponse)

      OATPP_LOGD("SystemItem", "CREATED System Item %s", systemItem->id->c_str())
    }
  }
  return get_status(200, "OK");
}

oatpp::Object<StatusDto> SystemItemService::deleteById(const oatpp::String& id) {
  OATPP_ASSERT_HTTP(systemItemExists(id), Status::CODE_404, "System Item not found")

  auto parentId = getById(id)->parentId;

  auto dbResponse = systemItemDb->deleteSystemItemById(id);

  DB_ASSERT(dbResponse)

  OATPP_LOGD("SystemItem", "DELETED System Item %s", id->c_str())

//  update_size_date(parentId, );

  return get_status(200);
}

oatpp::Object<SystemItem> SystemItemService::getById(const oatpp::String& id) {

  auto dbResponse = systemItemDb->getSystemItemById(id);

  DB_ASSERT(dbResponse)

  OATPP_ASSERT_HTTP(dbResponse->hasMoreToFetch(), Status::CODE_404, "System Item not found")

  auto root = dbResponse->fetch<oatpp::Vector<oatpp::Object<SystemItem>>>()[0];
  add_subtree(root, dbResponse->getConnection());
  return root;
}

bool SystemItemService::systemItemExists(const oatpp::String& id) {
  auto dbResponse = systemItemDb->getId(id);

  OATPP_ASSERT_HTTP(dbResponse->isSuccess(), Status ::CODE_500, dbResponse->getErrorMessage())

  return dbResponse->hasMoreToFetch();
}
void SystemItemService::add_subtree(oatpp::Object<SystemItem> &item, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection) {
  if (item->type == Type::FILE) return;  // leave children null if it's file

  auto dbResponse = systemItemDb->getChildren(item->id, connection);

  OATPP_ASSERT_HTTP(dbResponse->isSuccess(), Status ::CODE_500, dbResponse->getErrorMessage())

  item->children = dbResponse->fetch<oatpp::Vector<oatpp::Object<SystemItem>>>();

  for (auto& child : *item->children) {
    add_subtree(child, connection);
  }
}
void SystemItemService::update_size_date(const oatpp::String &id,
                                         const oatpp::String &date,
                                         const oatpp::provider::ResourceHandle<oatpp::orm::Connection> &connection) {
  if (id == nullptr) return;  // if root is reached
  oatpp::Int64 new_size = std::make_shared<v_int64>(0);
  auto dbResponse = systemItemDb->getChildreSize(id, connection);

  DB_ASSERT(dbResponse)

  auto children = dbResponse->fetch<oatpp::Vector<oatpp::Object<SystemItem>>>();

  for (auto& child : *children) {
    new_size = new_size + child->size;
  }
  dbResponse = systemItemDb->updateSizeDate(id, new_size, date, connection);
  DB_ASSERT(dbResponse)
  auto item = getById(id);
  update_size_date(item->parentId, date, connection);
}