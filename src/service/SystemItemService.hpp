#ifndef OATPP_REST_YBS_SRC_SERVICE_SYSTEMITEMSERVICE_HPP_
#define OATPP_REST_YBS_SRC_SERVICE_SYSTEMITEMSERVICE_HPP_

#include "dto/StatusDto.hpp"
#include "dto/RequestDTOs.hpp"

class SystemItemService {
 private:
 public:
  oatpp::Object<StatusDto> imports(const oatpp::Object<SystemItemImportRequest>&);
  oatpp::Object<StatusDto> deleteById(oatpp::String id);
  oatpp::Object<StatusDto> getById(oatpp::String id);
};

#endif //OATPP_REST_YBS_SRC_SERVICE_SYSTEMITEMSERVICE_HPP_
