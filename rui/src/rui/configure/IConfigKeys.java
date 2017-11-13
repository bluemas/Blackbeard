package rui.configure;

public interface IConfigKeys {
	public static final String KEY_CAMERA_DATAGRAM_MAX_SIZE = "DATAGRAM_MAX_SIZE";
	public static final String KEY_CAMERA_LISTEN_PORT = "CAMERA_LISTEN_PORT";
	public static final String KEY_MAZE_ROW_COUNT = "MAZE_ROW_COUNT";
	public static final String KEY_MAZE_COLUMN_COUNT = "MAZE_COLUMN_COUNT";
	public static final String KEY_ROBOT_IP = "ROBOT_IP";
	public static final String KEY_ROBOT_PORT = "ROBOT_PORT";
	public static final String KEY_RUI_IP = "RUI_IP";
	
	public static final int CAMERA_DATAGRAM_MAX_SIZE = 65507;
	public static final int CAMERA_LISTEN_PORT = 3000;
	public static final int MAZE_ROW_COUNT = 10;
	public static final int MAZE_COLUMN_COUNT = 10;
	public static final String ROBOT_IP = "192.168.56.10";
	public static final int ROBOT_PORT = 11999;
}
