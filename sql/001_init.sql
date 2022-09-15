CREATE TABLE "systemitem" (
    "id" varchar(255) NOT NULL PRIMARY KEY,
    "url" varchar(255) NULL,
    "date" timestamp with time zone NOT NULL,
    "type" varchar(6) NOT NULL,
    "size" bigint NULL,
    "parentId" varchar(255) NULL);
ALTER TABLE "systemitem" ADD CONSTRAINT "systemitem_parentId_828a75e1_fk_systemitem_id" FOREIGN KEY ("parentId") REFERENCES "systemitem" ("id") ON DELETE CASCADE  DEFERRABLE INITIALLY DEFERRED;
CREATE INDEX "systemitem_id_e05b435f_like" ON "systemitem" ("id" varchar_pattern_ops);
CREATE INDEX "systemitem_parentId_828a75e1" ON "systemitem" ("parentId");
CREATE INDEX "systemitem_parentId_828a75e1_like" ON "systemitem" ("parentId" varchar_pattern_ops);
