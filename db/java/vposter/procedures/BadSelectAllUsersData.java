package vposter.procedures;

import org.voltdb.*;

public class BadSelectAllUsersData extends VoltProcedure {
	public final SQLStmt selectAll = new SQLStmt(
		"SELECT ip, text FROM messages WHERE nick = ?;");
	
	public VoltTable[] run(String[] users)
		throws VoltAbortException
	{
		for (int idx = 0; idx < users.length; ++idx)
		{
		    voltQueueSQL(selectAll, users[idx]);
		}
		return voltExecuteSQL(true);
	}
} 
