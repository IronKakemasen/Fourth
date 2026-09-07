#pragma once

namespace Comparison
{
	template<typename ValueType>
	ValueType Max(ValueType const lVal_, ValueType const rVal_)
	{
		return lVal_ >= rVal_ ? lVal_ : rVal_;
	}

	template<typename ValueType>
	ValueType Min(ValueType const lVal_, ValueType const rVal_)
	{
		return lVal_ <= rVal_ ? lVal_ : rVal_;
	}

	template<typename ValueType>
	int Sign(ValueType const val_)
	{
		return (val_ > 0) - (val_ < 0);
	}

}