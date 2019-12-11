package com.happyzleaf.politoexercises;

import com.happyzleaf.politoexercises.pathfiding.Point;
import com.happyzleaf.politoexercises.pathfiding.Swamp;

import java.io.FileNotFoundException;
import java.nio.file.Paths;
import java.util.List;

public class PolitoExercises {
	public static void main(String[] args) {
		if (args.length < 1) {
			System.out.println("No arguments specified.");
			return;
		}

		switch (args[0].toLowerCase()) {
			case "swamp":
				if (args.length < 2) {
					System.out.println("No file specified.");
					return;
				}
				try {
					Swamp swamp = Swamp.fromFile(Paths.get(args[1]));

					int[][] map = swamp.getMap();
					for (int x = 0; x < map.length; x++) {
						StringBuilder line = new StringBuilder();
						for (int y = 0; y < map[0].length; y++) {
							line.append(map[x][y]).append(" ");
						}
						System.out.println(line);
					}
					System.out.println();

					List<Swamp.MapPath> paths = swamp.findPaths();
					if (paths.isEmpty()) {
						System.out.println("Couldn't find any path!");
					} else {
						if (paths.size() > 1) {
							System.out.println("Found some paths, here is the faster:");
						} else {
							System.out.println("Found a path:");
						}

						Swamp.MapPath fastest = paths.get(0);
						for (int x = 0; x < map.length; x++) {
							StringBuilder line = new StringBuilder();
							for (int y = 0; y < map[0].length; y++) {
								if (fastest.getHistory().contains(new Point(x, y))) {
									line.append("-").append(" ");
								} else {
									line.append(map[x][y]).append(" ");
								}
							}
							System.out.println(line);
						}
						System.out.println();
					}
				} catch (FileNotFoundException e) {
					System.out.println("Couldn't find the file.");
					e.printStackTrace();
				} catch (IllegalArgumentException e) {
					System.out.println("The file is badly formatted.");
					e.printStackTrace();
				}
				return;
			default:
				System.out.println("Wrong argument.");
		}
	}
}
