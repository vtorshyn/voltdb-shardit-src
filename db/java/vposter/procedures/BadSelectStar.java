package vposter.procedures;

import org.voltdb.*;

public class BadSelectStar extends VoltProcedure {
	public final SQLStmt selectAll = new SQLStmt(
		"SELECT * FROM messages;");
	
	public VoltTable[] run(String user, String ip)
		throws VoltAbortException
	{
		voltQueueSQL(selectAll);
		return voltExecuteSQL(true);
	}
} 
