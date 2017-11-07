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
	private DatagramSocket clientsocket;
	private RUIMain rui;

	public CameraImageReceiver(RUIMain rui) {
		this.rui = rui;
	}

	public void run() {
		try {
			this.clientsocket = new DatagramSocket(configManager.getImageListenPort());

			/* Setup byte array to store data received */
			byte[] buffer = new byte[configManager.getImageMaxSize()];

			/* Receiving loop */
			while (!this.clientsocket.isClosed()) {
				/* Receive a UDP packet */
				DatagramPacket dp = new DatagramPacket(buffer, buffer.length);
				clientsocket.receive(dp);

				byte[] data = dp.getData();
				
				BufferedImage bi = ImageIO.read(new ByteArrayInputStream(data));
				ImageData img = Utils.convertToSWT(bi);
				bi.flush();
				bi = null;
				
				RUIMain.display.asyncExec(new Runnable() {
					public void run() {
						Image image = new Image(null, img);
						rui.getCameraImageLabel().setImage(image);
						image.dispose();
					}
				});
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void close() {
		if (clientsocket != null) {
			try {
				clientsocket.close();
			} catch (Exception e) {
			}
		}
	}
}
