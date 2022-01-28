PRAGMA foreign_keys = ON;

/******************************************************************************
 * CREATE folders TABLE
 ******************************************************************************/
CREATE TABLE folders (
    uniqueId         INTEGER PRIMARY KEY,
    name             TEXT    NOT NULL,
    parentId         INTEGER DEFAULT NULL REFERENCES folders(uniqueId)
						ON UPDATE CASCADE
						ON DELETE SET DEFAULT,
    created          TEXT    DEFAULT (datetime('now', 'utc')),
    modified          TEXT    DEFAULT (datetime('now', 'utc'))
);

/******************************************************************************
 * NAME CHANGE TRIGGER
 ******************************************************************************/
CREATE TRIGGER folder_modified
    AFTER UPDATE ON folders
BEGIN
    UPDATE folders
        SET modified = datetime('now','utc')
        WHERE name = NEW.name;
END;

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

INSERT INTO folders(name)
VALUES
    ('Home'),
    ('Church'),
    ('Work');

