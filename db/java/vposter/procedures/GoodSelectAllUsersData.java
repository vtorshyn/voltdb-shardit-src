package vposter.procedures;

import org.voltdb.*;

public class GoodSelectAllUsersData extends VoltProcedure {
	public final SQLStmt selectAll = new SQLStmt(
		"SELECT ip, text FROM messages WHERE nick IN ?;");
	public final byte FAIL = 1;
	public final byte OK = 0;
	
	public VoltTable[] run(String[] users)
		throws VoltAbortException
	{	
		VoltTable[] result = null;
		voltQueueSQL(selectAll, (Object)users);
		try {
		    result = voltExecuteSQL(true);
		} catch (Exception ex) {
		    setAppStatusCode(FAIL);
		    setAppStatusString(ex.getMessage());
		    return null;
		}
		setAppStatusCode(OK);
		setAppStatusString("Good!");
		return result;
	}
} 
