PRAGMA foreign_keys = ON;

/******************************************************************************
 * CREATE tasks TABLE
 ******************************************************************************/
CREATE TABLE tasks (
    uniqueId         INTEGER PRIMARY KEY AUTOINCREMENT,
    name             TEXT    NOT NULL DEFAULT "Task",
    parentId         INTEGER DEFAULT NULL REFERENCES tasks(uniqueId)
						ON UPDATE CASCADE
						ON DELETE SET DEFAULT,
    contextId        INTEGER DEFAULT NULL REFERENCES contexts(uniqueId)
						ON UPDATE CASCADE
						ON DELETE SET DEFAULT,
    projectId        INTEGER DEFAULT NULL REFERENCES projects(uniqueId)
						ON UPDATE CASCADE
						ON DELETE SET DEFAULT,
	status			 TEXT    NOT NULL DEFAULT "Active",
	deferred         TEXT,
    due              TEXT,
    notes			 TEXT,
    created          TEXT    DEFAULT (datetime('sys_clk_now', 'utc')),
    modified         TEXT    DEFAULT (datetime('sys_clk_now', 'utc'))
);

/******************************************************************************
 * NAME CHANGE TRIGGER
 ******************************************************************************/
CREATE TRIGGER task_modified
    AFTER UPDATE ON tasks
        WHEN old.name <> new.name
    	OR old.parentId <> new.parentId
    	OR old.contextId <> new.contextId
    	OR old.projectId <> new.projectId
    	OR old.status <> new.status
    	OR old.deferred <> new.deferred
    	OR old.due <> new.due
    	OR old.notes <> new.notes
BEGIN
    UPDATE tasks
        SET modified = datetime('sys_clk_now','utc')
        WHERE name = NEW.name;
END;

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

INSERT INTO tasks(name, contextId)
VALUES
    ('Take out trash', 9),
    ('Buy eggs',       7),
    ('Wash truck',     9),
    ('Cut grass',      9),
    ('Do laundry',     9),
    ('Call Mami',      5),
    ('Comb hair',      9);
    
INSERT INTO tasks(name, contextId, parentId)
VALUES
	('Weed eat', 9, 4)






