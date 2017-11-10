package rui.configure;

public class ConfigManager {
	private static int DATAGRAM_MAX_SIZE = 65507;
	private static int PORT = 3000;

	private static int MAZE_ROW_COUNT = 10;
	private static int MAZE_COLUMN_COUNT = 10;

	private static String ROBOT_IP = "192.168.56.10";
	private static int ROBOT_PORT = 11999;

	private static ConfigManager instance = new ConfigManager();

	private ConfigManager() {

	}

	public static ConfigManager getInstance() {
		return instance;
	}

	public String getRobotIpAddress() {
		return ROBOT_IP;
	}

	public int getRobotPort() {
		return ROBOT_PORT;
	}

	public int getImageListenPort() {
		return PORT;
	}

	public int getImageMaxSize() {
		return DATAGRAM_MAX_SIZE;
	}

	public int getMazeRowCount() {
		return MAZE_ROW_COUNT;
	}

	public int getMazeColumnCount() {
		return MAZE_COLUMN_COUNT;
	}
}
