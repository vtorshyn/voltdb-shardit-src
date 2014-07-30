-- Simple schema for Chat 
-- It stores IP, NICK and textual message
-- Please note the size of each column
CREATE TABLE messages (
    uid BIGINT NOT NULL,
    nick VARCHAR(64) NOT NULL,
    ip VARCHAR(16) NOT NULL,
    text VARCHAR(1024)
);

-- Creating compound index 
CREATE INDEX messages_idx ON messages (nick, ip);
-- Let know for voltdb that our table should be partitioned
PARTITION TABLE messages ON COLUMN nick;

-- Creating procedures from compiled (!!!) java classes
CREATE PROCEDURE FROM CLASS vposter.procedures.GetHistory;
CREATE PROCEDURE FROM CLASS vposter.procedures.AddMessage;
CREATE PROCEDURE FROM CLASS vposter.procedures.GetStats;
CREATE PROCEDURE FROM CLASS vposter.procedures.BadSelectStar;
CREATE PROCEDURE FROM CLASS vposter.procedures.BadSelectAllUsersData;
CREATE PROCEDURE FROM CLASS vposter.procedures.GoodSelectAllUsersData;

-- Tell for voltdb that the following procedures are partitioned by column nick
PARTITION PROCEDURE AddMessage ON TABLE messages COLUMN nick;
PARTITION PROCEDURE GetStats ON TABLE messages COLUMN nick;
