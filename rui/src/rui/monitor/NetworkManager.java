package rui.monitor;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.Socket;

import rui.Command;
import rui.RUIMain;
import rui.configure.ConfigManager;

public class NetworkManager {
	private ConfigManager configManager = ConfigManager.getInstance();

	private BufferedWriter bw = null;
	private Socket socket = null;

	RUIMain rui;

	public NetworkManager(RUIMain rui) {
		this.rui = rui;
	}

	public void connect() {
		try {
			String ip = configManager.getRobotIpAddress();
			int port = configManager.getRobotPort();
			
			rui.appendLogMessage(String.format("%s / IP : %s / PORT : %s", "Trying to connect the remote robot ", ip, port));

			disconnect();

			socket = new Socket(ip, port);
			bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));

			new Thread(new MonitoringReceiver(this.rui, socket)).start();

			rui.appendLogMessage("Connection established.");
		} catch (Exception e) {
			rui.appendLogMessage("Connection failed.");
			rui.appendLogMessage(e.getMessage());

			e.printStackTrace();
		}
	}

	public void disconnect() {
		if (socket != null)
			try {
				socket.close();
			} catch (IOException e) {
			} finally {
				socket = null;
			}

		if (bw != null)
			try {
				bw.close();
			} catch (Exception e) {
			} finally {
				bw = null;
			}
	}

	public void sendCommand(Command command) {
		try {
			bw.write(command.getMessage());
			bw.flush();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
