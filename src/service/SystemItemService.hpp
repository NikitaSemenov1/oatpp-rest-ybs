#ifndef OATPP_REST_YBS_SRC_SERVICE_SYSTEMITEMSERVICE_HPP_
#define OATPP_REST_YBS_SRC_SERVICE_SYSTEMITEMSERVICE_HPP_

#include "dto/StatusDto.hpp"
#include "dto/RequestDTOs.hpp"
#include "db/SystemItemDb.hpp"

#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/protocol/http/Http.hpp"

class SystemItemService {
 private:
  typedef oatpp::web::protocol::http::Status Status;

  OATPP_COMPONENT(std::shared_ptr<db::SystemItemDb>, systemItemDb);

  bool systemItemExists(const oatpp::String& id);

  void add_subtree(oatpp::Object<SystemItem>& item, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);

  void update_size_date(const oatpp::String& id, const oatpp::String& date, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);

 public:
  oatpp::Object<StatusDto> imports(const oatpp::Object<SystemItemImportRequest>&);
  oatpp::Object<StatusDto> deleteById(const oatpp::String& id);
  oatpp::Object<SystemItem> getById(const oatpp::String& id);
};

#endif //OATPP_REST_YBS_SRC_SERVICE_SYSTEMITEMSERVICE_HPP_
