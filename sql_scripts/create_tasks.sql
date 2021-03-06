PRAGMA foreign_keys = ON;

/******************************************************************************
 * CREATE tasks TABLE
 ******************************************************************************/
CREATE TABLE tasks (
    uniqueId         INTEGER PRIMARY KEY,
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
    created          TEXT    DEFAULT (datetime('sys_clk_now', 'utc')),
    modified         TEXT    DEFAULT (datetime('sys_clk_now', 'utc')),
    deferred         TEXT,
    due              TEXT
);

/******************************************************************************
 * NAME CHANGE TRIGGER
 ******************************************************************************/
CREATE TRIGGER task_modified
    AFTER UPDATE ON tasks
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

