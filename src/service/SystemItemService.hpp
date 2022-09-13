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

  bool systemItemExists(oatpp::String id);
 public:
  oatpp::Object<StatusDto> imports(const oatpp::Object<SystemItemImportRequest>&);
  oatpp::Object<StatusDto> deleteById(const oatpp::String& id);
  oatpp::Object<StatusDto> getById(const oatpp::String& id);
};

#endif //OATPP_REST_YBS_SRC_SERVICE_SYSTEMITEMSERVICE_HPP_
