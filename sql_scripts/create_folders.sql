PRAGMA foreign_keys = ON;

/******************************************************************************
 * CREATE folders TABLE
 ******************************************************************************/
CREATE TABLE folders (
    uniqueId         INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    name             TEXT    NOT NULL,
    parentId         INTEGER DEFAULT NULL REFERENCES folders(uniqueId)
						ON UPDATE CASCADE
						ON DELETE SET DEFAULT,
	status			 TEXT    NOT NULL DEFAULT "Active",
    created          TEXT    NOT NULL DEFAULT (datetime('sys_clk_now', 'utc')),
    modified         TEXT    NOT NULL DEFAULT (datetime('sys_clk_now', 'utc'))
);

/******************************************************************************
 * NAME CHANGE TRIGGER
 ******************************************************************************/
CREATE TRIGGER folder_modified
    AFTER UPDATE ON folders
        WHEN old.name <> new.name
    	OR old.parentId <> new.parentId
    	OR old.status <> new.status
BEGIN
    UPDATE folders
        SET modified = datetime('sys_clk_now','utc')
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

