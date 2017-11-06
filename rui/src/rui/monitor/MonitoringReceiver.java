package rui.monitor;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

import rui.RUIMain;

public class MonitoringReceiver implements Runnable {
	private BufferedReader br;
	private RUIMain rui;

	public MonitoringReceiver(RUIMain rui, Socket socket) throws IOException {
		this.br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
		this.rui = rui;
	}

	@Override
	public void run() {
		String message;

		try {
			while ((message = br.readLine()) != null) {
				rui.notify(message);
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if (br != null)
				try {
					br.close();
				} catch (Exception e) {
					e.printStackTrace();
				}
		}
	}
}