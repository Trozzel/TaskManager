/******************************************************************************
 * The creation of the tables must occur in this order due to dependencies:
 * 1. folders
 * 2. contexts
 * 3. projects
 * 4. tasks
 ******************************************************************************/

.read create_contexts.sql
.read create_folders.sql
.read create_projects.sql
.read create_tasks.sql

.mode columns
.headers on
