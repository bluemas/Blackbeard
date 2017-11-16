package rui.monitor;

import java.io.BufferedOutputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;

import rui.Command;
import rui.RUIMain;
import rui.configure.ConfigManager;
import rui.configure.IConstants;

public class NetworkManager {
	private ConfigManager configManager = ConfigManager.getInstance();

	private BufferedOutputStream bos = null;
	private Socket socket = null;

	private NetworkWatchdog watchdog = null;
	private RUIMain rui;

	public NetworkManager(RUIMain rui) {
		this.rui = rui;
	}

	public boolean connect() {
		try {
			String ip = configManager.getRobotIp();
			int port = configManager.getRobotPort();

			rui.appendLogMessage(String.format("%s / IP : %s / PORT : %s", "Trying to connect the remote robot ", ip, port));

			disconnect();

			socket = new Socket();
			socket.connect(new InetSocketAddress(ip, port), IConstants.SOCKET_TIMEOUT);

			bos = new BufferedOutputStream(socket.getOutputStream());

			new Thread(new MonitoringReceiver(this.rui, socket)).start();

			rui.appendLogMessage("Connection established.");
			rui.setNetworkStatus(true);

			startNetworkWatchdog();

			return true;
		} catch (Exception e) {
			rui.appendLogMessage("Connection failed. " + e.getMessage());
			rui.setNetworkStatus(false);

			return false;
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

	private boolean isConnected() {
		return socket != null && socket.isConnected() && !socket.isClosed();
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

	public void startNetworkWatchdog() {
		if (watchdog != null)
			watchdog.stop();

		watchdog = new NetworkWatchdog();
		new Thread(watchdog).start();
	}

	public void stopNetworkWatchdog() {
		if (watchdog != null)
			watchdog.stop();
	}

	class NetworkWatchdog implements Runnable {
		private int retryCnt = IConstants.RETRY_CNT;
		private boolean isRunning = true;

		@Override
		public void run() {
			while (isRunning && !rui.getShell().isDisposed()) {
				try {
					if (!isConnected()) {
						rui.notify(new Command(7, "S"));

						if (connect()) {
							retryCnt = IConstants.RETRY_CNT;
						} else if (--retryCnt == 0) {
							break;
						}
					}

					Thread.sleep(1000);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}

		public void stop() {
			isRunning = false;
		}
	}
}
