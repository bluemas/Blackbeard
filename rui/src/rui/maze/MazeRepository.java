package rui.maze;

import rui.configure.ConfigManager;

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
				// cell.setWalls(new boolean[] {true,true,true,true});
				cell.setSigns(new String[] { "B", "GO", "T", "STOP" });
				cell.setVisited(true);
				cell.setHasRedDot(true);
			}
		}

	}

	public void updateMaze(String payload) {
		// first, check whether it is within the bound of maze
	}

	boolean withinBounds(int r, int c) {
		return c >= 0 && c < nColumn && r >= 0 && r < nRow;
	}

	public MazeCell[][] getMaze() {
		return maze;
	}
}
