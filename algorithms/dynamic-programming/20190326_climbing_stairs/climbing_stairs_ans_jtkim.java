class Solution {
    // Memoization 용 배열
    int[] nums = null;

    public int climbStairs(int n) {
        if (nums == null) {
            nums = new int[n];
        }

		if (n < 1) {
			return 0;
		} else if (n == 1) {
			return 1;
		} else if (n == 2) {
			return 2;
		} else {
			if (nums[n-1] == 0) {
                // 계단을 1칸 오르는 경우
				nums[n-1] = climbStairs(n-1);
			}
			if (nums[n-2] == 0) {
                // 계단을 2칸 오르는 경우
				nums[n-2] = climbStairs(n-2);
			}

            // 두 경우의 합
			return nums[n-1] + nums[n-2];
		}
	}
}
