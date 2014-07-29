CREATE TABLE messages (
    uid BIGINT NOT NULL,
    nick VARCHAR(64) NOT NULL,
    ip VARCHAR(16) NOT NULL,
    text VARCHAR(1024)
);

CREATE INDEX messages_idx ON messages (nick, ip);
PARTITION TABLE messages ON COLUMN nick;

CREATE PROCEDURE FROM CLASS vposter.procedures.GetHistory;
CREATE PROCEDURE FROM CLASS vposter.procedures.AddMessage;
CREATE PROCEDURE FROM CLASS vposter.procedures.GetStats;

PARTITION PROCEDURE AddMessage ON TABLE messages COLUMN nick;