#pragma once

namespace utils
{
	struct InputIteratorTag {};
	struct OutputIteratorTag {};
	struct ForwardIteratorTag : InputIteratorTag {};
	struct BidirectionalIteratorTag : ForwardIteratorTag {};
	struct RandomAccessIteratorTag : BidirectionalIteratorTag {};
}