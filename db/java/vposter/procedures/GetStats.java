package vposter.procedures;

import org.voltdb.*;

public class GetStats extends VoltProcedure {
	public final SQLStmt getUserStats = new SQLStmt(
		"SELECT count(text) messages_by_uid FROM messages WHERE nick LIKE ?;");
	
	public final SQLStmt getIpStats = new SQLStmt(
		"SELECT count(text) messages_by_ip FROM messages WHERE ip LIKE ?;");

	public VoltTable[] run(String user, String ip)
		throws VoltAbortException
	{
		VoltTable[] result = new VoltTable[2];
		if (null == user)
		{
		    throw new VoltAbortException();
		}
		voltQueueSQL(getUserStats, user);
		VoltTable[] ustat = voltExecuteSQL();
		if (null == ip) 
		{
			return ustat;
		}
		voltQueueSQL(getIpStats, ip);
		VoltTable[] ipstat = voltExecuteSQL();
		result[0] = ustat[0];
		result[1] = ipstat[0];
		return result;
	}
} 
