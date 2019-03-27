int climbStairs(int n) {

	int startOneStepRslt;
	int startTwoStepsRslt;

	if (n <= 1) {
		return 1;
	}
	else {
		// Get number of methods to top start by one step
		startOneStepRslt = climbStairs(n-1);

		// Get number of methods to top start by two steps
		startTwoStepsRslt = climbStairs(n-2);

		return startOneStepRslt + startTwoStepsRslt;
	}
}

