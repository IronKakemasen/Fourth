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

	inline void Resize(UINT capacity_)
	{
		freeList.resize(capacity_);

		for (UINT i = 0;i < capacity_;++i)
		{
			freeList[i] = i;
		}
	}

private:
	std::vector<uint32_t> freeList;
};

