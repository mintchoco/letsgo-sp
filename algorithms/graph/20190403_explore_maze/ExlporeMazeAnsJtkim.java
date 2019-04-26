import java.util.Scanner;

public class ExlporeMazeAnsJtkim {

	// up, down, left, right 4 방향 순회용 directive
	private static final int[] dr = {-1, 1, 0, 0};
	private static final int[] dc = {0, 0, -1, 1};

	// 4 방향 체크 시 왔던 길로 돌아가는 것을 막기 위한 플래그
	private static boolean[][] marked = null;
	
	// 최단 경로
	private static int shortest = 0;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int[][] grid = null;
		int N = 0;
		int M = 0;

		// N, M 설정
		if (sc.hasNext()) {
			N = sc.nextInt();
			M = sc.nextInt();
			grid = new int[N][M];
			marked = new boolean[N][M];
			shortest = N * M;
		}

		// 입력 값으로 Grid 초기화
		for (int i = 0; i < N; i++) {
			String line = sc.next();
			for (int j = 0; j < M; j++) {
				grid[i][j] = line.charAt(j) - '0';
			}

		}

		// dfs 로 순회
		dfs(grid, 0, 0, 1);

		System.out.println(shortest);

		sc.close();
	}

	private static void dfs(int[][] grid, int row, int col, int path) {
		// 최종 목적지 도착
		if (row == grid.length - 1 && col == grid[0].length - 1) {
			// 목적지까지 갈 수 있는 경로 중 제일 짧은 경로
			if (shortest > path) {
				shortest = path;
				return;
			}
		}

		marked[row][col] = true;

		// 상 하 좌 우 값이 1인지 체크해서 1이면 해당 경로로 이동
		for (int i = 0; i < 4; i++) {
			int nextRow = row + dr[i];
			int nextCol = col + dc[i];

			// 미로 범위를 벗어나면 다음 경로 탐색
			if (nextRow < 0 || nextRow > grid.length - 1 || nextCol < 0
					|| nextCol > grid[0].length - 1) {
				continue;
			}

			if (marked[nextRow][nextCol] == false
					&& grid[nextRow][nextCol] == 1) {
				dfs(grid, nextRow, nextCol, path + 1);
			}
		}

		marked[row][col] = false;
	}
}
