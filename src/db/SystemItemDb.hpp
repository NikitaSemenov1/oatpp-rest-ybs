
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
     migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
     // TODO - Add more migrations here.
     migration.migrate(); // <-- run migrations. This guy will throw on error.

     auto version = executor->getSchemaVersion();
     OATPP_LOGD("SystemItemDb", "Migration - OK. Version=%d.", version);
   }

   QUERY(createSystemItem,
         "INSERT INTO SystemItem"
         "(id, url, date, parentId, type, size) VALUES"
         ":systemItem.id , :systemItem.url, :systemItem.parentId, :systemItem.type, :systemItem.size",
         PREPARE(true),
         PARAM(oatpp::Object<SystemItem>, systemItem))
 };
 }
#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //SYSTEM_UNIT_DB_HPP