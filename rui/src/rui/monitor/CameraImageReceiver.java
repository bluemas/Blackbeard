package rui.monitor;

import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

import javax.imageio.ImageIO;

import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.graphics.ImageData;

import rui.RUIMain;
import rui.configure.ConfigManager;
import rui.utils.Utils;

public class CameraImageReceiver implements Runnable {
	private ConfigManager configManager = ConfigManager.getInstance();
	private DatagramSocket socket;
	private RUIMain rui;

	public CameraImageReceiver(RUIMain rui) {
		this.rui = rui;
	}

	public void run() {
		try {
			this.socket = new DatagramSocket(configManager.getCameraListenport());

			/* Setup byte array to store data received */
			byte[] buffer = new byte[configManager.getCameraDatagramMaxSize()];

			/* Receiving loop */
			while (!this.socket.isClosed()) {
				try {
					/* Receive a UDP packet */
					DatagramPacket dp = new DatagramPacket(buffer, buffer.length);
					socket.receive(dp);

					byte[] data = dp.getData();

					BufferedImage bi = ImageIO.read(new ByteArrayInputStream(data));
					if (bi == null)
						continue;

					ImageData img = Utils.convertToSWT(bi);
					bi.flush();
					bi = null;

					RUIMain.display.asyncExec(new Runnable() {
						public void run() {
							if (!rui.getShell().isDisposed()) {	
								rui.getCameraImageLabel().setImage(new Image(RUIMain.display, img));
							}
						}
					});
				} catch (Exception ex) {
				}
			}
		} catch (IOException e) {
		}
	}

	public void close() {
		if (socket != null) {
			try {
				socket.close();
			} catch (Exception e) {
			}
		}
	}
}
