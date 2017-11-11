package rui.maze;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.PaintEvent;
import org.eclipse.swt.graphics.GC;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.wb.swt.SWTResourceManager;

import rui.RUIMain;
import rui.configure.ConfigManager;

public class MazeDrawer {
	private ConfigManager configManager = ConfigManager.getInstance();
	private Canvas canvas;
	
	public MazeDrawer(RUIMain rui) {
		this.canvas = rui.getMazeCanvas();
		
		// @ TODO
		MazeRepository.getInstance().generateMaze();
	}
	
	public void updateMaze(String data) {
		MazeRepository.getInstance().updateMaze(data);
		canvas.redraw();
	}
	
	public void clear() {
		MazeRepository.getInstance().initialize();
		canvas.redraw();
	}

	public void draw(PaintEvent e) {
		GC gc = e.gc;

		int nRow = configManager.getMazeRowCount();
		int nColumn = configManager.getMazeColumnCount();

		int margin = 5;

		Rectangle clientArea = ((Canvas) e.widget).getClientArea();
		int w = clientArea.width - margin * 2;
		int h = clientArea.height - margin * 2;

		int cellWidth = w / nColumn;
		int cellHeight = h / nRow;

		gc.setLineWidth(1);
		gc.setBackground(SWTResourceManager.getColor(SWT.COLOR_BLACK));

//		for (int i = 0; i <= nRow; i++) {
//			gc.drawLine(margin, margin + i * cellHeight, margin + nColumn * cellWidth, margin + i * cellHeight);
//		}
//
//		for (int i = 0; i <= nColumn; i++) {
//			gc.drawLine(margin + i * cellWidth, margin, margin + i * cellWidth, margin + nRow * cellHeight);
//		}

		MazeCell[][] maze = MazeRepository.getInstance().getMaze();

		for (int r = 0; r < nRow; r++) {
			for (int c = 0; c < nColumn; c++) {
				int x = margin + c * cellWidth;
				int y = margin + r * cellHeight;

				maze[r][c].draw(gc, x, y, cellWidth, cellHeight);
			}
		}

//		rui.appendLogMessage(">>> maze drawing completed");
	}
}
