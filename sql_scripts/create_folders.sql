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
	status			 TEXT    NOT NULL DEFAULT "Active",
    created          TEXT    DEFAULT (datetime('sys_clk_now', 'utc')),
    modified         TEXT    DEFAULT (datetime('sys_clk_now', 'utc'))
);

/******************************************************************************
 * NAME CHANGE TRIGGER
 ******************************************************************************/
CREATE TRIGGER folder_modified
    AFTER UPDATE ON folders
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

