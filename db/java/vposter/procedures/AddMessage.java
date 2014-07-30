package vposter.procedures;

import org.voltdb.*;

public class AddMessage extends VoltProcedure {
	public final SQLStmt addNew = new SQLStmt(
		"INSERT INTO messages VALUES(?,?,?,?);");

	public VoltTable[] run(String user, String ip, String msg)
		throws VoltAbortException
	{
		long uid = getUniqueId();
		voltQueueSQL(addNew, uid, user, ip, msg);
		return voltExecuteSQL(true);
	}
} 
