PRAGMA foreign_keys = ON;

/******************************************************************************
 * CREATE projects TABLE
 ******************************************************************************/
CREATE TABLE projects (
    uniqueId         INTEGER PRIMARY KEY,
    name             TEXT    NOT NULL,
    parentId         INTEGER DEFAULT NULL REFERENCES projects(uniqueId)
						ON UPDATE CASCADE
						ON DELETE SET DEFAULT,
    contextId        INTEGER DEFAULT NULL REFERENCES contexts(uniqueId)
						ON UPDATE CASCADE
						ON DELETE SET DEFAULT,
    folderId         INTEGER DEFAULT NULL REFERENCES folders(uniqueId)
						ON UPDATE CASCADE
						ON DELETE SET DEFAULT,
    created          TEXT    DEFAULT (datetime('now', 'utc')),
    modified          TEXT    DEFAULT (datetime('now', 'utc')),
    deferred         TEXT,
    due              TEXT
);

/******************************************************************************
 * NAME CHANGE TRIGGER
 ******************************************************************************/
CREATE TRIGGER project_modified
    AFTER UPDATE ON projects
BEGIN
    UPDATE projects
        SET modified = datetime('now','utc')
        WHERE name = NEW.name;
END;

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

INSERT INTO projects(name, folderId)
VALUES
    ('Get truck fixed', 1),
    ('Go on date',      1),
    ('George Birthday', 1),
    ('Clean AC',        1),
    ('Serve in CC',     2);
