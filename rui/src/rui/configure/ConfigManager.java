package rui.configure;

import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Properties;

import rui.utils.Utils;

public class ConfigManager {
	File configFile = new File(System.getProperty("user.home") + File.separator + "robot_config.properties");

	private int cameraDatagramMaxSize;
	private int cameraListenport;

	private int mazeRowCount;
	private int mazeColumnCount;

	private String ruiIp;

	private String robotIp;
	private int robotPort;

	private static ConfigManager instance = new ConfigManager();

	private ConfigManager() {
		try {
			this.load();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static ConfigManager getInstance() {
		return instance;
	}

	public void load() throws IOException {
		FileReader reader = null;

		try {
			if (!configFile.exists())
				configFile.createNewFile();

			reader = new FileReader(configFile);

			Properties props = new Properties();
			props.load(reader);

			String CAMERA_DATAGRAM_MAX_SIZE = props.getProperty(IConfigKeys.KEY_CAMERA_DATAGRAM_MAX_SIZE, IConfigKeys.CAMERA_DATAGRAM_MAX_SIZE + "");
			this.cameraDatagramMaxSize = Integer.parseInt(CAMERA_DATAGRAM_MAX_SIZE);

			String CAMERA_LISTEN_PORT = props.getProperty(IConfigKeys.KEY_CAMERA_LISTEN_PORT, IConfigKeys.CAMERA_LISTEN_PORT + "");
			this.cameraListenport = Integer.parseInt(CAMERA_LISTEN_PORT);

			String MAZE_ROW_COUNT = props.getProperty(IConfigKeys.KEY_MAZE_ROW_COUNT, IConfigKeys.MAZE_ROW_COUNT + "");
			this.mazeRowCount = Integer.parseInt(MAZE_ROW_COUNT);

			String MAZE_COLUMN_COUNT = props.getProperty(IConfigKeys.KEY_MAZE_COLUMN_COUNT, IConfigKeys.MAZE_COLUMN_COUNT + "");
			this.mazeColumnCount = Integer.parseInt(MAZE_COLUMN_COUNT);

			this.robotIp = props.getProperty(IConfigKeys.KEY_ROBOT_IP, IConfigKeys.ROBOT_IP);

			String ROBOT_PORT = props.getProperty(IConfigKeys.KEY_ROBOT_PORT, IConfigKeys.ROBOT_PORT + "");
			this.robotPort = Integer.parseInt(ROBOT_PORT);

			this.ruiIp = props.getProperty(IConfigKeys.KEY_RUI_IP);
			if (Utils.isEmpty(this.ruiIp)) {
				this.ruiIp = Utils.getLocalIPAddress();
			}
		} finally {
			if (reader != null)
				try {
					reader.close();
				} catch (Exception e) {
				}
		}
	}

	public void persist() throws IOException {
		FileWriter writer = null;

		try {
			writer = new FileWriter(configFile);

			Properties props = new Properties();

			props.setProperty(IConfigKeys.KEY_CAMERA_DATAGRAM_MAX_SIZE, this.cameraDatagramMaxSize + "");
			props.setProperty(IConfigKeys.KEY_CAMERA_LISTEN_PORT, this.cameraListenport + "");
			props.setProperty(IConfigKeys.KEY_MAZE_ROW_COUNT, this.mazeRowCount + "");
			props.setProperty(IConfigKeys.KEY_MAZE_COLUMN_COUNT, this.mazeColumnCount + "");
			props.setProperty(IConfigKeys.KEY_ROBOT_IP, this.robotIp);
			props.setProperty(IConfigKeys.KEY_ROBOT_PORT, this.robotPort + "");
			props.setProperty(IConfigKeys.KEY_RUI_IP, this.ruiIp);

			props.store(writer, "RUI Settings");
		} finally {
			if (writer != null)
				try {
					writer.close();
				} catch (Exception e) {
				}
		}

	}

	public int getCameraDatagramMaxSize() {
		return cameraDatagramMaxSize;
	}

	public void setCameraDatagramMaxSize(int cameraDatagramMaxSize) {
		this.cameraDatagramMaxSize = cameraDatagramMaxSize;
	}

	public int getCameraListenport() {
		return cameraListenport;
	}

	public void setCameraListenport(int cameraListenport) {
		this.cameraListenport = cameraListenport;
	}

	public int getMazeRowCount() {
		return mazeRowCount;
	}

	public void setMazeRowCount(int mazeRowCount) {
		this.mazeRowCount = mazeRowCount;
	}

	public int getMazeColumnCount() {
		return mazeColumnCount;
	}

	public void setMazeColumnCount(int mazeColumnCount) {
		this.mazeColumnCount = mazeColumnCount;
	}

	public String getRobotIp() {
		return robotIp;
	}

	public void setRobotIp(String robotIp) {
		this.robotIp = robotIp;
	}

	public int getRobotPort() {
		return robotPort;
	}

	public void setRobotPort(int robotPort) {
		this.robotPort = robotPort;
	}

	public String getConfigFilePath() {
		return this.configFile.getAbsolutePath();
	}

	public String getRuiIp() {
		return ruiIp;
	}

	public void setRuiIp(String ruiIp) {
		this.ruiIp = ruiIp;
	}
}
