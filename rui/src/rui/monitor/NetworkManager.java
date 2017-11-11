package rui.monitor;

import java.io.BufferedOutputStream;
//import java.io.BufferedWriter;
import java.io.IOException;
//import java.io.OutputStreamWriter;
import java.net.Socket;

import rui.Command;
import rui.RUIMain;
import rui.configure.ConfigManager;

public class NetworkManager {
	private ConfigManager configManager = ConfigManager.getInstance();

	private BufferedOutputStream bos = null;
	private Socket socket = null;

	private RUIMain rui;

	public NetworkManager(RUIMain rui) {
		this.rui = rui;
	}

	public void connect() {
		try {
			String ip = configManager.getRobotIp();
			int port = configManager.getRobotPort();

			rui.appendLogMessage(String.format("%s / IP : %s / PORT : %s", "Trying to connect the remote robot ", ip, port));

			disconnect();

			socket = new Socket(ip, port);
			bos = new BufferedOutputStream(socket.getOutputStream());

			new Thread(new MonitoringReceiver(this.rui, socket)).start();

			rui.appendLogMessage("Connection established.");
			rui.setNetworkStatus(true);
		} catch (Exception e) {
			rui.appendLogMessage("Connection failed. " + e.getMessage());
			rui.setNetworkStatus(false);
		}
	}

	public void disconnect() {
		rui.setNetworkStatus(false);

		if (socket != null)
			try {
				socket.close();
			} catch (IOException e) {
			} finally {
				socket = null;
			}

		if (bos != null)
			try {
				bos.close();
			} catch (Exception e) {
			} finally {
				bos = null;
			}
	}

	public boolean isConnected() {
		return socket != null && socket.isConnected();
	}

	public void sendCommand(Command command) {
		if (!isConnected())
			return;

		try {
			bos.write(command.getMessageBytes());
			bos.flush();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
