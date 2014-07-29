package vposter.procedures;

import org.voltdb.*;

public class GetHistory extends VoltProcedure {
	public final SQLStmt getHistory = new SQLStmt(
		"SELECT uid,ip, nick, text FROM messages ORDER by uid DESC LIMIT ?;");

	public VoltTable[] run(short limit)
		throws VoltAbortException
	{
		if (limit < 1)
		{
		    throw new VoltAbortException();
		}
		voltQueueSQL(getHistory, limit);
		return voltExecuteSQL();
	}
} 
