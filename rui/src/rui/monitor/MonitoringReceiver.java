package rui.monitor;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.net.Socket;
import java.nio.ByteBuffer;

import rui.Command;
import rui.RUIMain;

public class MonitoringReceiver implements Runnable {
	private BufferedInputStream bis;
	private RUIMain rui;

	public MonitoringReceiver(RUIMain rui, Socket socket) throws IOException {
		this.bis = new BufferedInputStream(socket.getInputStream());
		this.rui = rui;
	}

	@Override
	public void run() {
		try {
			byte[] typeByte = new byte[1];

			while (bis.read(typeByte) != -1) {
				int type = new Integer(typeByte[0]);

				byte[] payloadSizeByte = new byte[4];
				bis.read(payloadSizeByte);
				int payloadSize = ByteBuffer.wrap(payloadSizeByte).getInt();

				byte[] payloadByte = new byte[payloadSize];
				bis.read(payloadByte);
				String payload = new String(payloadByte);

				rui.notify(new Command(type, payload));
			}
		} catch (Exception e) {
			// rui.appendLogMessage(Utils.getStackTrace(e));
		} finally {
			if (bis != null)
				try {
					bis.close();
				} catch (Exception e) {
				}
		}
	}
}