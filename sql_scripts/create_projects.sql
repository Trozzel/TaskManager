PRAGMA foreign_keys = ON;

/******************************************************************************
 * CREATE projects TABLE
 ******************************************************************************/
CREATE TABLE projects (
    uniqueId         INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    name             TEXT    NOT NULL,
    parentId         INTEGER DEFAULT NULL REFERENCES projects(uniqueId)
						ON UPDATE CASCADE
						ON DELETE SET DEFAULT,
    contextId        INTEGER DEFAULT NULL REFERENCES contexts(uniqueId)
						ON UPDATE CASCADE
						ON DELETE SET DEFAULT,
	status			 TEXT    NOT NULL DEFAULT "Active",
    deferred         TEXT,
    due              TEXT,
	notes			 TEXT,
	type			 TEXT 	 NOT NULL DEFAULT "Parallel",
	completeWithLast INTEGER NOT NULL DEFAULT 0,
	repeating        INTEGER NOT NULL DEFAULT 0, /* 0 == False; >0 == True */
	repeatFrom       TEXT    NOT NULL DEFAULT "due",
	repeatEveryFile  TEXT,   /* Contains a path to a JSON file containing repeat parameters */
    created          TEXT    NOT NULL DEFAULT (datetime('sys_clk_now', 'utc')),
    modified         TEXT    NOT NULL DEFAULT (datetime('sys_clk_now', 'utc'))
);

/******************************************************************************
 * NAME CHANGE TRIGGER
 ******************************************************************************/
CREATE TRIGGER project_modified
    AFTER UPDATE ON projects
    WHEN old.name <> new.name
    	OR old.parentId <> new.parentId
    	OR old.status <> new.status
    	OR old.deferred <> new.deferred
    	OR old.due <> new.due
    	OR old.notes <> new.notes
    	OR old.type <> new.type
    	OR old.completeWithLast <> new.completeWithLast
    	OR old.repeating <> new.repeating
    	OR old.repeatEveryFile <> new.repeatEveryFile
BEGIN
    UPDATE projects
        SET modified = datetime('sys_clk_now','utc')
        WHERE name = NEW.name;
END;

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

INSERT INTO projects(name)
VALUES
    ('Get truck fixed'),
    ('Go on date'),
    ('George Birthday'),
    ('Clean AC'),
    ('Serve in CC');
