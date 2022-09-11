#ifndef DTOs_hpp
#define DTOs_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */

ENUM(Type, v_uint8,
     VALUE(FILE, 0, "FILE"),
     VALUE(FOLDER, 1, "FOLDER")
)

class SystemItemImport : public oatpp::DTO {

    DTO_INIT(SystemItemImport, DTO)

    DTO_FIELD(String, id, "id");
    DTO_FIELD(String, url, "url");
    DTO_FIELD(UInt64, date, "date");
    DTO_FIELD(String, parentId, "ParentId");
    DTO_FIELD(Enum<Type>::AsString, type, "type");
    DTO_FIELD(UInt64, size, "size");
};

class SystemItem : public SystemItemImport {

  DTO_INIT(SystemItem, DTO)

  DTO_FIELD(UnorderedSet<Object<SystemItem>>, children, "children");
};

class SystemItemImportRequest : public oatpp::DTO {

    DTO_INIT(SystemItemImportRequest, DTO)

    DTO_FIELD(Vector<Object<SystemItemImport>>, items, "items");
    DTO_FIELD(String, updateDate, "updateDate");
};

#include OATPP_CODEGEN_END(DTO)

#endif /* DTOs_hpp */
