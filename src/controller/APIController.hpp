#ifndef MyController_hpp
#define MyController_hpp

#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

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
public:

  ENDPOINT("POST", "imports", post_imports) {
      return createResponse(Status::CODE_200, "TODO");
  }

  ENDPOINT("GET", "nodes/{id}", get_node, PATH(String, id)) {
      return createResponse(Status::CODE_200, "TODO");
  }

  ENDPOINT("DELETE", "nodes/{id}", delete_node, PATH(String, id)) {
      return createResponse(Status::CODE_200, "TODO");
  }
  
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */
