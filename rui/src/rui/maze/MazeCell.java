package rui.maze;

import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.GC;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.wb.swt.SWTResourceManager;

import rui.RUIMain;
import rui.utils.Utils;

public class MazeCell {
	private int column = -1;
	private int row = -1;

	private boolean visited = false;
	private boolean isCurrentPosition = false;

	private boolean[] walls = new boolean[4];
	private String[] signs = new String[4];

	private boolean isStartPosition = false;
	private boolean isEndPosition = false;
	private boolean hasRedDot = false;

	private int LINE_WIDTH = 8;
	private int LINE_WIDTH_2 = LINE_WIDTH / 2;
	
	public MazeCell(int row, int column) {
		this.column = column;
		this.row = row;
	}

	public void draw(GC gc, int x, int y, int width, int height) {
		if (!visited)
			return;

		int s = Math.min(width, height) / 4;
		int xoffset = width / 2 - s / 2;
		int yoffset = height / 2 - s / 2;

		if (isStartPosition || isEndPosition) {
			gc.setBackground(SWTResourceManager.getColor(isStartPosition ? SWT.COLOR_BLUE : SWT.COLOR_DARK_GREEN));
			gc.fillRectangle(x + LINE_WIDTH_2, y + LINE_WIDTH_2, width - LINE_WIDTH, height - LINE_WIDTH);
		} else {
			gc.setBackground(SWTResourceManager.getColor(SWT.COLOR_WHITE));
			gc.fillRectangle(x + LINE_WIDTH_2, y + LINE_WIDTH_2, width - LINE_WIDTH, height - LINE_WIDTH);
		}

		if (hasRedDot) {
			gc.setBackground(SWTResourceManager.getColor(SWT.COLOR_RED));
			gc.fillOval(x + xoffset, y + yoffset, s, s);
		}

		if (isCurrentPosition) {

		}

		gc.setLineWidth(LINE_WIDTH);
		gc.setBackground(SWTResourceManager.getColor(SWT.COLOR_BLACK));

		if (walls[0]) { // North
			gc.drawLine(x, y, x + width, y);

			if (!Utils.isEmpty(signs[0])) {
				Image img = getSignImage(signs[0]);
				Rectangle rec = img.getBounds();
				gc.drawImage(img, 0, 0, rec.width, rec.height, x + xoffset, y + LINE_WIDTH_2, width / 4, height / 4);
			}
		}

		if (walls[1]) { // East
			gc.drawLine(x + width, y, x + width, y + height);

			if (!Utils.isEmpty(signs[1])) {
				Image img = getSignImage(signs[1]);
				Rectangle rec = img.getBounds();
				gc.drawImage(img, 0, 0, rec.width, rec.height, x + width - s - LINE_WIDTH_2, y + yoffset, width / 4, height / 4);
			}
		}

		if (walls[2]) { // South
			gc.drawLine(x, y + height, x + width, y + height);

			if (!Utils.isEmpty(signs[2])) {
				Image img = getSignImage(signs[2]);
				Rectangle rec = img.getBounds();
				gc.drawImage(img, 0, 0, rec.width, rec.height, x + xoffset, y + height - s - LINE_WIDTH_2, width / 4, height / 4);
			}
		}

		if (walls[3]) { // West
			gc.drawLine(x, y, x, y + height);

			if (!Utils.isEmpty(signs[3])) {
				Image img = getSignImage(signs[3]);
				Rectangle rec = img.getBounds();
				gc.drawImage(img, 0, 0, rec.width, rec.height, x + LINE_WIDTH_2, y + yoffset, width / 4, height / 4);
			}
		}
	}

	private Image getSignImage(String sign) {
		return SWTResourceManager.getImage(RUIMain.class, "/resources/arrow" + sign.toUpperCase() + "_print.jpg");
	}

	public int getColumn() {
		return column;
	}

	public void setColumn(int column) {
		this.column = column;
	}

	public int getRow() {
		return row;
	}

	public void setRow(int row) {
		this.row = row;
	}

	public boolean isVisited() {
		return visited;
	}

	public void setVisited(boolean visited) {
		this.visited = visited;
	}

	public boolean isCurrentPosition() {
		return isCurrentPosition;
	}

	public void setCurrentPosition(boolean isCurrentPosition) {
		this.isCurrentPosition = isCurrentPosition;
	}

	public boolean[] getWalls() {
		return walls;
	}

	public void setWalls(boolean[] walls) {
		this.walls = walls;
	}

	public String[] getSigns() {
		return signs;
	}

	public void setSigns(String[] signs) {
		this.signs = signs;
	}

	public boolean isStartPosition() {
		return isStartPosition;
	}

	public void setStartPosition(boolean isStartPosition) {
		this.isStartPosition = isStartPosition;
	}

	public boolean isEndPosition() {
		return isEndPosition;
	}

	public void setEndPosition(boolean isEndPosition) {
		this.isEndPosition = isEndPosition;
	}

	public boolean isHasRedDot() {
		return hasRedDot;
	}

	public void setHasRedDot(boolean hasRedDot) {
		this.hasRedDot = hasRedDot;
	}
}
