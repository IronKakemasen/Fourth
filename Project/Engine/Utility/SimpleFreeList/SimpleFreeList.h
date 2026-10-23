#pragma once

class SimpleFreeList
{
public:

	inline uint32_t Distribute()
	{
		ErrorMessageOutput::Assert::DetectError(!freeList.empty(), listName + " はもうすかすかだぜ", "SimpleFreeList.h");

		uint32_t lastIndex = freeList.back();
		freeList.pop_back();

		return lastIndex;
	}

	inline void Add(uint32_t dst_)
	{
		freeList.emplace_back(dst_);
	}

	inline void Resize(UINT capacity_,std::string const& listName_)
	{
		listName = listName_;

		Logger::Log("resize " + listName_ + "(" + std::to_string(capacity_) + ")");

		freeList.resize(capacity_);

		for (UINT i = 0;i < capacity_;++i)
		{
			freeList[i] = i;
		}
	}

private:

	std::string listName;

	std::vector<uint32_t> freeList;
};

