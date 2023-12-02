--
-- File generated with SQLiteStudio v3.2.1 on Fri Dec 1 21:39:44 2023
--
-- Text encoding used: UTF-8
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: contexts
CREATE TABLE contexts (
    uniqueId INTEGER PRIMARY KEY ASC AUTOINCREMENT
                     UNIQUE
                     NOT NULL,
    name     TEXT    NOT NULL,
    parentId INTEGER DEFAULT NULL
                     REFERENCES contexts (uniqueId) ON UPDATE CASCADE
                                                    ON DELETE SET DEFAULT,
    status   TEXT    NOT NULL
                     DEFAULT Active
                     CONSTRAINT contextsStatus CHECK (status = "Active" OR 
                                                      status = "OnHold" OR 
                                                      status = "Dropped"),
    created  TEXT    DEFAULT (datetime('now', 'utc') ) 
                     NOT NULL
                     CHECK (created = datetime(created) ),
    modified TEXT    DEFAULT (datetime('now', 'utc') ) 
                     NOT NULL
                     CHECK (modified = datetime(modified) ) 
);


-- Table: folders
CREATE TABLE folders (
    uniqueId INTEGER PRIMARY KEY ASC AUTOINCREMENT
                     UNIQUE
                     NOT NULL,
    name     TEXT    NOT NULL,
    parentId INTEGER DEFAULT NULL
                     REFERENCES folders (uniqueId) ON UPDATE CASCADE
                                                   ON DELETE SET DEFAULT,
    status   TEXT    NOT NULL
                     DEFAULT Active
                     CONSTRAINT foldersStatus CHECK (status = "Active" OR 
                                                     status = "Dropped"),
    created  TEXT    DEFAULT (datetime('now', 'utc') ) 
                     NOT NULL
                     CHECK (created = datetime(created) ),
    modified TEXT    DEFAULT (datetime('now', 'utc') ) 
                     NOT NULL
                     CHECK (modified = datetime(modified) ) 
);


-- Table: projects
CREATE TABLE projects (
    uniqueId         INTEGER   PRIMARY KEY ASC AUTOINCREMENT
                               UNIQUE
                               NOT NULL,
    name             TEXT      NOT NULL,
    parentId         INTEGER   DEFAULT NULL
                               REFERENCES projects (uniqueId) ON UPDATE CASCADE
                                                              ON DELETE SET DEFAULT,
    status           TEXT      NOT NULL
                               DEFAULT Active
                               CONSTRAINT projectsStatus CHECK (status = "Active" OR 
                                                                status = "OnHold" OR 
                                                                status = "Dropped" OR 
                                                                status = "Completed"),
    created          TEXT      DEFAULT (datetime('now', 'utc') ) 
                               NOT NULL
                               CHECK (created = datetime(created) ),
    modified         TEXT      DEFAULT (datetime('now', 'utc') ) 
                               NOT NULL
                               CHECK (modified = datetime(modified) ),
    contextId        INTEGER   DEFAULT NULL
                               REFERENCES contexts (uniqueId) ON UPDATE CASCADE
                                                              ON DELETE SET DEFAULT,
    folderId         INTEGER   DEFAULT NULL
                               REFERENCES folders (uniqueId) ON UPDATE CASCADE
                                                             ON DELETE SET DEFAULT,
    flagged          INTEGER   NOT NULL
                               DEFAULT false
                               CHECK (flagged = 0 OR 
                                      flagged = 1),
    [deferred]       TEXT      CHECK ("deferred" = datetime("deferred") ),
    due              TEXT      CHECK (due = datetime(due) ),
    isRepeating      INTEGER   NOT NULL
                               DEFAULT false
                               CHECK (isRepeating = 0 OR 
                                      isRepeating = 1),
    repeatFrom       TEXT      NOT NULL
                               DEFAULT Due
                               CHECK (repeatFrom = "Due" OR 
                                      "Deferred"),
    repeatSchedule   CHAR (50) DEFAULT ('30 16 * * *') 
                               NOT NULL,
    completeWithLast INTEGER   NOT NULL
                               DEFAULT false
                               CHECK (completeWithLast = 0 OR 
                                      completeWithLast = 1) 
);


-- Table: tasks
CREATE TABLE tasks (
    uniqueId       INTEGER   PRIMARY KEY ASC AUTOINCREMENT
                             NOT NULL
                             UNIQUE,
    name           TEXT      NOT NULL
                             DEFAULT Task,
    parentId       INTEGER   DEFAULT NULL
                             REFERENCES tasks (uniqueId) ON UPDATE CASCADE
                                                         ON DELETE SET DEFAULT,
    status         TEXT      NOT NULL
                             DEFAULT Active
                             CONSTRAINT tasksStatus CHECK (status = "Active" OR 
                                                           status = "Dropped" OR 
                                                           status = "Completed"),
    created        TEXT      DEFAULT (datetime('now', 'utc') ) 
                             NOT NULL
                             CHECK (created = datetime(created) ),
    modified       TEXT      DEFAULT (datetime('now', 'utc') ) 
                             NOT NULL
                             CHECK (modified = datetime(modified) ),
    contextId      INTEGER   DEFAULT NULL
                             REFERENCES contexts (uniqueId) ON DELETE SET DEFAULT
                                                            ON UPDATE CASCADE,
    projectId      INTEGER   DEFAULT NULL
                             REFERENCES projects (uniqueId) ON UPDATE CASCADE
                                                            ON DELETE SET DEFAULT,
    flagged        INTEGER   NOT NULL
                             DEFAULT false
                             CHECK (flagged = 0 OR 
                                    flagged = 1),
    [deferred]     TEXT      CHECK (tasks.[deferred] = datetime(tasks.[deferred]) ),
    due            TEXT      CHECK (tasks.due = datetime(tasks.due) ),
    isRepeating    INT       NOT NULL
                             DEFAULT false
                             CHECK (isRepeating = 0 OR 
                                    isRepeating = 1),
    repeatFrom     TEXT      NOT NULL
                             DEFAULT Due
                             CHECK (repeatFrom = 'Due' OR 
                                    repeatFrom = 'Deferred'),
    repeatSchedule CHAR (50) NOT NULL
                             DEFAULT ('30 16 * * *') 
);


-- Trigger: context_modified
CREATE TRIGGER context_modified
         AFTER UPDATE OF uniqueId,
                         name,
                         parentId,
                         status
            ON contexts
BEGIN
    UPDATE contexts
       SET modified = datetime('now', 'utc') 
     WHERE name = NEW.name;
END;


-- Trigger: folder_modified
CREATE TRIGGER folder_modified
         AFTER UPDATE OF uniqueId,
                         name,
                         parentId,
                         status
            ON folders
BEGIN
    UPDATE folders
       SET modified = datetime('now', 'utc') 
     WHERE name = NEW.name;
END;


-- Trigger: project_modified
CREATE TRIGGER project_modified
         AFTER UPDATE OF uniqueId,
                         name,
                         parentId,
                         contextId,
                         folderId,
                         status,
                         created,
                         due
            ON projects
BEGIN
    UPDATE projects
       SET modified = datetime('now', 'utc') 
     WHERE name = NEW.name;
END;


-- Trigger: task_modified
CREATE TRIGGER task_modified
         AFTER UPDATE OF uniqueId,
                         name,
                         parentId,
                         contextId,
                         projectId,
                         status,
                         created,
                         due,
                         isRepeating
            ON tasks
BEGIN
    UPDATE tasks
       SET modified = datetime('now', 'utc') 
     WHERE name = NEW.name;
END;


COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
