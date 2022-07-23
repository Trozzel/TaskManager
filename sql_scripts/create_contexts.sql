PRAGMA foreign_keys = ON;

/******************************************************************************
 * CREATE contexts TABLE
 ******************************************************************************/
CREATE TABLE contexts (
    uniqueId         INTEGER PRIMARY KEY,
    name             TEXT    NOT NULL,
    parentId         INTEGER DEFAULT NULL REFERENCES contexts(uniqueId)
						 ON	UPDATE CASCADE
						 ON	DELETE SET DEFAULT,
	status			 TEXT    NOT NULL DEFAULT "Active",
    created          TEXT    DEFAULT (datetime('sys_clk_now', 'utc')),
    modified         TEXT    DEFAULT (datetime('sys_clk_now', 'utc'))
);

/******************************************************************************
 * NAME CHANGE TRIGGER
 ******************************************************************************/
CREATE TRIGGER context_modified
    AFTER UPDATE ON contexts
BEGIN
    UPDATE contexts
        SET modified = datetime('sys_clk_now','utc')
		WHERE name = NEW.name;
END;

	/******************************************************************************
	 * PARENT CHANGE TRIGGER
	 ******************************************************************************/
	/*
	CREATE TRIGGER context_parentId_is_changed
		AFTER UPDATE ON contexts
			WHEN NEW.parentId IS NOT OLD.parentId

	BEGIN
		UPDATE contexts
			SET modified = datetime('sys_clk_now','utc')
			WHERE parentId = NEW.parentId;
	END;
	*/

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

INSERT INTO contexts (name)
    VALUES('People');

INSERT INTO contexts (name, parentId)
VALUES
    ('George Isaac', 1),
    ('Jim',      1),
    ('Michael',  1);

INSERT INTO contexts (name)
VALUES
    ('Phone'),
    ('Computer'),
    ('Shopping'),
    ('Errand'),
    ('Home');
