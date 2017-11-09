package rui;

import java.io.ByteArrayOutputStream;
import java.nio.ByteBuffer;

import rui.utils.Utils;

public class Command {
	private int type;
	private String payload;

	public Command(int type, String payload) {
		this.type = type;
		this.payload = payload;
	}

	public int getType() {
		return type;
	}

	public void setType(int type) {
		this.type = type;
	}

	public String getPayload() {
		return payload;
	}

	public void setPayload(String payload) {
		this.payload = payload;
	}

	public byte[] getMessageBytes() {
		byte[] result = new byte[0];
	
		try (ByteArrayOutputStream byteos = new ByteArrayOutputStream()) {
			boolean hasPayload = !Utils.isEmpty(payload);
			int payloadSize = hasPayload ? payload.length() : 0;
			
			ByteBuffer bb = ByteBuffer.allocate(4);
			bb.putInt(payloadSize);

			byteos.write(type);
			byteos.write(bb.array());

			if (hasPayload) {
				byteos.write(payload.getBytes());
			}
			
			result = byteos.toByteArray();
		} catch (Exception e) {
			e.printStackTrace();
		}

		return result;
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();

		sb.append("{").append("type=" + type).append(", ");
		sb.append("payload=" + payload);
		sb.append("}");

		return sb.toString();
	}
}
