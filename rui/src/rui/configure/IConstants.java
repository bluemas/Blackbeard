package rui.configure;

public interface IConstants {
	public static final String TYPE = "type";
	public static final String PAYLOAD = "payload";
	public static final String MM = " mm";
	public static final String SECOND = " s";

	public static final String SAVE_SUCCESS = "Configuration Saving completed.\n\nFile Path = ";
	public static final String SAVE_ERROR = "Error occurred while saving.\nPlease check the error message in Message Console Tab";
	public static final String MISSION_COMPLETED = "Solving Maze is completed.";
	
	public static final int SOCKET_TIMEOUT = 5000;
	public static final int RETRY_CNT = 60;
}
