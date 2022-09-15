
#ifndef SYSTEM_UNIT_DB_HPP
#define SYSTEM_UNIT_DB_HPP

#include "dto/RequestDTOs.hpp"
#include "oatpp-postgresql/orm.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * UserDb client definitions.
 */
 namespace db {
 class SystemItemDb : public oatpp::orm::DbClient {
  public:

   SystemItemDb(const std::shared_ptr<oatpp::orm::Executor> &executor)
       : oatpp::orm::DbClient(executor) {

     setEnabledInterpretations({"protobuf"});

     oatpp::orm::SchemaMigration migration(executor);
     migration.addFile(1 /* start fr  om version 1 */, DATABASE_MIGRATIONS "/001_init.sql");

     migration.migrate(); // <-- run migrations. This guy will throw on error.

     auto version = executor->getSchemaVersion();
     OATPP_LOGD("SystemItemDb", "Migration - OK. Version=%d.", version);
   }

   QUERY(createSystemItem,
         "INSERT INTO SystemItem"
         "(id, url, date, \"parentId\", type, size) VALUES "
         "(:systemItem.id , :systemItem.url, CAST( :systemItem.date AS TIMESTAMP), :systemItem.parentId, :systemItem.type, :systemItem.size);",
         PREPARE(true),
         PARAM(oatpp::Object<SystemItem>, systemItem))

   QUERY(getSystemItemById,
         "SELECT id, url, to_char(date, 'YYYY-MM-DDT') || to_char(date,'HH24:MI:SSZ') as date, \"parentId\", type, size FROM SystemItem WHERE id=:id;",
         PARAM(oatpp::String, id))

   QUERY(udpateFile,
         "UPDATE SystemItem "
         "SET "
         " url=:systemItem.url, "
         " date=CAST( :systemItem.date AS TIMESTAMP), "
         " \"parentId\"=:systemItem.parentId, "
         " size=:systemItem.size "
         "WHERE "
         " id=:systemItem.id;",
         PARAM(oatpp::Object<SystemItem>, systemItem))

   QUERY(updateFolder,
         "UPDATE SystemItem "
         "SET "
         " date=CAST( :systemItem.date AS TIMESTAMP), "
         " \"parentId\"=:systemItem.parentId "
         "WHERE "
         " id=:systemItem.id;",
         PARAM(oatpp::Object<SystemItem>, systemItem))

   QUERY(deleteSystemItemById,
         "DELETE FROM SystemItem WHERE id=:id;",
         PARAM(oatpp::String, id))

   QUERY(getId,
         "SELECT id FROM SystemItem WHERE id=:id;",
         PARAM(oatpp::String, id))

   QUERY(getChildren,
         "SELECT id, url, to_char(date, 'YYYY-MM-DDT') || to_char(date,'HH24:MI:SSZ') as date, \"parentId\", type, size FROM SystemItem WHERE \"parentId\"=:id;",
         PARAM(oatpp::String, id))

   QUERY(getChildreSize,
         "SELECT size FROM SystemItem WHERE \"parentId\"=:id;",
         PARAM(oatpp::String, id))

   QUERY(updateSizeDate,
         "UPDATE SystemItem "
         "SET "
         " size=:size, "
         " date=CAST(:date AS TIMESTAMP) "
         "WHERE "
         " id=:id",
         PARAM(oatpp::String, id),
         PARAM(oatpp::Int64, size),
         PARAM(oatpp::String, date))
 };
 }
#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //SYSTEM_UNIT_DB_HPP