
#ifndef SYSTEM_UNIT_DB_HPP
#define SYSTEM_UNIT_DB_HPP

#include "dto/RequestDTOs.hpp"
#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * UserDb client definitions.
 */
 namespace db {
 class SystemItemDb : public oatpp::orm::DbClient {
  public:

   SystemItemDb(const std::shared_ptr<oatpp::orm::Executor> &executor)
       : oatpp::orm::DbClient(executor) {

     oatpp::orm::SchemaMigration migration(executor);
     migration.addFile(1 /* start fr  om version 1 */, DATABASE_MIGRATIONS "/001_init.sql");

     migration.migrate(); // <-- run migrations. This guy will throw on error.

     auto version = executor->getSchemaVersion();
     OATPP_LOGD("SystemItemDb", "Migration - OK. Version=%d.", version);
   }

   QUERY(createSystemItem,
         "INSERT INTO SystemItem"
         "(id, url, date, parent_id, type, size) VALUES "
         "(:systemItem.id , :systemItem.url, CAST( :systemItem.updateDate AS TIMESTAMP WITH TIME ZONE), :systemItem.parentId, :systemItem.type, :systemItem.size);",
         PREPARE(true),
         PARAM(oatpp::Object<SystemItem>, systemItem))

   QUERY(getSystemItemById,
         "SELECT * FROM SystemItem WHERE id=:id;",
         PARAM(oatpp::String, id))

   QUERY(udpateSystemItem,
         "UPDATE SystemItem "
         "SET "
         " url=:systemItem.url, "
         " date=CAST( :systemItem.updateDate AS TIMESTAMP WITH TIME ZONE), "
         " parent_id=:systemItem.parentId, "
         " type=:systemItem.type, "
         " size=:systemItem.size "
         "WHERE "
         " id=:systemItem.id;",
         PARAM(oatpp::Object<SystemItem>, systemItem))

   QUERY(deleteSystemItemById,
         "DELETE FROM SystemItem WHERE id=:id;",
         PARAM(oatpp::String, id))

   QUERY(getId,
         "SELECT id FROM SystemItem WHERE id=:id;",
         PARAM(oatpp::String, id))
 };
 }
#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //SYSTEM_UNIT_DB_HPP