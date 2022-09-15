#ifndef MyController_hpp
#define MyController_hpp

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/Types.hpp"

#include "dto/RequestDTOs.hpp"

#include "service/SystemItemService.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class APIController : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  APIController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
 private:
  SystemItemService systemItemService;
 public:

  ENDPOINT("POST", "imports", post_imports,
           BODY_DTO(Object<SystemItemImportRequest>, systemItemImportRequest)) {
    return createDtoResponse(Status::CODE_200, systemItemService.imports(systemItemImportRequest));
  }

  ENDPOINT("GET", "nodes/{id}", get_node, PATH(String, id)) {
      return createDtoResponse(Status::CODE_200, systemItemService.getById(id));
  }

  ENDPOINT("DELETE", "delete/{id}", delete_node, PATH(String, id),
           QUERY(String, date)) {
      return createDtoResponse(Status::CODE_200, systemItemService.deleteById(id, date));
  }
  
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */
