#pragma once

struct SRankListBase {
	int rank{ 0 };
	SRankListBase &operator=(const SRankListBase &lcx) = 0;
};