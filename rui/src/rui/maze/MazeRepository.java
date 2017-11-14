package rui.maze;

import rui.configure.ConfigManager;
import rui.utils.Utils;

public class MazeRepository {
	private static MazeRepository instance = new MazeRepository();

	private MazeRepository() {

	}

	private MazeCell[][] maze = new MazeCell[0][0];

	private int nRow = 0;
	private int nColumn = 0;

	public static MazeRepository getInstance() {
		return instance;
	}

	public void initialize() {
		nRow = ConfigManager.getInstance().getMazeRowCount();
		nColumn = ConfigManager.getInstance().getMazeColumnCount();

		maze = new MazeCell[nRow][nColumn];

		for (int i = 0; i < maze.length; i++) {
			MazeCell[] mazeCells = maze[i];
			for (int j = 0; j < mazeCells.length; j++) {
				maze[i][j] = new MazeCell(i, j);
			}
		}
	}

	public void generateMaze() {
		initialize();

		for (int i = 0; i < maze.length; i++) {
			MazeCell[] mazeCells = maze[i];
			for (int j = 0; j < mazeCells.length; j++) {
				MazeCell cell = maze[i][j];
				cell.setWalls(new boolean[] { Math.random() < 0.5, Math.random() < 0.5, Math.random() < 0.5, Math.random() < 0.5 });
				cell.setSigns(new String[] { "B", "GO", "T", "STOP" });
				cell.setVisited(true);
				cell.setHasRedDot(true);
				cell.setCurrentPosition("W");
			}
		}
	}

	private boolean isTrue(String v) {
		return "Y".equals(v);
	}

	private String getSign(String code) {
		if ("G".equals(code))
			return "GO";
		else if ("A".equals(code))
			return "S";
		else if ("P".equals(code))
			return "PUSH";
		else if ("S".equals(code))
			return "STOP";

		return code;
	}

	public void updateMaze(String payload) {
		if (Utils.isEmpty(payload))
			return;

		String[] cells = payload.split("&");

		int startIdx, endIdx;
		int row, column;

		for (String cell : cells) {
			try {
				startIdx = cell.indexOf('{');
				endIdx = cell.lastIndexOf('}');

				if (startIdx == -1 || endIdx == -1)
					continue;

				cell = cell.substring(startIdx + 1, endIdx);
				String[] v = cell.split(",", -1);

				row = Integer.parseInt(v[0]);
				column = Integer.parseInt(v[1]);

				if (!withinBounds(row, column))
					continue;

				MazeCell mazeCell = maze[row][column];

				mazeCell.setVisited(isTrue(v[2]));
				mazeCell.setCurrentPosition(v[3]);
				mazeCell.setStartPosition(isTrue(v[4]));
				mazeCell.setEndPosition(isTrue(v[5]));
				mazeCell.setHasRedDot(isTrue(v[6]));
				mazeCell.setWalls(new boolean[] { isTrue(v[7]), isTrue(v[8]), isTrue(v[9]), isTrue(v[10]) });
				mazeCell.setSigns(new String[] { getSign(v[11]), getSign(v[12]), getSign(v[13]), getSign(v[14]) });
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	boolean withinBounds(int r, int c) {
		return c >= 0 && c < nColumn && r >= 0 && r < nRow;
	}

	public MazeCell[][] getMaze() {
		return maze;
	}
}
