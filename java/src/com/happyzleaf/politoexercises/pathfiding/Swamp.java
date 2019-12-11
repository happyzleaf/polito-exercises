package com.happyzleaf.politoexercises.pathfiding;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

/**
 * This is my attempt to the Polito's swamp exercise (Informatics).
 * It has been done in Java since it's the language I'm the most fluent in.
 * I'm sure it'd be much harder in C. But I have time.
 *
 * @see <a href="https://areeweb.polito.it/didattica/fondinf/Piccolo/esercizi/Approfondimenti/Palude/palude.pdf">Complete exercise</a>
 * @see <a href="https://web.archive.org/web/20191210233935/https://areeweb.polito.it/didattica/fondinf/Piccolo/esercizi/Approfondimenti/Palude/palude.pdf">Wayback Machine url</a> if anything happens to the other link.
 *
 * @author Marco Montanari
 * @since 10-dec-2019
 */
public class Swamp {
	private final int[][] map;
	private final int columns, rows;

	public Swamp(int[][] map) {
		this.map = map;
		this.columns = map.length;
		this.rows = map[0].length;
	}

	public int[][] getMap() {
		return map; // should be immutable
	}

	public int getColumns() {
		return columns;
	}

	public int getRows() {
		return rows;
	}

	/**
	 * Calculates all the paths and sorts them from the faster to the slowest.
	 *
	 * @return The calculated paths.
	 */
	public List<MapPath> findPaths() {
		List<MapPath> startingPoints = new ArrayList<>();
		for (int x = 0; x < columns; x++) {
			if (map[x][0] == 1) {
				startingPoints.add(new MapPath(new ArrayList<>(), new Point(x, 0)));
			}
		}

		List<MapPath> allPaths = walkRecursively(startingPoints);

		List<MapPath> paths = new ArrayList<>();
		for (MapPath path : allPaths) {
			if (path.getPoint().getY() == rows - 1) {
				paths.add(path);
			}
		}

		paths.sort(Comparator.comparingInt(mapPath -> mapPath.getHistory().size()));

		return paths;
	}

	private List<MapPath> walkRecursively(List<MapPath> parents) {
		List<MapPath> children = new ArrayList<>();

		for (MapPath child : parents) {
			children.addAll(walkRecursively(child.walk()));
		}

		children.addAll(parents);
		return children;
	}

	public class MapPath {
		private final List<Point> history;
		private final Point current;

		public MapPath(List<Point> history, Point current) {
			this.history = history;
			this.current = current;

			this.history.add(this.current);
		}

		public List<MapPath> walk() {
			List<MapPath> possiblePaths = new ArrayList<>();

			for (int x = current.getX() - 1; x <= current.getX() + 1; x++) {
				if (x < 0 || x >= columns) {
					continue;
				}

				for (int y = current.getY() - 1; y <= current.getY() + 1; y++) {
					if (y < 0 || y >= rows) {
						continue;
					}

					Point point = new Point(x, y);
					if (history.contains(point)) {
						continue;
					}

					if (map[x][y] == 1) {
						possiblePaths.add(new MapPath(new ArrayList<>(history), point));
					}
				}
			}

			return possiblePaths;
		}

		public Point getPoint() {
			return current;
		}

		public List<Point> getHistory() {
			return history; // should be immutable
		}

		@Override
		public String toString() {
			return "MapPath{current=" + current + "}";
		}
	}

	public static Swamp fromFile(Path file) throws FileNotFoundException, IllegalArgumentException {
		List<List<Integer>> matrix = new ArrayList<>();

		Scanner scanner = new Scanner(new FileReader(file.toFile()));
		while (scanner.hasNext()) {
			List<Integer> row = new ArrayList<>();
			String line = scanner.nextLine();
			if (line.isEmpty()) {
				continue;
			}

			for (int i = 0; i < line.length(); i++) {
				char c = line.charAt(i);
				if (c == '.') {
					row.add(0);
				} else if (c == '*') {
					row.add(1);
				} else {
					throw new IllegalArgumentException(String.format("Found '%c' in the line.", c));
				}
			}
			matrix.add(row);
		}

		if (matrix.size() == 0) {
			throw new IllegalArgumentException("The file is empty.");
		}

		int rows = matrix.get(0).size();
		for (int i = 1; i < matrix.size(); i++) {
			if (matrix.get(i).size() != rows) {
				throw new IllegalArgumentException("The rows aren't all of the same size.");
			}
		}

		int columns = matrix.size();
		int[][] swamp = new int[columns][rows];
		for (int x = 0; x < columns; x++) {
			for (int y = 0; y < rows; y++) {
				swamp[x][y] = matrix.get(x).get(y);
			}
		}
		return new Swamp(swamp);
	}
}
