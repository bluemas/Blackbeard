package com.lg.cmu.rui.comm;

import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

import javax.annotation.PostConstruct;
import javax.imageio.ImageIO;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;

@Component
public class ImageUdpReciever implements ImageReceiver {

	private static final Logger LOGGER = LoggerFactory.getLogger(ImageUdpReciever.class);

	/*
	 * The absolute maximum datagram packet size is 65507, The maximum IP packet
	 * size of 65535 minus 20 bytes for the IP header and 8 bytes for the UDP
	 * header.
	 */
	private static int DATAGRAM_MAX_SIZE = 65507;

	/* Default values */
	public static int PORT = 3000;

	private boolean isRunning;

	public ImageUdpReciever() {
		this.init();
	}

	/* (non-Javadoc)
	 * @see com.lg.cmu.rui.comm.ImageReceiver#init()
	 */
	@Override
	@PostConstruct
	public void init() {
		this.isRunning = true;
	}

	/* (non-Javadoc)
	 * @see com.lg.cmu.rui.comm.ImageReceiver#start()
	 */
	@Override
	public void start() {
		receive();
	}

	/* (non-Javadoc)
	 * @see com.lg.cmu.rui.comm.ImageReceiver#stop()
	 */
	@Override
	public void stop() {

	}

	private void receive() {
		DatagramSocket clientsocket = null;

		try {
			clientsocket = new DatagramSocket(PORT);

			/* Setup byte array to store data received */
			byte[] buffer = new byte[DATAGRAM_MAX_SIZE];

			/* Receiving loop */
			while (isRunning) {
				/* Receive a UDP packet */
				DatagramPacket dp = new DatagramPacket(buffer, buffer.length);
				clientsocket.receive(dp);
				byte[] data = dp.getData();

				LOGGER.debug("Image size : {} bytes", data.length);

				BufferedImage image = ImageIO.read(new ByteArrayInputStream(data));

				// TODO send Image Render or enqeue
			}
		} catch (IOException e) {

		} finally {
			if (clientsocket != null && !clientsocket.isClosed()) {
				clientsocket.close();
			}
		}
	}

}
