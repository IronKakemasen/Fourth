#pragma once

class SimpleFreeList
{
public:

	inline uint32_t Distribute()
	{
		ErrorMessageOutput::Assert::DetectError(!freeList.empty(), " もうすかすかだぜ", "SimpleFreeList.h");

		uint32_t lastIndex = freeList.back();
		freeList.pop_back();

		return lastIndex;
	}

	inline void Add(uint32_t dst_)
	{
		freeList.emplace_back(dst_);
	}

private:
	std::vector<uint32_t> freeList;
};

